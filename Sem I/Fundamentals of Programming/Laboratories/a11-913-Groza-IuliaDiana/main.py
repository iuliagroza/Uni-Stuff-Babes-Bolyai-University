import re
from domain.board_domain import Board
from gui.main_gui import GUI
from repository.repository import Repository
from services.services import Services
from ui.ui import UI
from validators.errors import InputError


def ui_option():
    print("""Choose your user interface option by typing its corresponding number: 
    1. Console
    2. GUI""")
    ipt = input(">>> ")

    try:
        if not re.match("^[1-2]{1}$", ipt):
            raise InputError
        else:
            return int(ipt)
    except InputError:
        print("Invalid option.")


if __name__ == "__main__":
    """
    Main call
    """
    while True:
        ui_input = ui_option()

        if not ui_input is None:
            break

    computer_board = Board(10, 10, "computer")
    user_board = Board(10, 10, "user")
    repository = Repository(computer_board, user_board)
    services = Services(repository)
    if ui_input == 1:
        ui = UI(services)
        ui.start()
    else:
        ui = GUI()
        ui.start()
