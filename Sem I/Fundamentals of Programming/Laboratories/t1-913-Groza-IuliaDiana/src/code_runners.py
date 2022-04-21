"""
Implement the solution here. 
You may add other source files.
Make sure you commit & push the source code before the end of the test.

Solutions using user-defined classes will not be graded.
"""
import time
from functions import generate_secret_number, find_codes, get_number
from ui import enter_number, print_input_error, print_codes_and_runners, cheat_code, print_win_message, print_lost_message, print_menu


def start():
    computer_number = int(generate_secret_number())
    print_menu()

    start_time = time.time()

    while 1:
        try:
            user_number = int(enter_number())
            cheat_code(get_number(user_number), get_number(computer_number))
        except ValueError:
            print_input_error()
            return

        if time.time() - start_time > 59:
            print_lost_message()
            return

        print_codes_and_runners(get_number(computer_number), get_number(user_number))
        if find_codes(get_number(computer_number), get_number(user_number)) == 4:
            print_win_message()
            return


# Main call
start()
