use std::sync::atomic::AtomicBool;
use crossbeam::queue::SegQueue;
use tokio::task::JoinHandle;
use std::sync::Arc;
use std::sync::atomic::Ordering;

use tokio::task;

mod reduce;
pub use reduce::*;

use super::storage::*;
use model::*;

pub struct InterpreterContext<S> where S : Storage + std::marker::Send + std::marker::Sync {
    storage : S,
    aborted : AtomicBool,
    errors : SegQueue<ExecutionError>,
    join_handles : SegQueue<JoinHandle<Result<(), ExecutionError>>>,
}

impl<S:Storage + std::marker::Send + std::marker::Sync> From<S> for InterpreterContext<S> {
    fn from(storage: S) -> Self {
        Self {
            storage : storage,
            aborted : AtomicBool::default(),
            errors : SegQueue::default(),
            join_handles : SegQueue::default(),
        }
    }
}




impl<S : Storage + std::marker::Send + std::marker::Sync + 'static> InterpreterContext<S> {

    pub async fn evaludate(self : &Arc<Self>, mut par : Par) {
        let env = Env::<Par>::default();
        par.evaluate(&self, &env).await.expect("par.evaluate(&self, &env) failed"); // should never fail
        while let Some(handle) = self.join_handles.pop() {
            let result = handle.await;
            match result {
                Ok(Err(err)) => {
                    if err.kind != ExecutionErrorKind::Aborted as i32 {
                        self.aborted.store(true, Ordering::Relaxed);
                        self.errors.push(err.clone());
                    }
                },
                Err(err) => panic!("JoinError occured in InterpreterContext::evaludate. {}", err),
                _ => (),
            }
        }
    }

    fn spawn_evaluation<T>(self : &Arc<Self>, t : T, env : &Env)
        where T : AsyncEvaluator<S> + std::marker::Send + 'static
    {
        let cloned_context = self.clone();
        let cloned_env = env.clone();
        self.join_handles.push(
            task::spawn( async move {
                let mut evaluator = t;
                let reference = &mut evaluator;
                if let Err(err) = reference.evaluate(&cloned_context, &cloned_env).await {
                    if err.kind != ExecutionErrorKind::Aborted as i32 {
                        cloned_context.aborted.store(true, Ordering::Relaxed);
                        cloned_context.errors.push(err.clone());
                    }
                    return Err(err);
                }
                Ok(())
            })
        );
    }

    

    
    #[inline]
    pub fn may_raise_aborted_error(&self) -> Result<(), ExecutionError> {
        if self.aborted.load(Ordering::Relaxed) {
            Err(ExecutionError{
                kind : ExecutionErrorKind::Aborted as i32,
                message : "aborted".to_string(),
            })
        } else {
            Ok(())
        }
    }


    
    #[inline]
    async fn produce(self : &Arc<Self>, channel : Par, data : ListParWithRandom, persistent : bool) {
        self.handle_comm_events(
            self.storage.produce(channel, data, persistent).await
        );
    }

    #[inline]
    async fn consume(self : &Arc<Self>, binds : Vec<(BindPattern, Par)>,body : ParWithRandom, persistent : bool, peek : bool) {
        self.handle_comm_events(
            self.storage.consume(binds, body, persistent, peek).await
        );
    }

    fn handle_comm_events(self : &Arc<Self>, reply : Reply) {
        match reply {
            Reply::ParWithBody(par_with_rand, data_list) => {
                
                let pars : Vec<_> = data_list.into_iter().flat_map( |x| x.pars.into_iter() ).collect();
                let env = Env::<Par>::create(pars);
                match par_with_rand.body {
                    Some(par) => {
                        self.spawn_evaluation(par, &env);
                    },
                    _ => {

                    }
                }
            },
            Reply::None => (),
        }
        
    }
}
