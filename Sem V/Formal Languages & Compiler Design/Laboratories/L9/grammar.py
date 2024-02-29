class Grammar:
    def __init__(self):
        self.nonterminals = []
        self.terminals = []
        self.productions = {}
        self.start_symbol = None
 
    def read_from_file(self, file_path):
        try:
            with open(file_path, 'r') as file:
                lines = file.readlines()
        except FileNotFoundError:
            print(f"File not found: {file_path}")
            return

        # Set nonterminals and terminals
        self.nonterminals = lines[0].strip().split()
        self.terminals = lines[1].strip().split()

        # Set start symbol
        self.start_symbol = lines[2].strip()

        # Read productions
        for line in lines[3:]:
            parts = line.strip().split('->')
            if len(parts) != 2:
                continue  # Skip invalid lines

            left, right = parts
            left = left.strip()

            if left not in self.productions:
                self.productions[left] = []

            right_symbols = [symbol.strip() for symbol in right.split('|')]
            self.productions[left].extend(right_symbols)
 
    def print_nonterminals(self):
        print("Nonterminals:", self.nonterminals)
 
    def print_terminals(self):
        print("Terminals:", self.terminals)
 
    def print_productions(self):
        for nonterminal, production_rules in self.productions.items():
            for rule in production_rules:
                print(f"{nonterminal} -> {rule}")
 
    def print_productions_for_nonterminal(self, nonterminal):
        if nonterminal in self.productions:
            print(f"Productions for {nonterminal}:")
            for production in self.productions[nonterminal]:
                print(f"{nonterminal} -> {production}")
        else:
            print(f"No productions found for nonterminal: {nonterminal}")
 
    def is_cfg(self):
        # Check if the start symbol is defined and is a valid nonterminal
        if not self.start_symbol or self.start_symbol not in self.nonterminals:
            print("Invalid or undefined start symbol.")
            return False

        # Check for overlap between terminals and nonterminals
        if set(self.terminals).intersection(self.nonterminals):
            print("Overlap found between terminals and nonterminals.")
            return False

        # Check each production rule
        for left, rights in self.productions.items():
            # Left side should be a single nonterminal
            if not (left in self.nonterminals and len(left.split()) == 1):
                print(f"Invalid production rule: {left} -> {rights}")
                return False

            for right in rights:
                if right == '':  # Allowing e-productions
                    continue

                # Split the right part and check each symbol
                for symbol in right.split():
                    if not (symbol in self.terminals or symbol in self.nonterminals):
                        print(f"Unrecognized symbol in production: {left} -> {right}")
                        return False
        return True
    
    def display_menu(self):
        print("Grammar Operations Menu:")
        print("1. Print Nonterminals")
        print("2. Print Terminals")
        print("3. Print All Productions")
        print("4. Print Productions for a Nonterminal")
        print("5. Check if CFG")
        print("0. Exit")
        choice = input("Enter your choice: ")
 
        if choice == '1':
            self.print_nonterminals()
        elif choice == '2':
            self.print_terminals()
        elif choice == '3':
            self.print_productions()
        elif choice == '4':
            nonterminal = input("Enter the nonterminal: ")
            self.print_productions_for_nonterminal(nonterminal)
        elif choice == '5':
            print("Is CFG:", self.is_cfg())
        elif choice == '0':
            return
        else:
            print("Invalid choice.")
 
        # To continue displaying the menu
        input("Press Enter to continue...")
        self.display_menu()

    def closure(self, items):
        closure_set = set(items)

        while True:
            new_items = set()
            for lhs, rhs_dot in closure_set:
                dot_index = rhs_dot.find('.')
                if dot_index < len(rhs_dot) - 1:  # Ensure dot is not at the end
                    symbol_after_dot = rhs_dot[dot_index + 1]

                    if symbol_after_dot in self.nonterminals:
                        for production in self.productions[symbol_after_dot]:
                            new_item = (symbol_after_dot, '.' + production)
                            if new_item not in closure_set:  # Check if new item is not already in closure set
                                new_items.add(new_item)

            if not new_items:
                break  # No new items were added

            closure_set.update(new_items)

        return closure_set

    
    def go_to(self, state, symbol):
        moved_items = set()
        for lhs, rhs_dot in state:
            dot_index = rhs_dot.find('.')
            if dot_index < len(rhs_dot) - 1 and rhs_dot[dot_index + 1] == symbol:
                # Move the dot past the symbol
                moved_item = (lhs, rhs_dot[:dot_index] + symbol + '.' + rhs_dot[dot_index + 2:])
                moved_items.add(moved_item)

        return self.closure(moved_items)
    
    def canonical_collection(self):
        initial_item = (self.start_symbol, '.' + self.productions[self.start_symbol][0])
        initial_state = self.closure({initial_item})
        states = [initial_state]

        while True:
            new_states = []
            for state in states:
                for symbol in self.terminals + self.nonterminals:
                    next_state = self.go_to(state, symbol)
                    if next_state and next_state not in states and next_state not in new_states:
                        print(f"Transitioning with symbol '{symbol}' from state {state} to new state {next_state}")
                        new_states.append(next_state)

            if not new_states:
                break  # No new states were added

            states.extend(new_states)

        return states
    
    def generate_parsing_table(self):
        action_table = {}
        go_to_table = {}
        collection = self.canonical_collection()

        for i, state in enumerate(collection):
            for item in state:
                lhs, rhs_dot = item
                dot_index = rhs_dot.find('.')

                if dot_index < len(rhs_dot) - 1:  # Shift
                    symbol_after_dot = rhs_dot[dot_index + 1]
                    next_state = self.go_to(state, symbol_after_dot)
                    if symbol_after_dot in self.terminals:
                        action_key = (i, symbol_after_dot)
                        if action_key in action_table:
                            print(f"Conflict at {action_key}")
                        action_table[action_key] = f'shift {collection.index(next_state)}'

                elif dot_index == len(rhs_dot) - 1:  # Reduce or Accept
                    if lhs == self.start_symbol:
                        action_table[(i, '$')] = 'accept'
                    else:
                        for b in self.terminals:
                            action_key = (i, b)
                            if action_key in action_table:
                                print(f"Conflict at {action_key}")
                            action_table[action_key] = f'reduce {lhs} -> {rhs_dot[:-1]}'

            for nonterminal in self.nonterminals:
                next_state = self.go_to(state, nonterminal)
                if next_state:
                    go_to_table[(i, nonterminal)] = collection.index(next_state)

        return action_table, go_to_table

 
 
# Example usage
grammar = Grammar()
grammar.read_from_file('g5.txt')

# Closure testing
""" initial_items = {('S', '.a S'), ('S', '.b S c'), ('S', '.d A'), ('A', '.d c'), ('A', '.e')}
closure_set = grammar.closure(initial_items)
print(closure_set) """

# Go-to testing
""" state = {('S', '.a S'), ('S', '.b S c'), ('S', '.d A'), ('A', '.d c'), ('A', '.e')}
symbol = 'a'
next_state = grammar.go_to(state, symbol)
print(next_state) """

# Print each state in the canonical collection
collection = grammar.canonical_collection()
for i, state in enumerate(collection):
    print(f"State {i}: {state}")
