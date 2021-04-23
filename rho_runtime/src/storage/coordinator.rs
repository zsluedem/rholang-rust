use std::collections::hash_map::Entry;
use std::cell::{ RefCell };
use std::rc::Rc;
use tokio::task;


use rustc_hash::{ FxHashMap };

use super::*;
use crossbeam::sync::ShardedLock;
use tokio::sync::mpsc::{ self, Sender, Receiver };
use blake3::Hash;

enum PendingTask{
    Install(InstallTask),
    Produce(ProduceTask),
    Consume(ConsumeTask<ConsumeChannel>),
}


pub(super) struct InstallTask {
    pub(super) channel : ConsumeChannel,
    pub(super) callback : RustCallbacFunction,
}


pub(super) struct ProduceTask {
    pub(super) replier : oneshot::Sender<Reply>,
    pub(super) channel : (Hash, Par),
    pub(super) data : ListParWithRandom,
    pub(super) persistent : bool,
}

pub(super) type ConsumeChannel = (Hash, BindPattern, Par);



pub(super) struct ConsumeTask<T> {
    pub(super) replier : oneshot::Sender<Reply>,
    pub(super) channels : ShortVector<T>,
    pub(super) continuation : TaggedContinuation,
    pub(super) persistent : bool,
    pub(super) peek : bool,
}

pub struct Coordinator {
    _tx: Sender<PendingTask>, // keep an instance here so that it will not close if no other senders
    rx : Receiver<PendingTask>,
    transit_port_map : FxHashMap<Hash, Rc<RefCell<TransitPort>>>
}

#[derive(Default)]
pub struct TransitPort {
    pub(super) completed_signal : Option<oneshot::Receiver<Transit>>,
}


pub struct  AsyncStore {
    tx : ShardedLock<Sender<PendingTask>>,
}

#[async_trait]
impl Storage for AsyncStore {

    async fn install(&self, channel : Par, bind_pattern : BindPattern, func : RustCallbacFunction) -> Reply {
        let install_task = InstallTask{
            channel : (channel.blake3_hash(), bind_pattern, channel),
            callback : func,
        };
        let sender = self.tx.read().unwrap().clone();
        if let Err(err) = sender.send(PendingTask::Install(install_task)).await {
            error!("sender.send(PendingTask::Install(install_task)) failed. {}", &err);
        }
        None
    }
    
    async fn produce(&self, channel : Par, data : ListParWithRandom, persistent : bool) -> Reply {
        let (tx, rx) = oneshot::channel();
        let produce_task = ProduceTask{
            replier : tx,
            channel : (channel.blake3_hash(), channel),
            data : data,
            persistent : persistent,
        };
        let sender = self.tx.read().unwrap().clone();
        if let Err(err) = sender.send(PendingTask::Produce(produce_task)).await {
            error!("sender.send(PendingTask::Produce(produce_task)) failed. {}", &err);
        }
        rx.await.unwrap()
    }

    async fn consume(&self, binds : Vec<(BindPattern, Par)>, body : ParWithRandom, persistent : bool, peek : bool) -> Reply {
        let (tx, rx) = oneshot::channel();
        let consume_task = ConsumeTask{
            replier : tx,
            channels : binds.into_iter().map(|tuple| (tuple.1.blake3_hash(), tuple.0, tuple.1)).collect(),
            continuation : TaggedContinuation::ParBody(body),
            persistent : persistent,
            peek : peek,
        };
        let sender = self.tx.read().unwrap().clone();
        if let Err(err) = sender.send(PendingTask::Consume(consume_task)).await {
            error!("sender.send(PendingTask::Consume(consume_task)) failed. {}", &err);
        }
        rx.await.unwrap()
    }
}


impl Coordinator {

    pub fn create() -> (AsyncStore, Self) {
        let (tx, rx) : (Sender<PendingTask>, Receiver<PendingTask>) = mpsc::channel(1000);
        let hot_store = AsyncStore { tx : ShardedLock::new(tx.clone()) };
        let coordinator = Self { rx : rx, _tx : tx, transit_port_map : FxHashMap::default() };
        (hot_store, coordinator)
    }

    pub async fn run(&mut self) {
        while let Some(pending_task) = self.rx.recv().await {
            match  pending_task {
                PendingTask::Install(install) => {
                    self.handle_install(install)
                },
                PendingTask::Produce(produce) => {
                    self.handle_produce(produce)
                },
                PendingTask::Consume(consume) => {
                    self.handle_consume(consume);
                },
                _ => unreachable!("Bug, this branch must not reach"),
            }
        }
    }

    fn get_or_create_transit_port(&mut self, channel_hash : Hash) -> Rc<RefCell<TransitPort>> {
        match self.transit_port_map.entry(channel_hash) {
            Entry::Occupied(o) => o.into_mut().clone(),
            Entry::Vacant(v) => {
                v.insert(Rc::new(RefCell::new(TransitPort::default()))).clone()
            },
        }
    }


    fn handle_install(&mut self, install : InstallTask) {

        // get the transit port of this channel
        let transit_port = self.get_or_create_transit_port(install.channel.0);
        // create a pair of sender + receiver
        let (tx, rx) = oneshot::channel();
        
        // replace receiver which will be signaled when current coroutine completes
        let prev_signal = match transit_port.borrow_mut().completed_signal.replace(rx) {
            Some(signal) => {
                signal
            },
            None => {
                // no previous Receiver, this is a fresh new channel
                // simulate one
                let (prev_tx, prev_rx) = oneshot::channel();
                if let Err(_) = prev_tx.send(Transit::default()) {
                    warn!("prev_tx.send(Transit::default()) failed but shouldn't!");
                }
                prev_rx
            }
        };
        
        task::spawn( async move {
            // first ensure previous coroutines are completed
            let mut transit = match prev_signal.await {
                Err(e) => {
                    error!("Error in oneshot::Receiver<Transit>. {} - {:?}", &e, &e);
                    return;
                },
                Ok(t) => t
            };

            // now handle it
            Transit::install(&mut transit, install);

            // now send the signal
            if let Err(_) = tx.send(transit) {
                error!("tx.send(transit) failed but shouldn't!");
            }
        });

    }


    fn handle_produce(&mut self, produce : ProduceTask) {

        // get the transit port of this channel
        let transit_port = self.get_or_create_transit_port(produce.channel.0);
        // create a pair of sender + receiver
        let (tx, rx) = oneshot::channel();
        
        // replace receiver which will be signaled when current coroutine completes
        let prev_signal = match transit_port.borrow_mut().completed_signal.replace(rx) {
            Some(signal) => {
                signal
            },
            None => {
                // no previous Receiver, this is a fresh new channel
                // simulate one
                let (prev_tx, prev_rx) = oneshot::channel();
                if let Err(_) = prev_tx.send(Transit::default()) {
                    warn!("prev_tx.send(Transit::default()) failed but shouldn't!");
                }
                prev_rx
            }
        };
        
        task::spawn( async move {
            // first ensure previous coroutines are completed
            let mut transit = match prev_signal.await {
                Err(e) => {
                    warn!("Error in oneshot::Receiver<Transit>. {} - {:?}", &e, &e);
                    return;
                },
                Ok(t) => t
            };

            // now handle it
            Transit::produce(&mut transit, produce);

            // now send the signal
            if let Err(_) = tx.send(transit) {
                warn!("tx.send(transit) failed but shouldn't!");
            }
        });

    }

    fn handle_consume(&mut self, mut consume : ConsumeTask<ConsumeChannel>) {

        let mut tuples = ShortVector::default();
        let mut channels = ShortVector::with_capacity(consume.channels.len());
        channels.append(&mut consume.channels);
        // get all signals
        for tuple in channels {
            // get the transit port of this channel
            let transit_port = self.get_or_create_transit_port(tuple.0);
            // create a pair of sender + receiver
            let (tx, rx) = oneshot::channel();

            tuples.push(
                // replace receiver which will be signaled when current coroutine completes
                match transit_port.borrow_mut().completed_signal.replace(rx) {
                    Some(signal) => {
                        (tuple.0, tuple.1, signal, tx)
                    },
                    None => {
                        // no previous Receiver, this is a fresh new channel
                        // simulate one
                        let (prev_tx, prev_rx) = oneshot::channel();
                        if let Err(_) = prev_tx.send(Transit::default()) {
                            warn!("prev_tx.send(Transit::default()) must not fail");
                        }
                        (tuple.0, tuple.1, prev_rx, tx)
                    }
                }
            );
        }

        
        task::spawn( async move {
            let mut pairs : ShortVector<(Transit, oneshot::Sender<Transit>)> = ShortVector::with_capacity(tuples.len());
            let mut channels : ShortVector<(Option<&mut Transit>, BindPattern, Hash)> = ShortVector::with_capacity(tuples.len());
            
    
            for (hash, bind_pattern, rx, tx) in tuples {
                match rx.await {
                    Err(e) => {
                        warn!("Error in oneshot::Receiver<Transit>. {} - {:?}", &e, &e);
                        return;
                    },
                    Ok(transit) => {
                        pairs.push((transit, tx));
                        channels.push((None, bind_pattern, hash));
                    }
                }
            }
    
            for (pair, chan) in (&mut pairs).iter_mut().zip(&mut channels) {
                chan.0 = Some(&mut pair.0);
            }
    
            // now handle it
            {
                let consuming_task = ConsumeTask::<ConsumingChannel> {
                    replier : consume.replier,
                    continuation : consume.continuation,
                    persistent: consume.persistent,
                    peek : consume.peek,
                    channels : channels,
                };
                Transit::consume(consuming_task)
            };

    
            // now send the signals
            for (transit, sender) in pairs {
                if let Err(_) = sender.send(transit) {
                    warn!("sender.send(transit) failed but it should not!");
                }
            }

        });
                
    }


}

