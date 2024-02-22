use bincode::{deserialize, serialize};
use serde::{Deserialize, Serialize};
use std::fs::File;
use std::io::{Read, Result, Write};

mod db;

#[derive(Debug, Serialize, Deserialize)]
struct Temp {
    val: i32,
    val_2: [i32; 5],
    test: Option<i32>,
}

fn write_temp_to_file(temp: &Temp, file_path: &str) -> Result<()> {
    // Serialize the struct into bytes
    let bytes = serialize(temp).unwrap();

    // Open the file in write mode
    let mut file = File::create(file_path)?;

    // Write the bytes to the file
    file.write_all(&bytes)?;

    Ok(())
}

fn read_temp_from_file(file_path: &str) -> Result<Option<Temp>> {
    // Open the file in read mode
    let mut file = File::open(file_path)?;

    // Get the file size
    let file_size = file.metadata()?.len() as usize;

    // Read the entire file into a buffer
    let mut buffer = Vec::with_capacity(file_size);
    file.read_to_end(&mut buffer)?;

    // Deserialize the buffer into a Temp struct
    Ok(deserialize(&buffer).ok())
}

fn main() {
    let temp_instance = Temp {
        val: 42,
        val_2: [1, 2, 3, 4, 5],
        test: Some(69),
    };

    // Provide the path to the file where you want to write the data
    let file_path = "example";

    // Call the function to write the struct to the file
    if let Err(err) = write_temp_to_file(&temp_instance, file_path) {
        eprintln!("Error writing to file: {}", err);
    }

    println!("{:?}", read_temp_from_file(&file_path));
}
