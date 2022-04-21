"""
Main call
"""
from settings import Settings
import re


def print_storage_menu():
    print("""Do you want to continue the previous game?""")
    print("Yes")
    print("No")


def get_storage_input():
    ipt = input(">>> ")
    try:
        if not re.match("^Yes|No$", ipt):
            raise IndexError
    except IndexError:
        print("Invalid input.")
    return ipt


if __name__ == "__main__":
    Settings().ui.start()
