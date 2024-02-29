from grammar import Grammar
from parser_output import ParserOutput


class LR0Parser:
    def __init__(self, grammar):
        self.grammar = grammar
        self.action_table, self.goto_table = self.grammar.generate_parsing_table()
        self.stack = []  # Stack for parser's states
        self.output = ParserOutput()

    def parse(self, input_string):
        self.stack.append(0)  # Initial state
        input_string += '$'  # End of input marker

        idx = 0
        while True:
            current_state = self.stack[-1]
            current_symbol = input_string[idx]

            action = self.action_table.get((current_state, current_symbol))

            if action is None:
                print("Error: No action defined for state", current_state, "and symbol", current_symbol)
                break

            if action.startswith('shift'):
                # Shift action
                new_state = int(action.split()[1])
                self.stack.append(new_state)
                self.output.add_node(current_symbol)  # Add terminal node
                idx += 1  # Move to next input symbol

            elif action.startswith('reduce'):
                # Reduce action
                production = action.split(' ', 1)[1]
                lhs, rhs = production.split(' -> ')
                rhs_len = len(rhs.split())

                # Pop the stack and ascend the tree in the output
                for _ in range(rhs_len):
                    self.stack.pop()
                    self.output.ascend_tree()

                self.output.add_node(lhs)  # Add nonterminal node after reduction
                goto_state = self.goto_table.get((self.stack[-1], lhs))
                if goto_state is not None:
                    self.stack.append(goto_state)

            elif action == 'accept':
                print("Parsing completed successfully.")
                break

            else:
                print("Error: Undefined action", action)
                break

        return self.output
    
grammar = Grammar()
grammar.read_from_file('g1.txt')
parser = LR0Parser(grammar)
parser_output = parser.parse('ab')

parser_output.print_to_file('output.txt')

