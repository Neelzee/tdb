/// First 2 bytes are the row count, and the remainding bytes are the col_header
pub struct MetaTable {
    row_count: u32,
    col_header: Vec<String>,
}

pub struct MetaCell {
    typ: DBType,
    size: u32,
}

pub enum DBType {
    Int32,
    Int64,
    Str,
    Blob,
}
