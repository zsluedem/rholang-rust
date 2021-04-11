use super::*;

impl Substitutable for Par {
    fn substitute(&mut self, reducer : &DebruijnInterpreter, depth : i32, env : &Env) -> Result<(), ExecutionError> {
        // substituteNoSort(term).flatMap(par => Sortable.sortMatch(par)).map(_.term)
        unimplemented!("Not implemented yet");
        //Ok(())
    }
    fn substitute_no_sort(&mut self, reducer : &DebruijnInterpreter, depth : i32, env : &Env) -> Result<(), ExecutionError> {

        for s in &mut self.sends {
            s.substitute_no_sort(reducer, depth, env)?;
        }
        for b in &mut self.bundles {
            b.substitute_no_sort(reducer, depth, env)?;
        }
        for r in &mut self.receives {
            r.substitute_no_sort(reducer, depth, env)?;
        }
        for n in &mut self.news {
            n.substitute_no_sort(reducer, depth, env)?;
        }
        for m in &mut self.matches {
            m.substitute_no_sort(reducer, depth, env)?;
        }

        if let Some(ref mut bitset) = self.locally_free {
            bitset.truncate(env.shift); // term.locallyFree.until(env.shift)  need test
        }
 
        substitute_connectives(self, reducer, depth, env)?;
        substitute_expressions(self, reducer, depth, env)?;
        Ok(())
    }

    
}

fn substitute_expressions(par : &mut Par, reducer : &DebruijnInterpreter, depth : i32, env : &Env) -> Result<(), ExecutionError> {
    // the scala code use fold(), here we use imperative style instead to avoid extra allocation
 
    for expression in &mut par.exprs {
        match &mut expression.expr_instance {
            Some(ExprInstance::EVarBody(EVar{ v : Some(var) })) => {
                // case EVarBody(e) =>
                //     maybeSubstitute[M](e).map {
                //         case Left(_e)    => par.prepend(_e, depth)
                //         case Right(_par) => _par ++ par
                //     }
                let _ = var;
                unimplemented!("Some(ExprInstance::EVarBody(EVar))");
            },
            Some(ExprInstance::EVarBody(EVar{ v : None })) => {
                return Err(ExecutionError::new(ExecutionErrorKind::InvalidExpression,
                    "Expr::expr_instance::EVarBody::Var is None")
                );
            },
            None => {
                return Err(ExecutionError::new(ExecutionErrorKind::InvalidExpression,
                    "Expr::expr_instance is None")
                );
            }
            _ => {
                expression.substitute_no_sort(reducer, depth, env)?;
                if let Some(ref instance) = expression.expr_instance {
                    if let Some(bitset) = ExprInstanceLocallyFree::locally_free(instance, depth) {
                        if let Some(ref mut locally_free) = par.locally_free {
                            locally_free.union_with(&bitset);
                        } else {
                            par.locally_free = Some(bitset);
                        }
                    }
        
                    if ExprInstanceLocallyFree::connective_used(instance) {
                        par.connective_used = true;
                    }
                }                
            }
        }
    }
    
    Ok(())
}


fn substitute_connectives(par : &mut Par, reducer : &DebruijnInterpreter, depth : i32, env : &Env) -> Result<(), ExecutionError> {

    if !par.connectives.is_empty() {
        unimplemented!("substitute_connectives() is not implemented");
    }

    Ok(())

    // conns.toList.reverse.foldM(VectorPar()) { (par, conn) =>
    //     conn.connectiveInstance match {
    //       case VarRefBody(v) =>
    //         maybeSubstitute[M](v).map {
    //           case Left(_)       => par.prepend(conn, depth)
    //           case Right(newPar) => newPar ++ par
    //         }
    //       case ConnectiveInstance.Empty => par.pure[M]
    //       case ConnAndBody(ConnectiveBody(ps)) =>
    //         ps.toVector
    //           .traverse(substitutePar[M].substituteNoSort(_))
    //           .map(ps => par.prepend(Connective(ConnAndBody(ConnectiveBody(ps))), depth))
    //       case ConnOrBody(ConnectiveBody(ps)) =>
    //         ps.toVector
    //           .traverse(substitutePar[M].substituteNoSort(_))
    //           .map(ps => par.prepend(Connective(ConnOrBody(ConnectiveBody(ps))), depth))
    //       case ConnNotBody(p) =>
    //         substitutePar[M]
    //           .substituteNoSort(p)
    //           .map(p => Connective(ConnNotBody(p)))
    //           .map(par.prepend(_, depth))
    //       case c: ConnBool      => par.prepend(Connective(c), depth).pure[M]
    //       case c: ConnInt       => par.prepend(Connective(c), depth).pure[M]
    //       case c: ConnString    => par.prepend(Connective(c), depth).pure[M]
    //       case c: ConnUri       => par.prepend(Connective(c), depth).pure[M]
    //       case c: ConnByteArray => par.prepend(Connective(c), depth).pure[M]
    //     }
}