use std::fs::File;
use std::io::{self, BufRead};

pub(crate) struct FiniteAutomata {
    states: Vec<String>,
    alphabet: Vec<char>,
    transitions: Vec<((String, char), String)>,
    initial_state: String,
    final_states: Vec<String>,
}

impl FiniteAutomata {
    pub fn new() -> Self {
        FiniteAutomata {
            states: vec![],
            alphabet: vec![],
            transitions: Vec::new(),
            initial_state: String::new(),
            final_states: vec![],
        }
    }

    pub fn read_from_file(&mut self, filename: &str) -> io::Result<()> {
        let file = File::open(filename)?;
        let lines = io::BufReader::new(file).lines();

        for line in lines {
            let line = line?;
            let parts: Vec<&str> = line.split(':').collect();
            if parts.len() != 2 {
                continue;
            }

            match parts[0].trim() {
                "states" => {
                    self.states = parts[1].split(',').map(|s| s.trim().to_string()).collect()
                }
                "alphabet" => {
                    self.alphabet = parts[1]
                        .split(',')
                        .map(|s| s.trim())
                        .filter(|s| !s.is_empty())
                        .collect::<String>()
                        .chars()
                        .collect()
                }
                "initial state" => self.initial_state = parts[1].trim().to_string(),
                "final state" => {
                    self.final_states = parts[1].split(',').map(|s| s.trim().to_string()).collect()
                }
                "transitions" => {
                    self.transitions = parts[1]
                        .split(';')
                        .filter(|&t| !t.trim().is_empty()) // Filter out empty transitions
                        .map(|transition| {
                            let elements: Vec<&str> = transition.trim().split(',').collect();
                            if elements.len() == 3 {
                                let from_state = elements[0]
                                    .trim_matches(|p| p == '(' || p == ')')
                                    .to_string();
                                let to_state = elements[1].trim().to_string();
                                let symbol = elements[2].trim().chars().next().unwrap();

                                ((from_state, symbol), to_state)
                            } else {
                                (("".to_string(), ' '), "".to_string()) // Placeholder for invalid transition
                            }
                        })
                        .filter(|t| !t.0 .0.is_empty()) // Further filter out any invalid transitions
                        .collect();
                }
                _ => (),
            }
        }

        Ok(())
    }

    pub fn is_sequence_accepted(&self, sequence: &str) -> bool {
        let mut current_state = self.initial_state.clone();

        for c in sequence.chars() {
            if !self.alphabet.contains(&c) {
                return false; // Invalid character in sequence
            }

            let mut transition_found = false;
            for transition in &self.transitions {
                if transition.0 == (current_state.clone(), c) {
                    current_state = transition.1.clone();
                    transition_found = true;
                    break;
                }
            }

            if !transition_found {
                return false; // No transition found for this character
            }
        }

        self.final_states.contains(&current_state)
    }
}
