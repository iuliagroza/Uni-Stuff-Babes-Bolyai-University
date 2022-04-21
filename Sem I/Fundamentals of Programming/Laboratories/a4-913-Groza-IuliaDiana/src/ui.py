"""
  User interface module
"""


from functions import get_value, get_expense, get_expenses_list
import re  # Used for regex match


class RegexError(Exception):
    """
    Raised when a string doesn't match a given regex
    """
    pass


def print_main_menu():
    print("""Welcome to the Apartment Building Administrator! Choose one of the operations that are listed below by typing its corresponding command format:
        add <apartment> <type> <amount> - Add to apartment <apartment> (positive integer) an expense for <type> ("water", "heating", "electricity", "gas" or "other") 
                                          in amount of <amount> (positive integer).
        modify - Modify expenses.
        display - Display expenses.
        calculate - Obtain different characteristics of the expenses.
        filter - Filter expenses.
        undo - Undo the last operation.
        exit - Exit""")


def print_second_menu():
    print("""Choose one of the modify operations that are listed below by typing its corresponding command format:
        remove <apartment> - Remove all the expenses for apartment <apartment> (positive integer).
        remove <start apartment> to <end apartment> - Remove all expenses for apartments between <start_apartment> (positive integer) and <end_apartment> (positive integer).
        remove <type> - Remove all <type> ("water", "heating", "electricity", "gas" or "other") expenses from all apartments.
        replace <apartment> <type> with <amount> - Replace the amount of the expense with type <type> ("water", "heating", "electricity", "gas" or "other") for apartment 
                                                   <apartment> (positive integer) with <amount> (positive integer).
        back - Return to main menu.
        """)


def print_third_menu():
    print("""Choose one of the display operations that are listed below by typing its corresponding command format:
        list - Display all expenses.
        list <apartment> - Display all expenses for apartment <apartment> (positive integer).
        list [ < | = | > ] <amount> - Display all apartments having total expenses [ < | = | > ]<amount> (positive integer).
        back - Return to main menu.
    """)


def print_fourth_menu():
    print("""Choose one of the calculate operations that are listed below by typing its corresponding command format:
        sum <type> - Display the total amount for the expenses having type <type> ("water", "heating", "electricity", "gas" or "other").
        max <apartment> - Display the maximum amount per each expense type for apartment <apartment> (positive integer).
        sort apartment - Display the list of apartments sorted ascending by total amount of expenses.
        sort type -  Display the total amount of expenses for each type, sorted ascending by amount of money.
        back - Return to main menu.
    """)


def print_fifth_menu():
    print("""Choose one of the filter operations that are listed below by typing its corresponding command format:
        filter <type> - Keep only expenses for <type> ("water", "heating", "electricity", "gas" or "other").
        filter <value> - Keep only expenses having an amount of money smaller than <value> (positive integer).
        back - Return to main menu.
    """)


def read_option(regexes):
    """
    Function that reads and validates the input using a list of regex for every permitted format. This allows us to use the
    function in every input read situation.
    :param regexes: list of strings
    :return: string
    """
    option = input(">>> ")

    correct = False
    for regex in regexes.keys():
        if re.match(regexes[regex], option):
            correct = True

    if not correct:
        raise RegexError

    return option


def print_solution_sum(items):
    """
    Prints the solution of "sum <type>" command.
    :param items: list
    """
    print(f"The total amount for the expenses having type {items[1]} is: {items[0]} RON.")


def print_amount_max(item, type):
    """
    Used in the print_solution_max() function.
    :param item: non-negative integer
    :param type: string
    """
    if item == 0:
        print(f"{type}: no expenses")
    else:
        print(f"{type}: {item} RON")


def print_solution_max(items):
    """
    Prints the solution of "max <apartment>" command.
    :param items: list
    """
    print_amount_max(items[0], "water")
    print_amount_max(items[1], "heating")
    print_amount_max(items[2], "electricity")
    print_amount_max(items[3], "gas")
    print_amount_max(items[4], "other")


def print_solution_sort_one(items):
    """
    Prints the solution of "sort apartment" command.
    :param items: dictionary
    """
    for item in items.keys():
        print(f"Apartment {item}: {items[item]} RON")


def print_solution_sort_two(items):
    """
    Prints the solution of "sort type" command.
    :param items: dictionary
    """
    for item in items.keys():
        print(f"Expenses of type {item}: {items[item]} RON")


def print_error():
    print("Invalid command.")


def print_index_error():
    print("There are no more operations to undo.")


def print_apartment_error():
    print("This apartment does not exist.")


def print_type_error():
    print("There are no expenses of this type.")


def print_expense_error():
    print("There is no such expense.")


def display_one(expenses_list):
    """
    Implements the "list" command. If there are no elements in the list, we print an appropriate message.
    :param expenses_list: list
    """
    if len(get_expenses_list(expenses_list)) == 0:
        print("There are no expenses.")

    for expense in get_expenses_list(expenses_list):
        print(get_expense(expense))


def display_two(expenses_list, command):
    """
    Implements the "list <apartment>" command. If there is no such expense, we print an appropriate message.
    :param expenses_list: list
    :param command: string
    """
    apartment = int(command.split()[1])
    ok = False

    for expense in get_expenses_list(expenses_list):
        if get_value(get_expense(expense), "apartment") == apartment:
            print(get_expense(expense))
            ok = True

    if not ok:
        print("There is no apartment " + str(apartment) + " in the expenses list.")


def display_three(expenses_list, command):
    """
    Implements the "list [ < | = | > ] <amount>" operation.
    :param expenses_list: list
    :param command: string
    """
    comparator = command.split()[1]
    amount = int(command.split()[2])
    ok = False

    for expense in get_expenses_list(expenses_list):
        if comparator == ">" and get_value(get_expense(expense), "amount") > amount:
            print(get_expense(expense))
            ok = True
        if comparator == "=" and get_value(get_expense(expense), "amount") == amount:
            print(get_expense(expense))
            ok = True
        if comparator == "<" and get_value(get_expense(expense), "amount") < amount:
            print(get_expense(expense))
            ok = True

    if not ok:
        print("There is no expense that meets this requirement.")
