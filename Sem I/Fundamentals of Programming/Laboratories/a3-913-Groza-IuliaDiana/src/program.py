"""
5. Apartment Building Administrator
"""


import re  # Used for regex match


"""
  Write non-UI functions below
"""


# Getters
def get_value(expense, key):
    return expense[key]


def get_expense(expense):
    return expense


def get_expenses_list(expenses_list):
    return expenses_list


# Setters
def set_key(dict, key, value):
    """
    We set the key of an expense with its corresponding value. If it does not exist, we create it.
    :param dict: dictionary
    :param key: string
    :param value: string/integer
    """
    if key in dict.keys():
        dict[key] = value
    else:
        dict.update({key: value})


def set_expense(expense, apartment, type, amount):
    """
    We set an expense by setting each of its keys using the setter above.
    :param expense: dictionary
    :param apartment: integer
    :param type: string
    :param amount: integer
    """
    set_key(expense, "apartment", apartment)
    set_key(expense, "type", type)
    set_key(expense, "amount", amount)


def set_expenses_list(expenses_list, new_expenses_list):
    expenses_list[:] = new_expenses_list[:]


def init_expenses(expenses_list):
    """
    We initiate an expense list with the predefined list below using its setter.
    :param expenses_list: list
    """
    new_expenses_list = [{"apartment": 25, "type": "other", "amount": 200},
                         {"apartment": 1, "type": "heating", "amount": 400},
                         {"apartment": 100, "type": "heating", "amount": 50},
                         {"apartment": 25, "type": "gas", "amount": 99},
                         {"apartment": 70, "type": "electricity", "amount": 1320},
                         {"apartment": 25, "type": "other", "amount": 322},
                         {"apartment": 100, "type": "gas", "amount": 50},
                         {"apartment": 29, "type": "other", "amount": 100},
                         {"apartment": 99, "type": "water", "amount": 200},
                         {"apartment": 70, "type": "water", "amount": 200}]

    set_expenses_list(expenses_list, new_expenses_list)


def add_expense(expenses_list, command):
    """
    We create an expense and then we append it to the list of expenses. Notice that duplicates are allowed.
    Each key of the expense dictionary is obtained parsing the command string using .split().
    :param expenses_list: list
    :param command: string
    """
    expense = {}
    apartment = int(command.split()[1])
    type = command.split()[2]
    amount = int(command.split()[3])

    set_expense(expense, apartment, type, amount)

    get_expenses_list(expenses_list).append(get_expense(expense))


def modify_one(expenses_list, command):
    """
    Function that implements the "remove <apartment>" operation. If such expense is found, we replace the expanses list with a
    list that does not contain it (using concatenation).
    :param expenses_list: list
    :param command: string
    """
    apartment = int(command.split()[1])

    index = 0
    while index < len(get_expenses_list(expenses_list)):
        if get_value(get_expense(expenses_list[index]), "apartment") == apartment:
            set_expenses_list(expenses_list, get_expenses_list(expenses_list[:index])+get_expenses_list(expenses_list[index+1:]))
        else:
            index += 1


def modify_two(expenses_list, command):
    """
    Implements the "remove <start apartment> to <end apartment>" command. Similar to the first modify function.
    :param expenses_list: list
    :param command: string
    """
    start_apartment = int(command.split()[1])
    end_apartment = int(command.split()[3])

    index = 0
    while index < len(get_expenses_list(expenses_list)):
        if start_apartment <= get_value(get_expense(expenses_list[index]), "apartment") <= end_apartment:
            set_expenses_list(expenses_list, get_expenses_list(expenses_list[:index])+get_expenses_list(expenses_list[index+1:]))
        else:
            index += 1


def modify_three(expenses_list, command):
    """
    Implements the "remove <type>" operation. Similar to the first modify function.
    :param expenses_list: list
    :param command: string
    """
    type = command.split()[1]

    index = 0
    while index < len(get_expenses_list(expenses_list)):
        if get_value(get_expense(expenses_list[index]), "type") == type:
            set_expenses_list(expenses_list, get_expenses_list(expenses_list[:index])+get_expenses_list(expenses_list[index+1:]))
        else:
            index += 1


def modify_four(expenses_list, command):
    """
    Implements the "replace <apartment> <type> with <amount>" operation. We modify the expense by setting a new amount value.
    :param expenses_list: list
    :param command: string
    """
    apartment = int(command.split()[1])
    type = command.split()[2]
    amount = int(command.split()[4])

    for index in range(len(get_expenses_list(expenses_list))):
        if get_value(get_expense(expenses_list[index]), "apartment") == apartment and get_value(get_expense(expenses_list[index]), "type") == type:
            set_expense(get_expenses_list(expenses_list)[index], apartment, type, amount)


"""
  Write the command-driven UI below
"""


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


def print_error():
    print("Invalid command.")


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


def test_get_value():
    expense = {
        "apartment": 234,
        "type": "heating",
        "amount": 1000
    }

    assert(get_value(expense, "type") == "heating")
    assert(get_value(expense, "amount") == 1000)


def test_get_expense():
    expense = {
        "apartment": 234,
        "type": "heating",
        "amount": 1000
    }

    assert(get_expense(expense) == expense)


def test_get_expenses_list():
    expenses_list = [{"apartment": 34, "type": "heating", "amount": 230},
                     {"apartment": 34, "type": "gas", "amount": 1099},
                     {"apartment": 12, "type": "heating", "amount": 50},
                     {"apartment": 9, "type": "other", "amount": 400}]

    assert(get_expenses_list(expenses_list) == expenses_list)


def test_set_key():
    expense = {
        "apartment": 234,
        "amount": 1000
    }

    set_key(expense, "apartment", 250)
    set_key(expense, "type", "other")

    assert(expense == {
        "apartment": 250,
        "type": "other",
        "amount": 1000
    })


def test_set_expense():
    expense = {
        "apartment": 234,
        "amount": 1000
    }

    set_expense(expense, 250, "water", 1300)

    assert(expense == {
        "apartment": 250,
        "type": "water",
        "amount": 1300
    })


def test_set_expenses_list():
    expenses_list = [{"apartment": 25, "type": "water", "amount": 1340},
                     {"apartment": 30, "type": "other", "amount": 29}]

    new_expenses_list = [{"apartment": 34, "type": "heating", "amount": 230},
                         {"apartment": 34, "type": "gas", "amount": 1099},
                         {"apartment": 12, "type": "heating", "amount": 50},
                         {"apartment": 9, "type": "other", "amount": 400}]

    set_expenses_list(expenses_list, new_expenses_list)

    assert(expenses_list == new_expenses_list)


def test_add():
    """
    Tests add_expense() function.
    """
    expenses_list = [{"apartment": 34, "type": "heating", "amount": 230}, {"apartment": 34, "type": "gas", "amount": 1099},
                     {"apartment": 12, "type": "heating", "amount": 50}, {"apartment": 9, "type": "other", "amount": 400}]

    add_expense(expenses_list, "add 9 other 400")
    add_expense(expenses_list, "add 89 water 110")

    assert(expenses_list == [{"apartment": 34, "type": "heating", "amount": 230},
                             {"apartment": 34, "type": "gas", "amount": 1099},
                             {"apartment": 12, "type": "heating", "amount": 50},
                             {"apartment": 9, "type": "other", "amount": 400},
                             {"apartment": 9, "type": "other", "amount": 400},
                             {"apartment": 89, "type": "water", "amount": 110}])


def test_modify_one():
    """
    Tests modify_one() function
    """
    expenses_list = [{"apartment": 34, "type": "heating", "amount": 230},
                     {"apartment": 34, "type": "gas", "amount": 1099},
                     {"apartment": 12, "type": "heating", "amount": 50},
                     {"apartment": 9, "type": "other", "amount": 400},
                     {"apartment": 9, "type": "other", "amount": 400},
                     {"apartment": 89, "type": "water", "amount": 110}]

    modify_one(expenses_list, "remove 34")
    modify_one(expenses_list, "remove 10")

    assert(expenses_list == [{"apartment": 12, "type": "heating", "amount": 50},
                             {"apartment": 9, "type": "other", "amount": 400},
                             {"apartment": 9, "type": "other", "amount": 400},
                             {"apartment": 89, "type": "water", "amount": 110}])


def test_modify_two():
    """
    Tests modify_two() function
    """
    expenses_list = [{"apartment": 34, "type": "heating", "amount": 230},
                     {"apartment": 34, "type": "gas", "amount": 1099},
                     {"apartment": 12, "type": "heating", "amount": 50},
                     {"apartment": 9, "type": "other", "amount": 400},
                     {"apartment": 9, "type": "other", "amount": 400},
                     {"apartment": 89, "type": "water", "amount": 110}]

    modify_two(expenses_list, "remove 9 to 34")

    assert(expenses_list == [{"apartment": 89, "type": "water", "amount": 110}])


def test_modify_three():
    """
    Tests modify_three() function
    """
    expenses_list = [{"apartment": 34, "type": "heating", "amount": 230},
                     {"apartment": 34, "type": "gas", "amount": 1099},
                     {"apartment": 12, "type": "heating", "amount": 50},
                     {"apartment": 9, "type": "other", "amount": 400},
                     {"apartment": 9, "type": "other", "amount": 400},
                     {"apartment": 89, "type": "water", "amount": 110}]

    modify_three(expenses_list, "remove heating")
    modify_three(expenses_list, "remove water")

    assert(expenses_list == [{"apartment": 34, "type": "gas", "amount": 1099},
                             {"apartment": 9, "type": "other", "amount": 400},
                             {"apartment": 9, "type": "other", "amount": 400}])


def test_modify_four():
    """
    Tests modify_three() function
    """
    expenses_list = [{"apartment": 34, "type": "heating", "amount": 230},
                     {"apartment": 34, "type": "gas", "amount": 1099},
                     {"apartment": 12, "type": "heating", "amount": 50},
                     {"apartment": 9, "type": "other", "amount": 400},
                     {"apartment": 9, "type": "other", "amount": 400},
                     {"apartment": 89, "type": "water", "amount": 110}]

    modify_four(expenses_list, "replace 9 other with 135")
    modify_four(expenses_list, "replace 12 water with 400")

    assert(expenses_list == [{"apartment": 34, "type": "heating", "amount": 230},
                             {"apartment": 34, "type": "gas", "amount": 1099},
                             {"apartment": 12, "type": "heating", "amount": 50},
                             {"apartment": 9, "type": "other", "amount": 135},
                             {"apartment": 9, "type": "other", "amount": 135},
                             {"apartment": 89, "type": "water", "amount": 110}])


def test():
    """
    Main test function
    """
    test_get_value()
    test_get_expense()
    test_get_expenses_list()
    test_set_key()
    test_set_expense()
    test_set_expenses_list()
    test_add()
    test_modify_one()
    test_modify_two()
    test_modify_three()
    test_modify_four()


def start():
    """
    Main function
    """
    test()

    expenses_list = []
    init_expenses(get_expenses_list(expenses_list))

    while True:
        print_main_menu()

        # Regexes for the main menu input commands
        main_regexes = {
            "add <apartment> <type> <amount>": "add [1-9][0-9]* (water|heating|electricity|gas|other){1} [1-9][0-9]*",
            "modify": "modify",
            "display": "display",
            "exit": "exit"
        }

        # Input validation
        try:
            option = read_option(main_regexes)

            # First option
            if re.match(main_regexes["add <apartment> <type> <amount>"], option):
                add_expense(get_expenses_list(expenses_list), option)
            # Second option
            elif re.match(main_regexes["modify"], option):
                print_second_menu()

                modify_regexes = {
                    "remove <apartment>": "^remove [1-9][0-9]*$",
                    "remove <start apartment> to <end apartment>": "remove [1-9][0-9]* to [1-9][0-9]*",
                    "remove <type>": "remove (water|heating|electricity|gas|other){1}",
                    "replace <apartment> <type> with <amount>": "replace [1-9][0-9]* (water|heating|electricity|gas|other){1} with [1-9][0-9]*",
                    "back": "back"
                }
                second_option = read_option(modify_regexes)

                # Options of the second menu
                if re.match(modify_regexes["back"], second_option):
                    continue
                elif re.match(modify_regexes["remove <apartment>"], second_option):
                    modify_one(expenses_list, second_option)
                elif re.match(modify_regexes["remove <start apartment> to <end apartment>"], second_option):
                    modify_two(expenses_list, second_option)
                elif re.match(modify_regexes["remove <type>"], second_option):
                    modify_three(expenses_list, second_option)
                else:
                    modify_four(expenses_list, second_option)
            # Third option
            elif re.match(main_regexes["display"], option):
                print_third_menu()

                display_regexes = {
                    "list": "^list$",
                    "list <apartment>": "list [1-9][0-9]*",
                    "list [ < | = | > ] <amount>": "list (<|=|>){1} [1-9][0-9]*",
                    "back": "back"
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
            else:
                return
        except RegexError:
            print_error()


# Main call
start()
