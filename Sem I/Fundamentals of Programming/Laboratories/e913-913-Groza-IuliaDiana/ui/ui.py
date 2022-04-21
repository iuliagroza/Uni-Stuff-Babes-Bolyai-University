from validators.errors import InputError, PlacementError, MovementError
from validators.validator import Validator
import re


class UI:
    def __init__(self, services):
        self.__services = services
        self.__validator = Validator()

    @staticmethod
    def print_start_menu():
        print("""Welcome to Achi! The Placement phase has started and the board is displayed below.
Now it's your turn to make the move. The computer will place one piece on the board next.""")

    def print_board(self):
        for row in self.__services.repo.board.board:
            for element in row:
                print(element, end="")
            print("")

    def get_input(self):
        print("Please type in the coordinates of the cell you want to place your piece separated by exactly one whitespace (0-indexed).")
        ipt = input(">>> ")
        if not self.__validator.validate_input(ipt):
            raise InputError()

        x = int(ipt.split()[0])
        y = int(ipt.split()[1])

        return x, y

    def get_movement_input(self):
        print("Please type in the coordinates of the cell of the piece you want to move and the coordinates of the destination cell separated by exactly one whitespace (0-indexed).")
        ipt = input(">>> ")
        if not self.__validator.validate_movement_input(ipt):
            raise InputError()

        x1 = int(ipt.split()[0])
        y1 = int(ipt.split()[1])
        x2 = int(ipt.split()[2])
        y2 = int(ipt.split()[3])

        return x1, y1, x2, y2

    @staticmethod
    def print_input_error():
        print("Invalid input.")

    @staticmethod
    def print_placement_error():
        print("Invalid placement.")

    @staticmethod
    def print_movement_error():
        print("Invalid movement.")

    @staticmethod
    def print_computer_won():
        print("That's too bad! The computer won!")

    @staticmethod
    def print_user_won():
        print("Congratulations! You won!")

    @staticmethod
    def print_movement_menu():
        print("""Now we continue with the Movement phase! You can only move a piece on a square that is adjacent. "
Now it's your turn!. The computer will make its turn right after you.""")

    @staticmethod
    def print_storage_menu():
        print("""Do you want to continue the previous game?""")
        print("Yes")
        print("No")

    @staticmethod
    def get_storage_input():
        ipt = input(">>> ")
        if not re.match("^Yes|No$", ipt):
            raise InputError
        return ipt

    def start(self):
        self.print_start_menu()

        number_of_exes = 0
        number_of_zeros = 0

        while number_of_exes < 4 and number_of_zeros < 4:
            self.print_board()
            try:
                x, y = self.get_input()
                self.__services.add_piece(x, y, 'X')
                number_of_exes += 1
                self.__services.computer_placement(self.__services.repo.board.board)
                number_of_zeros += 1
            except PlacementError:
                self.print_placement_error()
            except InputError:
                self.print_input_error()

        if self.__services.check_win_computer(self.__services.repo.board.board):
            self.print_computer_won()
        elif self.__services.check_win_user(self.__services.repo.board.board):
            self.print_user_won()
        else:
            while True:
                self.print_movement_menu()
                self.print_board()

                try:
                    x1, y1, x2, y2 = self.get_movement_input()
                    self.__services.move_piece(x1, y1, x2, y2, 'X')

                    self.__services.computer_movement(self.__services.repo.board.board)
                except InputError:
                    self.print_input_error()
                except MovementError:
                    self.print_movement_error()

                if self.__services.check_win_computer(self.__services.repo.board.board):
                    self.print_computer_won()
                    break
                elif self.__services.check_win_user(self.__services.repo.board.board):
                    self.print_user_won()
                    break
