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
 
 
# Example usage
grammar = Grammar()
grammar.read_from_file('g2.txt')
grammar.display_menu()