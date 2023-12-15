use std::fmt;

const TABLE_SIZE: usize = 256; // A constant for the size of the table

// A struct representing an entry in our hash table
#[derive(Clone, Debug)]
struct Entry {
    key: String,
    value: String,
}

#[derive(Debug)]
pub(crate) struct HashTable {
    table: Vec<Option<Vec<Entry>>>, // A vector of options containing vectors of entries
}

impl HashTable {
    pub fn new() -> Self {
        HashTable {
            table: vec![None; TABLE_SIZE],
        }
    }

    pub fn hash(&self, key: &str) -> usize {
        key.bytes()
            .fold(0, |acc, b| (acc + b as usize) % TABLE_SIZE)
    }

    pub fn insert(&mut self, key: String, value: String) -> usize {
        let idx = self.hash(&key);

        // Initialize the position to the index of the bucket
        let position = idx;

        match &mut self.table[idx] {
            Some(bucket) => {
                for (i, entry) in bucket.iter_mut().enumerate() {
                    if entry.key == key {
                        entry.value = value; // Update the value if key already exists
                        return position + i; // Return the unique position
                    }
                }
                bucket.push(Entry { key, value }); // Add a new entry if key not found
                position + bucket.len() - 1 // Return the new position
            }
            None => {
                self.table[idx] = Some(vec![Entry { key, value }]);
                position // The position is the start of the new bucket
            }
        }
    }
}

impl fmt::Display for HashTable {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        // Start with an empty string
        let mut table_str = String::new();

        // Iterate over the hash table and append each key-value pair to the string
        for (i, bucket) in self.table.iter().enumerate() {
            if let Some(entries) = bucket {
                for entry in entries {
                    // Change the format to (hash_table_position, token)
                    table_str.push_str(&format!("({}, {}), ", i, entry.key));
                }
            }
        }

        // Write the formatted string to the formatter
        write!(f, "{}", table_str)
    }
}
