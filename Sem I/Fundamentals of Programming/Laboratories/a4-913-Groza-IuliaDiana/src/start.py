"""
  Start the program by running this module
"""


from ui import print_main_menu, print_second_menu, print_third_menu, print_fourth_menu, print_fifth_menu, print_solution_sum, print_solution_max, print_solution_sort_one, print_solution_sort_two, print_error, print_index_error, print_apartment_error, print_type_error, print_expense_error, read_option, display_one, display_two, display_three, RegexError
from functions import get_expenses_list, init_expenses, add_expense, modify_one, modify_two, modify_three, modify_four, calculate_one, calculate_two, calculate_three, calculate_four, filter_one, filter_two, undo, test
import re  # Used for regex match


def start():
    """
    Main function
    """
    test()

    expenses_list = []
    init_expenses(get_expenses_list(expenses_list))

    history = []

    while True:
        print_main_menu()

        # Regexes for the main menu input commands
        main_regexes = {
            "add <apartment> <type> <amount>": "^add [1-9][0-9]* (water|heating|electricity|gas|other){1} [1-9][0-9]*$",
            "modify": "^modify$",
            "display": "^display$",
            "calculate": "^calculate$",
            "filter": "^filter$",
            "undo": "^undo$",
            "exit": "^exit$"
        }

        # Input validation
        try:
            option = read_option(main_regexes)

            # First option
            if re.match(main_regexes["add <apartment> <type> <amount>"], option):
                add_expense(get_expenses_list(expenses_list), option, history)
            # Second option
            elif re.match(main_regexes["modify"], option):
                print_second_menu()

                modify_regexes = {
                    "remove <apartment>": "^remove [1-9][0-9]*$",
                    "remove <start apartment> to <end apartment>": "^remove [1-9][0-9]* to [1-9][0-9]*$",
                    "remove <type>": "^remove (water|heating|electricity|gas|other){1}$",
                    "replace <apartment> <type> with <amount>": "^replace [1-9][0-9]* (water|heating|electricity|gas|other){1} with [1-9][0-9]*$",
                    "back": "^back$"
                }
                second_option = read_option(modify_regexes)

                # Options of the second menu
                if re.match(modify_regexes["back"], second_option):
                    continue
                elif re.match(modify_regexes["remove <apartment>"], second_option):
                    try:
                        modify_one(get_expenses_list(expenses_list), second_option, history)
                    except IndexError:
                        print_apartment_error()
                elif re.match(modify_regexes["remove <start apartment> to <end apartment>"], second_option):
                    modify_two(get_expenses_list(expenses_list), second_option, history)
                elif re.match(modify_regexes["remove <type>"], second_option):
                    try:
                        modify_three(get_expenses_list(expenses_list), second_option, history)
                    except IndexError:
                        print_type_error()
                else:
                    try:
                        modify_four(get_expenses_list(expenses_list), second_option, history)
                    except IndexError:
                        print_expense_error()
            # Third option
            elif re.match(main_regexes["display"], option):
                print_third_menu()

                display_regexes = {
                    "list": "^list$",
                    "list <apartment>": "^list [1-9][0-9]*$",
                    "list [ < | = | > ] <amount>": "^list (<|=|>){1} [1-9][0-9]*$",
                    "back": "^back$"
                }
                second_option = read_option(display_regexes)

                # Options of the third menu
                if re.match(display_regexes["back"], second_option):
                    continue
                elif re.match(display_regexes["list"], second_option):
                    display_one(get_expenses_list(expenses_list))
                elif re.match(display_regexes["list <apartment>"], second_option):
                    display_two(get_expenses_list(expenses_list), second_option)
                else:
                    display_three(get_expenses_list(expenses_list), second_option)
            # Fourth option
            elif re.match(main_regexes["calculate"], option):
                print_fourth_menu()

                calculate_regexes = {
                    "sum <type>": "^sum (water|heating|electricity|gas|other){1}$",
                    "max <apartment>": "^max [1-9][0-9]*$",
                    "sort apartment": "^sort apartment$",
                    "sort type": "^sort type$",
                    "back": "^back$"
                }
                second_option = read_option(calculate_regexes)

                if re.match(calculate_regexes["back"], second_option):
                    continue
                elif re.match(calculate_regexes["sum <type>"], second_option):
                    try:
                        print_solution_sum(calculate_one(get_expenses_list(expenses_list), second_option))
                    except IndexError:
                        print_type_error()
                elif re.match(calculate_regexes["max <apartment>"], second_option):
                    try:
                        print_solution_max(calculate_two(get_expenses_list(expenses_list), second_option))
                    except IndexError:
                        print_apartment_error()
                elif re.match(calculate_regexes["sort apartment"], second_option):
                    print_solution_sort_one(calculate_three(get_expenses_list(expenses_list)))
                else:
                    print_solution_sort_two(calculate_four(get_expenses_list(expenses_list)))
            # Fifth option
            elif re.match(main_regexes["filter"], option):
                print_fifth_menu()

                filter_regexes = {
                    "filter <type>": "^filter (water|heating|electricity|gas|other){1}$",
                    "filter <value>": "^filter [1-9][0-9]*$",
                    "back": "^back$"
                }
                second_option = read_option(filter_regexes)

                if re.match(filter_regexes["back"], second_option):
                    continue
                elif re.match(filter_regexes["filter <type>"], second_option):
                    filter_one(get_expenses_list(expenses_list), second_option, history)
                else:
                    filter_two(get_expenses_list(expenses_list), second_option, history)
            # Sixth option
            elif re.match(main_regexes["undo"], option):
                try:
                    undo(get_expenses_list(expenses_list), history)
                except IndexError:
                    print_index_error()
            else:
                return
        except RegexError:
            print_error()


# Main call
start()
