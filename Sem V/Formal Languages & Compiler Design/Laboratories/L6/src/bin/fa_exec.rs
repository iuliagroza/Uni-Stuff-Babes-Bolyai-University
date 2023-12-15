use std::fs::File;
use std::io::{self, BufRead};

fn main() {
    let mut fa = FiniteAutomata::new();
    if let Err(e) = fa.read_from_file("src/fa_input_config/fa.in") {
        println!("Error reading file: {}", e);
        return;
    }

    loop {
        println!("Menu:");
        println!("1. Show states");
        println!("2. Show alphabet");
        println!("3. Show transitions");
        println!("4. Show initial state");
        println!("5. Show final states");
        println!("6. Check sequence acceptance");
        println!("7. Exit");

        let mut choice = String::new();
        io::stdin().read_line(&mut choice).unwrap();
        match choice.trim() {
            "1" => println!("States: {:?}", fa.states),
            "2" => println!("Alphabet: {:?}", fa.alphabet),
            "3" => fa.show_transitions(),
            "4" => println!("Initial State: {}", fa.initial_state),
            "5" => println!("Final States: {:?}", fa.final_states),
            "6" => {
                println!("Enter a sequence:");
                let mut sequence = String::new();
                io::stdin().read_line(&mut sequence).unwrap();
                let accepted = fa.is_sequence_accepted(sequence.trim());
                println!("Sequence accepted: {}", accepted);
            }
            "7" => break,
            _ => println!("Invalid choice, try again."),
        }
    }
}

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

    pub fn show_transitions(&self) {
        for transition in &self.transitions {
            println!(
                "{} on {} goes to {}",
                transition.0 .0, transition.0 .1, transition.1
            );
        }
    }
}
