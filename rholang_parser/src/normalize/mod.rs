
use std::ffi::{ CStr }; 
use std::os::raw::c_char;
use std::rc::Rc;
use std::mem;
use std::collections::{ HashMap };



use model::*;

use super::context::*;
use super::bnfc;


mod norm_name;
mod norm_new;
mod norm_send;
mod norm_ground;
mod norm_par;
mod norm_pvar;
mod norm_input;
mod norm_reminder;
mod norm_eval;
mod norm_binary_expression;


//include!("rho_par_test.rs");
//include!("rho_send_test.rs");

type RawProc = bnfc::Proc_;
type RawName = bnfc::Name_;
type RawGround = bnfc::Ground_;
type RawReceipt = bnfc::Receipt_;
type RawNameRemainder = bnfc::NameRemainder_;
type RawProcVar = bnfc::ProcVar_;

pub fn from_root(p : bnfc::Proc) -> NormalizeResult {
    let mut normalizer = Normalizer::default();

    

    let mut result = NormalizeResult::default();
    match normalizer.normalize(p) {
        Err(e) => {
            result.compiliation_error = Some(e);
        },
        Ok(outputs) => {
            result.par = Some(outputs.par);
        },
    };
    result.syntax_errors = mem::replace( &mut normalizer.syntax_errors, Vec::new());
    result
}


// Input data to the normalizer
struct ProcVisitInputs {
    pub par : Par,
    pub env : Rc<IndexMapChain>,
    pub known_free : Rc<DeBruijnLevelMap>,
}

impl Default for ProcVisitInputs {
    fn default() -> Self { 
        Self {
            par : Par::default(),
            env : Rc::new(IndexMapChain::empty()),
            known_free : Rc::new(DeBruijnLevelMap::empty()),
        }
    }
}

impl ProcVisitInputs {
    pub fn clone_with_empty_par(&self) -> Self {
        Self {
            par : Par::default(),
            env : self.env.clone(),
            known_free : self.known_free.clone(),
        }
    }
}

struct ProcVisitOutputs {
    pub par : Par,
    pub known_free : DeBruijnLevelMap,
}


struct NameVisitInputs {
    pub env : Rc<IndexMapChain>,
    pub known_free : Rc<DeBruijnLevelMap>,
}

impl Default for NameVisitInputs {
    fn default() -> Self { 
        NameVisitInputs {
            env : Rc::new(IndexMapChain::empty()),
            known_free : Rc::new(DeBruijnLevelMap::empty()),
        }
    }
}


pub struct NameVisitOutputs {
    pub chan : Par,
    pub known_free : Rc<DeBruijnLevelMap>,
    
}
impl Default for NameVisitOutputs {
    fn default() -> Self { 
        NameVisitOutputs {
            chan : Par::default(),
            known_free : Rc::new(DeBruijnLevelMap::empty()),
        }
    }
}



struct Normalizer {
    pub environment : HashMap<String, Par>,

    // warning messages
    pub source_warnings : Vec<(SourcePosition, String)>,

    // error messages
    pub syntax_errors : Vec<SyntaxError>,   

    pub par : Option<Par>,
}
impl Default for Normalizer {
    fn default() -> Self { 
        Normalizer {
            source_warnings : Vec::new(),
            syntax_errors : Vec::new(),
            environment : HashMap::new(),
            par : None,
        }
    }
}

impl Drop for Normalizer {
    fn drop(&mut self) {

    }
}

impl Normalizer {

    fn normalize(&mut self, p : bnfc::Proc) -> Result<ProcVisitOutputs, CompiliationError> {
        unsafe{
            if p != 0 as bnfc::Proc {
                let s = std::ffi::CString::from_raw(bnfc::showProc(p));
                println!("normalize : {:?}", &s);
            }
        }

        let outputs = self.normalize_proc(p, &ProcVisitInputs::default())?;
        Ok(outputs)
    }

    // traverse abstract syntax tree
    fn normalize_proc(&mut self, p : bnfc::Proc, input: &ProcVisitInputs) -> Result<ProcVisitOutputs, CompiliationError> {
        if p == 0 as bnfc::Proc {
            return Err(CompiliationError::new_null_pointer("proc_"));
        }
        

        let proc = unsafe { *p };
    
        match proc.kind {
            bnfc::Proc__is_PGround => {
                self.normalize_ground(&proc, input)
            },
            bnfc::Proc__is_PPar => {
                self.normalize_par(&proc, input)
            },
            bnfc::Proc__is_PNew => {
                self.normalize_new(&proc, input)
            },
            bnfc::Proc__is_PSend => {
                self.normalize_send(&proc, input)
            },
            bnfc::Proc__is_PVar => {
                self.normalize_pvar(&proc, input)
            },
            bnfc::Proc__is_PInput => {
                self.normalize_input(&proc, input)
            },
            bnfc::Proc__is_PEval => {
                self.normalize_eval(&proc, input)
            },
            bnfc::Proc__is_PAdd => {
                let proc_1 = unsafe { proc.u.padd_.proc_1 };
                let proc_2 = unsafe { proc.u.padd_.proc_2 };
                self.normalize_binary_expression(proc_1, proc_2, input, |left, right| {
                    Expr {
                        expr_instance : Some(expr::ExprInstance::EPlusBody(EPlus {
                            p1 : Some(left),
                            p2 : Some(right)
                        }))
                    }
                })
            },
            bnfc::Proc__is_PNil => {
                Ok(ProcVisitOutputs {
                    par : input.par.clone(),
                    known_free : (*input.known_free).clone(),
                })
            },

            
    
            
            _ => Err(CompiliationError::new_unrecognized_token(proc.kind, proc.line_number, proc.char_number))
        }        
    }


    fn get_string(&mut self, raw_str : bnfc::String) -> Result<String, std::str::Utf8Error> {
        unsafe {
            let raw_pointer = raw_str as *const _ as *const c_char;
            CStr::from_ptr(raw_pointer).to_str().and_then( |s| {
                Ok(s.to_owned())
            })
        }
    }
}