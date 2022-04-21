#
# Write the implementation for A2 in this file
# Functionalities for task 3: 6 (Distinct numbers) and 10 (Sum of its elements is 10+10i)
#


import random
import re


# UI section
# (write all functions that have input or print statements here). 
# Ideally, this section should not contain any calculations relevant to program functionalities


class RegexError(Exception):
    # Raised when a string doesn't match a given regex
    pass


# Prints the menu in the console.
def print_menu():
    print("""Please select an option by typing its corresponding number:
             1. Read a list of complex numbers. Write each element on a new line, in a "z = a + bi" form. Enter 0 when the input is done.
             2. Display the entire list of numbers on the console.
             3. Display on the console the longest sequence of distinct numbers.
             4. Display on the console the longest sequence whose elements' sum is 10+10i.
             5. Exit
    """)


# Reads the user's option. Raises an error if the option is not valid (1, 2, 3, 4 or 5).
def get_input():
    try:
        option = int(input(">>> "))
        valid_options = [1, 2, 3, 4, 5]
        if option not in valid_options:
            raise ValueError
        return option
    except ValueError:  # ValueError + option not from [1, 5]
        print("Invalid input.")


# Reads a list of complex numbers up to 0. If the list is valid and not empty, it overwrites the current list.
def read_list(numbers_list):
    auxiliary_list = []

    while True:
        try:
            element_to_parse = input("z = ")

            if element_to_parse == "0":  # We reached the end of the list.
                break

            # Regex that checks if input is in "z = a + bi" form.
            if not re.match("-?[0-9]+ \+ -?[0-9]+i", element_to_parse):
                raise RegexError

            real_part = int(element_to_parse.split()[0])
            imaginary_part = int(element_to_parse.split()[2].strip("i"))
            auxiliary_list.append((real_part, imaginary_part))
        except RegexError:
            print("Invalid input.")

    if auxiliary_list:  # If the list is not empty we overwrite the current list.
        numbers_list[:] = auxiliary_list[:]
    else:
        print("Your list is empty.")


# Prints the list as [a1 + b1i, a2 + b2i, ..., an + bni].
def print_list(numbers_list):
    if len(numbers_list) == 1:  # The list contains one element
        print("[" + str(numbers_list[0][0]) + " + " + str(numbers_list[0][1]) + "i]")
    else:
        for i in range(len(numbers_list)):
            if i == 0:  # First element of the list
                print("[" + str(numbers_list[i][0]) + " + " + str(numbers_list[i][1]) + "i, ", end="")
            elif i == len(numbers_list) - 1:  # Last element of the list
                print(str(numbers_list[i][0]) + " + " + str(numbers_list[i][1]) + "i]")
            else:  # Middle element
                print(str(numbers_list[i][0]) + " + " + str(numbers_list[i][1]) + "i, ", end="")


def print_solution(numbers_list, solved=True):
    if solved:
        print_list(get_numbers_list(numbers_list))
    else:
        print("There is no such sequence")


# Function section
# (write all non-UI functions in this section)
# There should be no print or input statements below this comment
# Each function should do one thing only
# Functions communicate using input parameters and their return values

# print('Hello A2'!) -> prints aren't allowed here!


# Getters
def get_numbers_list(numbers_list):
    return numbers_list


def get_complex_number(complex_number):
    return complex_number


def get_real_part(x_tuple):
    return x_tuple[0]


def get_imaginary_part(x_tuple):
    return x_tuple[1]


# Setters
def set_numbers_list(numbers_list, new_numbers_list):
    numbers_list[:] = new_numbers_list[:]


def set_real_part(x_tuple, new_real_part):
    x_tuple[0] = new_real_part


def set_imaginary_part(x_tuple, new_imaginary_part):
    x_tuple[1] = new_imaginary_part


# Creates a predefined list with 10 randomized elements x, where |x| <= 100*sqrt(2).
def generate_random_list():
    numbers_list = []

    for i in range(10):
        real_part = random.randint(-100, 100)
        imaginary_part = random.randint(-100, 100)
        numbers_list.append((real_part, imaginary_part))

    return get_numbers_list(numbers_list)


# Displays the longest subsequence of distinct numbers on the console using Kadane's algorithm.
# We introduce numbers into a set.
# When we find a duplicate, we remove the subsequence up to it included and update the solution if needed.
# Runtime: O(n)
def distinct_numbers_sequence(numbers_list):
    sol_len = -1  # The starting index of the sequence
    sol_start = -1  # The length of the sequence

    s = set()  # We use a set to store the distinct values.

    for i in range(len(numbers_list)):
        while numbers_list[i] in s:  # We discard all the numbers from the start of the set to the duplicate of i
            s.discard(numbers_list[i - len(s)])

        s.add(numbers_list[i])

        if len(s) > sol_len:  # We update the solution.
            sol_len = len(s)
            sol_start = i - sol_len + 1

    return get_numbers_list(numbers_list[sol_start:sol_start + sol_len])


# Prints the longest sequence whose elements' sum is 10+10i. Outputs a message if there is no such sequence.
# Runtime: O(n^2) amortized
def module_sequence(numbers_list):
    sol_len = -1  # The starting index of the sequence
    sol_start = -1  # The length of the sequence

    for i in range(len(numbers_list)):
        real_sum = numbers_list[i][0]
        imaginary_sum = numbers_list[i][1]

        j = i + 1
        while j < len(numbers_list) and (real_sum != 10 and imaginary_sum != 10):
            real_sum += numbers_list[j][0]
            imaginary_sum += numbers_list[j][1]
            j += 1
        j -= 1

        if real_sum == 10 and imaginary_sum == 10 and j - i + 1 > sol_len:  # We found a solution
            sol_len = j - i + 1
            sol_start = i

    if sol_len == -1:  # If there is no solution
        return []
    else:
        return get_numbers_list(numbers_list[sol_start:sol_start + sol_len])


# Testing function for functionalities
def test():
    assert (distinct_numbers_sequence([(3, 2), (1, 1), (2, -2), (233, 1)]) == [(3, 2), (1, 1), (2, -2), (233, 1)])
    assert (distinct_numbers_sequence([(3, -24), (3, -24), (3, -24), (3, -24), (3, -24)]) == [(3, -24)])
    assert (distinct_numbers_sequence([(3, -24), (0, 0), (1, 1), (3, -23), (-3, 24)]) == [(3, -24), (0, 0), (1, 1),
                                                                                          (3, -23), (-3, 24)])
    assert (distinct_numbers_sequence([(3, -24), (2, 9), (3, -24), (3, -24), (17, 1)]) == [(3, -24), (2, 9)])

    assert (module_sequence([(1, 1), (2, 2), (3, 3), (5, 5), (3, 4)]) == [(2, 2), (3, 3), (5, 5)])
    assert (module_sequence([(1, 1), (2, 2), (3, 3), (1, 2), (3, 2)]) == [(1, 1), (2, 2), (3, 3), (1, 2), (3, 2)])
    assert (module_sequence([(1, 1), (2, 2), (3, 3), (-1, -2), (3, 4)]) == [])
    assert (module_sequence([(1, 1), (2, 7), (8, 3), (5, 5), (3, 4), (1, 6), (3, 2), (6, 2)]) == [(1, 6), (3, 2),
                                                                                                  (6, 2)])
    assert (module_sequence([(1, 1), (2, 7), (8, 3), (5, 5), (3, 4), (1, 6), (9, 4)]) == [(2, 7), (8, 3)])


# Main function
def start():
    test()
    numbers_list = generate_random_list()

    while True:
        print_menu()
        option = get_input()

        if option == 1:
            read_list(numbers_list)
        elif option == 2:
            print_list(numbers_list)
        elif option == 3:
            sol = distinct_numbers_sequence(numbers_list)
            print_solution(sol)
        elif option == 4:
            sol = module_sequence(numbers_list)
            if not sol:
                print_solution(sol, False)
            else:
                print_solution(sol)
        elif option == 5:
            return


# Main call
start()
