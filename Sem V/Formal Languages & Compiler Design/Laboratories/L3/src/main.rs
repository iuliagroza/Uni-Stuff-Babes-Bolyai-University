mod symbol_table;

use regex::Regex;
use std::collections::HashMap;
use std::fs;
use std::fs::File;
use std::io::Write;
use symbol_table::HashTable;

// Struct to represent the lexical scanner
struct LexicalScanner {
    symbol_table: HashTable,
    tokens: HashMap<String, String>,
}

impl LexicalScanner {
    // Initialize a new Lexical Scanner with the token list and empty symbol table
    fn new(token_file: &str) -> Self {
        let mut tokens = HashMap::new();
        let token_content = fs::read_to_string(token_file).expect("Unable to read token file");
        for token in token_content.lines() {
            tokens.insert(token.trim().to_string(), token.trim().to_string());
        }

        LexicalScanner {
            symbol_table: HashTable::new(),
            tokens,
        }
    }

    // Function to tokenize the input file
    fn tokenize(&mut self, file_path: &str) -> Result<(Vec<(String, isize)>, String), String> {
        let file_content = fs::read_to_string(file_path).expect("Unable to read file");
        let mut pif = Vec::new();
        let mut line_number = 1;

        for line in file_content.lines() {
            let tokens = self.extract_tokens(line);
            for token in tokens {
                if self.tokens.contains_key(&token) {
                    // Known token (not an identifier or constant), position is -1
                    pif.push((token, -1));
                } else if self.is_identifier(&token) || self.is_constant(&token) {
                    // Identifier or constant, insert into symbol table and use the position
                    let position = self
                        .symbol_table
                        .insert(token.to_string(), token.to_string())
                        as isize;
                    pif.push((token, position));
                } else {
                    // Token not recognized, return an error
                    return Err(format!("Lexical error at line {}: {}", line_number, token));
                }
            }
            line_number += 1;
        }

        Ok((pif, self.symbol_table.to_string()))
    }

    // Helper function to extract tokens from a line
    fn extract_tokens(&self, line: &str) -> Vec<String> {
        // Split the line at the comment start sequence ('//')
        let parts = line.splitn(2, "//").collect::<Vec<&str>>();
        let code_part = parts[0].trim();

        // If the code part is empty after splitting, return an empty vector
        if code_part.is_empty() {
            return vec![];
        }

        // Regex pattern to match operators, individual symbols, string literals, and other tokens
        let re = Regex::new(r#""[^"]*"|&&|\|\||==|<=|>=|!=|[\+\-\*/%]|[,;()]|[^\s;(),"+\-\*/%]+"#)
            .unwrap();
        re.find_iter(code_part)
            .map(|mat| mat.as_str().to_string())
            .collect()
    }

    // Function to check if a string is an identifier
    fn is_identifier(&self, s: &str) -> bool {
        let re = Regex::new(r"^[a-zA-Z_][a-zA-Z0-9_]*$").unwrap();
        re.is_match(s)
    }

    // Function to check if a string is a constant
    fn is_constant(&self, s: &str) -> bool {
        // Regex for integer constants (signed/unsigned)
        let int_const_re = Regex::new(r"^(\+|-)?\d+$").unwrap();

        // Regex for string constants
        // Matches a sequence of alphanumeric characters, underscores, and spaces between double quotes
        let str_const_re = Regex::new(r#"^"[a-zA-Z0-9_ ]*"$"#).unwrap();

        int_const_re.is_match(s) || str_const_re.is_match(s)
    }
}

fn main() {
    // Initialize the scanner
    let mut scanner = LexicalScanner::new("src/token.in");

    // Process the input file
    let result = scanner.tokenize("src/code_sources/p1.aks");

    // Handle the results
    match result {
        Ok((pif, symbol_table)) => {
            // Save PIF to PIF.out
            let mut pif_file =
                File::create("src/output/PIF.out").expect("Could not create PIF.out file");
            for (token, position) in pif {
                writeln!(pif_file, "({}, {})", token, position)
                    .expect("Could not write to PIF.out file");
            }

            // Save Symbol Table to ST.out
            let mut st_file =
                File::create("src/output/ST.out").expect("Could not create ST.out file");
            write!(st_file, "{}", symbol_table).expect("Could not write to ST.out file");
        }
        Err(err) => {
            // Output error message
            println!("{}", err);
        }
    }
}
