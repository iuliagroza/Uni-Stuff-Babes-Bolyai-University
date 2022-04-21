import random


# Getters
def get_number(number):
    return number


def generate_secret_number():
    """
    Generates the secret number chosen by the computer. The first digit is in range [1-9] and the rest of the digits
    are from [0-9] and they are also distinct. Digits are generated until a distinct digit is found. We work on strings
    and finally convert the number.
    :return: integer
    """
    number = ""
    digit = random.randint(1, 9)
    number += str(digit)
    for i in range(3):
        digit = random.randint(0, 9)
        while str(digit) in number:
            digit = random.randint(0, 9)
        number += str(digit)
    return int(number)


def find_codes(computer_num, user_num):
    codes = 0

    for i in range(4):
        if str(get_number(computer_num))[i] == str(get_number(user_num))[i]:
            codes += 1

    return codes


def find_runners(computer_num, user_num):
    runners = 0
    for i in range(4):
        for j in range(4):
            if str(get_number(computer_num))[i] == str(get_number(user_num))[j] and i != j:
                runners += 1
    return runners
