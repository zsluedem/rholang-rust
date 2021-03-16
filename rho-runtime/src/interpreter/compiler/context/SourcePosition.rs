// Represents code location in source
#[derive(Debug, Clone)]
pub struct SourcePosition {
    pub row : i32,
    pub column : i32,
    pub length : usize,
}
impl fmt::Display for SourcePosition {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{}:{}", self.row, self.column)
    }
}

impl SourcePosition {
    pub fn new (row : i32, col : i32, len : usize) -> SourcePosition {
        SourcePosition {
            row : row,
            column : col,
            length : len,
        }
    }
}