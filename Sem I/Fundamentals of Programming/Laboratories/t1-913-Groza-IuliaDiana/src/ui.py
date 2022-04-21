import re
from functions import find_codes, find_runners, get_number


def print_menu():
    print("""Welcome to Code Runners! The computer has made its guess. Now it's your turn! Enter a number of 4 distinct digits. 
    You should guess computer's number in less than 60 seconds, otherwise you lose!""")


def enter_number():
    number = input(">>> ")
    if not re.match("[1-9]{1}[0-9]{3}", get_number(number)):
        raise ValueError
    if get_number(number) != "8086":
        for i in range(4):
            for j in range(4):
                if number[i] == number[j] and i != j:
                    raise ValueError
    return get_number(number)


def print_input_error():
    print("You've entered an invalid number. Computer wins!")


def print_codes_and_runners(computer_num, user_num):
    print(f"Your number has {find_codes(get_number(computer_num), get_number(user_num))} codes and {find_runners(get_number(computer_num), get_number(user_num))} runners.")


def cheat_code(user_num, computer_num):
    if get_number(user_num) == 8086:
        print(f"Cheat enabled. Computer's number is: {get_number(computer_num)}.")


def print_win_message():
    print("Congratulations! You won!")


def print_lost_message():
    print("You ran out of time! Computer wins!")
