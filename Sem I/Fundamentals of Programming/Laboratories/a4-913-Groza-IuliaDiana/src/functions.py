"""
  Program functionalities module
"""


import copy
import pytest


# Getters
def get_value(expense, key):
    return expense[key]


def get_expense(expense):
    return expense


def get_expenses_list(expenses_list):
    return expenses_list


def get_history(history):
    return history


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
    :param expenses_list: list of dictionaries
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

    set_expenses_list(get_expenses_list(expenses_list), get_expenses_list(new_expenses_list))


def add_expense(expenses_list, command, history):
    """
    We create an expense and then we append it to the list of expenses. Notice that duplicates are allowed.
    Each key of the expense dictionary is obtained parsing the command string using .split().
    :param expenses_list: list of dictionaries
    :param command: string
    :param history: list of lists of dictionaries
    """
    add_undo(get_history(history), get_expenses_list(expenses_list))

    expense = {}
    apartment = int(command.split()[1])
    type = command.split()[2]
    amount = int(command.split()[3])

    set_expense(expense, apartment, type, amount)

    get_expenses_list(expenses_list).append(get_expense(expense))


def modify_one(expenses_list, command, history):
    """
    Function that implements the "remove <apartment>" operation. If such expense is found, we replace the expanses list with a
    list that does not contain it (using concatenation).
    :param expenses_list: list of dictionaries
    :param command: string
    :param history: list of lists of dictionaries
    """
    add_undo(get_history(history), get_expenses_list(expenses_list))

    apartment = int(command.split()[1])

    ok = 0

    index = 0
    while index < len(get_expenses_list(expenses_list)):
        if get_value(get_expense(expenses_list[index]), "apartment") == apartment:
            ok += 1
            set_expenses_list(expenses_list, get_expenses_list(expenses_list[:index])+get_expenses_list(expenses_list[index+1:]))
        else:
            index += 1

    if not ok:
        raise IndexError


def modify_two(expenses_list, command, history):
    """
    Implements the "remove <start apartment> to <end apartment>" command. Similar to the first modify function.
    :param expenses_list: list of dictionaries
    :param command: string
    :param history: list of lists of dictionaries
    """
    add_undo(get_history(history), get_expenses_list(expenses_list))

    start_apartment = int(command.split()[1])
    end_apartment = int(command.split()[3])

    index = 0
    while index < len(get_expenses_list(expenses_list)):
        if start_apartment <= get_value(get_expense(expenses_list[index]), "apartment") <= end_apartment:
            set_expenses_list(expenses_list, get_expenses_list(expenses_list[:index])+get_expenses_list(expenses_list[index+1:]))
        else:
            index += 1


def modify_three(expenses_list, command, history):
    """
    Implements the "remove <type>" operation. Similar to the first modify function.
    :param expenses_list: list of dictionaries
    :param command: string
    :param history: list of lists of dictionaries
    """
    add_undo(get_history(history), get_expenses_list(expenses_list))

    type = command.split()[1]

    ok = 0

    index = 0
    while index < len(get_expenses_list(expenses_list)):
        if get_value(get_expense(expenses_list[index]), "type") == type:
            ok += 1
            set_expenses_list(expenses_list, get_expenses_list(expenses_list[:index])+get_expenses_list(expenses_list[index+1:]))
        else:
            index += 1

    if not ok:
        raise IndexError


def modify_four(expenses_list, command, history):
    """
    Implements the "replace <apartment> <type> with <amount>" operation. We modify the expense by setting a new amount value.
    :param expenses_list: list of dictionaries
    :param command: string
    :param history: list of lists of dictionaries
    """
    add_undo(get_history(history), get_expenses_list(expenses_list))

    apartment = int(command.split()[1])
    type = command.split()[2]
    amount = int(command.split()[4])

    ok = 0

    for index in range(len(get_expenses_list(expenses_list))):
        if get_value(get_expense(expenses_list[index]), "apartment") == apartment and get_value(get_expense(expenses_list[index]), "type") == type:
            ok += 1
            set_expense(get_expenses_list(expenses_list)[index], apartment, type, amount)

    if not ok:
        raise IndexError


def calculate_one(expenses_list, command, sum=0):
    """
    Implements the "sum <type>" command. We compute the total amount of all expenses having the given type. If there is no expense with this type, we print
    an appropriate message, using print_solution_sum() from the UI module.
    :param expenses_list: list of dictionaries
    :param command: string
    :param sum: integer initialized with 0
    :return: list that contains the sum and the type
    """
    type = command.split()[1]

    ok = 0

    for expense in get_expenses_list(expenses_list):
        if get_value(expense, "type") == type:
            ok += 1
            sum += get_value(expense, "amount")

    if not ok:
        raise IndexError

    return [sum, type]


def calculate_two(expenses_list, command):
    """
    Implements the "max <apartment>" operation. We calculate the maximum amount for each type in expenses from the given apartment. If there are no expenses for
    a certain type for the apartment, we print an appropriate message, using print_solution_max() from the UI module.
    :param expenses_list: list of dictionaries
    :param command: string
    :return: list that contains all the maximum values and the apartment value
    """
    apartment = int(command.split()[1])
    max_water = 0
    max_heating = 0
    max_electricity = 0
    max_gas = 0
    max_other = 0

    ok = 0

    for expense in get_expenses_list(expenses_list):
        if get_value(get_expense(expense), "apartment") == apartment:
            ok += 1
            if get_value(get_expense(expense), "type") == "water":
                max_water = max(max_water, get_value(get_expense(expense), "amount"))

            if get_value(get_expense(expense), "type") == "heating":
                max_heating = max(max_heating, get_value(get_expense(expense), "amount"))

            if get_value(get_expense(expense), "type") == "electricity":
                max_electricity = max(max_electricity, get_value(get_expense(expense), "amount"))

            if get_value(get_expense(expense), "type") == "gas":
                max_gas = max(max_gas, get_value(get_expense(expense), "amount"))

            if get_value(get_expense(expense), "type") == "other":
                max_other = max(max_other, get_value(get_expense(expense), "amount"))

    if not ok:
        raise IndexError

    return [max_water, max_heating, max_electricity, max_gas, max_other]


def calculate_three(expenses_list):
    """
    Implements the "sort apartment" command. We iterate through the expenses and update the total amount for each apartment. Finally, we sort the apartments and return
    the sorted dictionary.
    :param expenses_list: list of dictionaries
    :return: list of a dictionary's keys
    """
    apartments = {}

    for expense in get_expenses_list(expenses_list):
        if get_value(get_expense(expense), "apartment") in apartments.keys():
            apartments[get_value(get_expense(expense), "apartment")] += get_value(get_expense(expense), "amount")
        else:
            apartments.update({get_value(get_expense(expense), "apartment"): get_value(get_expense(expense), "amount")})

    # Sorting the dictionary's keys by value
    sorted_apartments = {}
    sorted_keys = sorted(apartments, key=apartments.get)

    for key in sorted_keys:
        sorted_apartments[key] = apartments[key]

    return sorted_apartments


def calculate_four(expenses_list):
    """
    Implements the "sort type" command. We iterate through the expenses and update the total amount for each expense type. Finally, we sort the types and return
    the sorted dictionary.
    :param expenses_list: list of dictionaries
    :return: dictionary
    """
    types = {"water": 0, "heating": 0, "electricity": 0, "gas": 0, "other": 0}

    for expense in get_expenses_list(expenses_list):
        types[get_value(get_expense(expense), "type")] += get_value(get_expense(expense), "amount")

    # Sorting the dictionary's keys by value
    sorted_types = {}
    sorted_keys = sorted(types, key=types.get)

    for key in sorted_keys:
        sorted_types[key] = types[key]

    return sorted_types


def filter_one(expenses_list, command, history):
    """
    Implementation of "filter <type>" operation. We build a new expenses list that contains only expenses of type <type> and then replace the initial expenses list with it.
    :param expenses_list: list of dictionaries
    :param command: string
    :param history: list of lists of dictionaries
    """
    add_undo(get_history(history), get_expenses_list(expenses_list))

    type = command.split()[1]
    new_expenses_list = []

    for expense in get_expenses_list(expenses_list):
        if get_value(get_expense(expense), "type") == type:
            get_expenses_list(new_expenses_list).append(get_expense(expense))

    set_expenses_list(get_expenses_list(expenses_list), get_expenses_list(new_expenses_list))


def filter_two(expenses_list, command, history):
    """
    Implementation of "filter <value>" operation. We build a new expenses list that contains only expenses smaller than <amount> and then replace the initial expenses list with it.
    :param expenses_list: list of dictionaries
    :param command: string
    :param history: list of lists of dictionaries
    """
    add_undo(get_history(history), get_expenses_list(expenses_list))

    amount = int(command.split()[1])
    new_expenses_list = []

    for expense in get_expenses_list(expenses_list):
        if get_value(get_expense(expense), "amount") < amount:
            get_expenses_list(new_expenses_list).append(get_expense(expense))

    set_expenses_list(get_expenses_list(expenses_list), get_expenses_list(new_expenses_list))


def add_undo(history, expenses_list):
    """
    Adds the version of the expenses list before a modification to the history.
    :param history: list of lists of dictionaries
    :param expenses_list: list of dictionaries
    """
    get_history(history).append(copy.deepcopy(get_expenses_list(expenses_list)))


def undo(expenses_list, history):
    """
    Implementation of "undo" operation. We recover the last version of the list and eliminate it from the "history" stack.
    :param expenses_list: list of dictionaries
    :param history: list of lists of dictionaries
    """
    if len(history) == 0:
        raise IndexError
    set_expenses_list(expenses_list, get_history(history).pop())


# Tests
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


def test_get_history():
    history = [[{"apartment": 34, "type": "heating", "amount": 230},
                {"apartment": 34, "type": "gas", "amount": 1099},
                {"apartment": 12, "type": "heating", "amount": 50},
                {"apartment": 9, "type": "other", "amount": 400}],
               [{"apartment": 34, "type": "heating", "amount": 230},
                {"apartment": 34, "type": "gas", "amount": 1099},
                {"apartment": 12, "type": "heating", "amount": 50},
                {"apartment": 9, "type": "other", "amount": 1000}]]

    assert(get_history(history) == history)


def test_set_key():
    expense = {
        "apartment": 234,
        "amount": 1000
    }

    set_key(get_expense(expense), "apartment", 250)
    set_key(get_expense(expense), "type", "other")

    assert(get_expense(expense) == {
        "apartment": 250,
        "type": "other",
        "amount": 1000
    })


def test_set_expense():
    expense = {
        "apartment": 234,
        "amount": 1000
    }

    set_expense(get_expense(expense), 250, "water", 1300)

    assert(get_expense(expense) == {
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

    set_expenses_list(get_expenses_list(expenses_list), get_expenses_list(new_expenses_list))

    assert(get_expenses_list(expenses_list) == get_expenses_list(new_expenses_list))


def test_init_expenses():
    """
    Tests init_expenses() function.
    """
    expenses_list = [{"apartment": 25, "type": "water", "amount": 1340},
                     {"apartment": 30, "type": "other", "amount": 29}]

    init_expenses(get_expenses_list(expenses_list))

    assert(get_expenses_list(expenses_list) == [{"apartment": 25, "type": "other", "amount": 200},
                                                {"apartment": 1, "type": "heating", "amount": 400},
                                                {"apartment": 100, "type": "heating", "amount": 50},
                                                {"apartment": 25, "type": "gas", "amount": 99},
                                                {"apartment": 70, "type": "electricity", "amount": 1320},
                                                {"apartment": 25, "type": "other", "amount": 322},
                                                {"apartment": 100, "type": "gas", "amount": 50},
                                                {"apartment": 29, "type": "other", "amount": 100},
                                                {"apartment": 99, "type": "water", "amount": 200},
                                                {"apartment": 70, "type": "water", "amount": 200}])


def test_add():
    """
    Tests add_expense() function.
    """
    expenses_list = [{"apartment": 34, "type": "heating", "amount": 230}, {"apartment": 34, "type": "gas", "amount": 1099},
                     {"apartment": 12, "type": "heating", "amount": 50}, {"apartment": 9, "type": "other", "amount": 400}]

    mock_history = []

    add_expense(get_expenses_list(expenses_list), "add 9 other 400", get_history(mock_history))
    add_expense(get_expenses_list(expenses_list), "add 89 water 110", get_history(mock_history))

    assert(get_expenses_list(expenses_list) == [{"apartment": 34, "type": "heating", "amount": 230},
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

    mock_history = []

    modify_one(get_expenses_list(expenses_list), "remove 34", get_history(mock_history))
    with pytest.raises(IndexError):
        modify_one(get_expenses_list(expenses_list), "remove 10", get_history(mock_history))

    assert(get_expenses_list(expenses_list) == [{"apartment": 12, "type": "heating", "amount": 50},
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

    mock_history = []

    modify_two(get_expenses_list(expenses_list), "remove 9 to 34", get_history(mock_history))

    assert(get_expenses_list(expenses_list) == [{"apartment": 89, "type": "water", "amount": 110}])


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

    mock_history = []

    modify_three(get_expenses_list(expenses_list), "remove heating", get_history(mock_history))
    modify_three(get_expenses_list(expenses_list), "remove water", get_history(mock_history))
    with pytest.raises(IndexError):
        modify_three(get_expenses_list(expenses_list), "remove electricity", get_history(mock_history))

    assert(get_expenses_list(expenses_list) == [{"apartment": 34, "type": "gas", "amount": 1099},
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

    mock_history = []

    modify_four(get_expenses_list(expenses_list), "replace 9 other with 135", get_history(mock_history))
    with pytest.raises(IndexError):
        modify_four(get_expenses_list(expenses_list), "replace 23 gas with 6969", get_history(mock_history))

    assert(get_expenses_list(expenses_list) == [{"apartment": 34, "type": "heating", "amount": 230},
                                                {"apartment": 34, "type": "gas", "amount": 1099},
                                                {"apartment": 12, "type": "heating", "amount": 50},
                                                {"apartment": 9, "type": "other", "amount": 135},
                                                {"apartment": 9, "type": "other", "amount": 135},
                                                {"apartment": 89, "type": "water", "amount": 110}])


def test_calculate_one():
    """
    Tests calculate_one() function
    """
    expenses_list = [{"apartment": 34, "type": "heating", "amount": 230},
                     {"apartment": 34, "type": "gas", "amount": 1099},
                     {"apartment": 12, "type": "heating", "amount": 50},
                     {"apartment": 9, "type": "other", "amount": 400},
                     {"apartment": 9, "type": "other", "amount": 400},
                     {"apartment": 89, "type": "water", "amount": 110}]

    with pytest.raises(IndexError):
        calculate_one(get_expenses_list(expenses_list), "sum electricity")

    assert(calculate_one(get_expenses_list(expenses_list), "sum heating") == [280, "heating"])
    assert (calculate_one(get_expenses_list(expenses_list), "sum water") == [110, "water"])


def test_calculate_two():
    """
    Tests calculate_two() function
    """
    expenses_list = [{"apartment": 34, "type": "heating", "amount": 230},
                     {"apartment": 34, "type": "gas", "amount": 1099},
                     {"apartment": 12, "type": "heating", "amount": 50},
                     {"apartment": 9, "type": "other", "amount": 400},
                     {"apartment": 9, "type": "other", "amount": 400},
                     {"apartment": 89, "type": "water", "amount": 110},
                     {"apartment": 34, "type": "heating", "amount": 499},
                     {"apartment": 34, "type": "heating", "amount": 49},
                     {"apartment": 34, "type": "other", "amount": 280}]

    with pytest.raises(IndexError):
        calculate_two(get_expenses_list(expenses_list), "max 1334")

    assert(calculate_two(get_expenses_list(expenses_list), "max 34") == [0, 499, 0, 1099, 280])


def test_calculate_three():
    """
    Tests the calculate_three() function.
    """
    expenses_list = [{"apartment": 34, "type": "heating", "amount": 230},
                     {"apartment": 34, "type": "gas", "amount": 1099},
                     {"apartment": 12, "type": "heating", "amount": 50},
                     {"apartment": 9, "type": "other", "amount": 400},
                     {"apartment": 9, "type": "other", "amount": 400},
                     {"apartment": 89, "type": "water", "amount": 110}]

    assert(calculate_three(get_expenses_list(expenses_list)) == {12: 50, 89: 110, 9: 800, 34: 1329})


def test_calculate_four():
    """
    Tests calculate_four() function
    """
    expenses_list = [{"apartment": 34, "type": "heating", "amount": 230},
                     {"apartment": 34, "type": "gas", "amount": 1099},
                     {"apartment": 12, "type": "heating", "amount": 50},
                     {"apartment": 9, "type": "other", "amount": 400},
                     {"apartment": 9, "type": "other", "amount": 400},
                     {"apartment": 89, "type": "water", "amount": 110}]

    assert (calculate_four(get_expenses_list(expenses_list)) == {"electricity": 0, "water": 110, "heating": 280, "other": 800, "gas": 1099})


def test_filter_one():
    """
    Tests filter_one() function
    """
    expenses_list = [{"apartment": 34, "type": "heating", "amount": 230},
                     {"apartment": 34, "type": "gas", "amount": 1099},
                     {"apartment": 12, "type": "heating", "amount": 50},
                     {"apartment": 9, "type": "other", "amount": 400},
                     {"apartment": 9, "type": "other", "amount": 400},
                     {"apartment": 89, "type": "heating", "amount": 110}]

    mock_history = []

    filter_one(get_expenses_list(expenses_list), "sort heating", get_history(mock_history))

    assert(get_expenses_list(expenses_list) == [{"apartment": 34, "type": "heating", "amount": 230},
                                                {"apartment": 12, "type": "heating", "amount": 50},
                                                {"apartment": 89, "type": "heating", "amount": 110}])

    set_expenses_list(expenses_list, [{"apartment": 34, "type": "heating", "amount": 230},
                                      {"apartment": 34, "type": "gas", "amount": 1099},
                                      {"apartment": 12, "type": "heating", "amount": 50},
                                      {"apartment": 9, "type": "other", "amount": 400},
                                      {"apartment": 9, "type": "other", "amount": 400},
                                      {"apartment": 89, "type": "heating", "amount": 110}])

    filter_one(get_expenses_list(expenses_list), "sort electricity", get_history(mock_history))

    assert(get_expenses_list(expenses_list) == [])


def test_filter_two():
    """
    Tests filter_two() function
    """
    expenses_list = [{"apartment": 34, "type": "heating", "amount": 230},
                     {"apartment": 34, "type": "gas", "amount": 1099},
                     {"apartment": 12, "type": "heating", "amount": 50},
                     {"apartment": 9, "type": "other", "amount": 400},
                     {"apartment": 9, "type": "other", "amount": 400},
                     {"apartment": 89, "type": "heating", "amount": 110}]

    mock_history = []

    filter_two(get_expenses_list(expenses_list), "sort 400", get_history(mock_history))

    assert(get_expenses_list(expenses_list) == [{"apartment": 34, "type": "heating", "amount": 230},
                                                {"apartment": 12, "type": "heating", "amount": 50},
                                                {"apartment": 89, "type": "heating", "amount": 110}])

    set_expenses_list(expenses_list, [{"apartment": 34, "type": "heating", "amount": 230},
                                      {"apartment": 34, "type": "gas", "amount": 1099},
                                      {"apartment": 12, "type": "heating", "amount": 50},
                                      {"apartment": 9, "type": "other", "amount": 400},
                                      {"apartment": 9, "type": "other", "amount": 400},
                                      {"apartment": 89, "type": "heating", "amount": 110}])

    filter_two(get_expenses_list(expenses_list), "sort 50", get_history(mock_history))

    assert(get_expenses_list(expenses_list) == [])


def test_undo():
    """
    Tests undo() function
    """
    expenses_list = [{"apartment": 34, "type": "heating", "amount": 230},
                     {"apartment": 34, "type": "gas", "amount": 1099},
                     {"apartment": 12, "type": "heating", "amount": 50},
                     {"apartment": 9, "type": "other", "amount": 400},
                     {"apartment": 9, "type": "other", "amount": 400},
                     {"apartment": 89, "type": "heating", "amount": 110}]

    mock_history = []

    add_expense(get_expenses_list(expenses_list), "add 50 electricity 230", get_history(mock_history))
    modify_four(get_expenses_list(expenses_list), "replace 12 heating with 150", get_history(mock_history))
    filter_two(get_expenses_list(expenses_list), "filter 1000", get_history(mock_history))

    undo(get_expenses_list(expenses_list), get_history(mock_history))

    assert(get_expenses_list(expenses_list) == [{"apartment": 34, "type": "heating", "amount": 230},
                                                {"apartment": 34, "type": "gas", "amount": 1099},
                                                {"apartment": 12, "type": "heating", "amount": 150},
                                                {"apartment": 9, "type": "other", "amount": 400},
                                                {"apartment": 9, "type": "other", "amount": 400},
                                                {"apartment": 89, "type": "heating", "amount": 110},
                                                {"apartment": 50, "type": "electricity", "amount": 230}])

    undo(get_expenses_list(expenses_list), get_history(mock_history))

    assert(get_expenses_list(expenses_list) == [{"apartment": 34, "type": "heating", "amount": 230},
                                                {"apartment": 34, "type": "gas", "amount": 1099},
                                                {"apartment": 12, "type": "heating", "amount": 50},
                                                {"apartment": 9, "type": "other", "amount": 400},
                                                {"apartment": 9, "type": "other", "amount": 400},
                                                {"apartment": 89, "type": "heating", "amount": 110},
                                                {"apartment": 50, "type": "electricity", "amount": 230}])

    undo(get_expenses_list(expenses_list), get_history(mock_history))

    assert(get_expenses_list(expenses_list) == [{"apartment": 34, "type": "heating", "amount": 230},
                                                {"apartment": 34, "type": "gas", "amount": 1099},
                                                {"apartment": 12, "type": "heating", "amount": 50},
                                                {"apartment": 9, "type": "other", "amount": 400},
                                                {"apartment": 9, "type": "other", "amount": 400},
                                                {"apartment": 89, "type": "heating", "amount": 110}])

    with pytest.raises(IndexError):
        undo(get_expenses_list(expenses_list), get_history(mock_history))


def test():
    """
    Main test function
    """
    test_get_value()
    test_get_expense()
    test_get_expenses_list()
    test_get_history()
    test_set_key()
    test_set_expense()
    test_set_expenses_list()
    test_init_expenses()
    test_add()
    test_modify_one()
    test_modify_two()
    test_modify_three()
    test_modify_four()
    test_calculate_one()
    test_calculate_two()
    test_calculate_three()
    test_calculate_four()
    test_filter_one()
    test_filter_two()
    test_undo()
