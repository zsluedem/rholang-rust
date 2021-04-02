
// Extends the generated ExecutionError struct
impl ExecutionError {
    pub fn new_invalid_expression(message : String) -> Self {
        ExecutionError {
            kind : ExecutionErrorKind::InvalidExpression as i32,
            message : message
        }
    }

    

}







impl fmt::Display for ExecutionError {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{} - {}", &self.kind, &self.message)
    }
}

impl Error for ExecutionError {
    fn source(&self) -> Option<&(dyn Error + 'static)> {
        None
    }
}

