import re
from services.ai import AI
from validators.errors import InputError, PlanePlacementError, AlreadyHitError, CellError
from validators.validator import Validator


class UI:
    def __init__(self, services):
        self.__setup = False
        self.__validator = Validator()
        self.__services = services
        self.__ai = AI(self.__services.repository.user_board)

    @staticmethod
    def ai_menu():
        print("""Welcome to Planes! Choose the difficulty of the game by typing its corresponding number:
    1. Easy
    2. Medium
    3. Hard """)

    def print_main_menu(self):
        if not self.__setup:
            print("""The computer has placed its planes. Now it's your turn! Place three planes on the board so we can start the game. 
A plane cannot overlap with another plane and it should not outrun your board.""")
        else:
            print("""Now try guessing the position of the cabin of one of the computer's planes!
    "air" means there is no plane situated on that cell;
    "hit" means there is a plane situated on that cell, but you didn't hit the cabin;
    "shot down" means there is a plane cabin situated on that cel; the plane is shot down.""")

    def print_user_board(self):
        print("")
        print("Your board: ")

        for i in range(self.__services.repository.user_board.height):
            for j in range(self.__services.repository.user_board.width):
                print(self.__services.repository.user_board.board[i][j], end="")
            print("")

        if self.__services.repository.user_board.number_of_planes < 3:
            print(f"Planes placed: {self.__services.repository.user_board.number_of_planes}/3")
        else:
            print(f"Planes shot down: {self.__services.repository.user_board.score}")
        print("")

    def print_computer_board(self):
        print("")
        print("Computer board: ")

        for i in range(self.__services.repository.computer_board.height):
            for j in range(self.__services.repository.computer_board.width):
                if self.__services.repository.computer_board.board[i][j] == "X":
                    print("X", end="")
                else:
                    print("0", end="")
            print("")

        print(f"Planes shot down: {self.__services.repository.computer_board.score}")
        print("")

    def print_computer_board_revealed(self):
        print("")
        print("Computer board: ")

        for i in range(self.__services.repository.computer_board.height):
            for j in range(self.__services.repository.computer_board.width):
                print(self.__services.repository.computer_board.board[i][j], end="")
            print("")

        print(f"Planes shot down: {self.__services.repository.computer_board.score}")
        print("")

    @staticmethod
    def ai_input():
        """
        Gets the difficulty of the game option.
        :return:
        """
        ipt = input(">>> ")

        if not re.match("^[1-3]{1}$", ipt):
            raise InputError
        else:
            return int(ipt)

    def place_plane(self):
        """
        Gets the input of the user in the "place a plane" function.
        :return: two integers and a string (the coordinates of the cabin and the orientation of the plane)
        """
        print("""Please input the coordinates of the plane (the row - in the range [0, 9] and the column - in the range[0, 9]) and 
its orientation ("up", "down", "left" or "right") each separated by one whitespace: """)
        ipt = input(">>> ")

        if len(ipt.split()) != 3:
            raise InputError

        x = ipt.split()[0]
        y = ipt.split()[1]
        orientation = ipt.split()[2]

        if not self.__validator.coordinate_regex(x) or not self.__validator.coordinate_regex(y) or not self.__validator.orientation_regex(orientation):
            raise InputError

        return int(x), int(y), orientation

    def hit(self):
        """
        Gets the input of the user in the "hit cell" option.
        :return: two integers (the coordinates of the cell to be hit)
        """
        print("""Please input the coordinates of the cell to attack, separated by one whitespace: """)
        ipt = input(">>> ")

        if len(ipt.split()) != 2:
            raise InputError

        x = ipt.split()[0]
        y = ipt.split()[1]

        if not self.__validator.coordinate_regex(x) or not self.__validator.coordinate_regex(y):
            raise InputError

        return int(x), int(y)

    @staticmethod
    def print_input_error():
        print("Invalid input.")

    @staticmethod
    def print_plane_placement_error():
        print("Invalid placement. A plane cannot overlap with another plane and it should not outrun your board.")

    @staticmethod
    def print_already_hit_error():
        print("You already hit that cell!")

    @staticmethod
    def print_cell_error():
        print("This cell does not exist.")

    @staticmethod
    def print_shot_status(message):
        print(f"Shot status: {message}")

    @staticmethod
    def print_computer_shot(x, y, message):
        print(f"Last cell hit by the computer: ({x}, {y}) - {message}")

    @staticmethod
    def print_user_win():
        print("Congrats! You shot down all the planes of the computer! This is how the boards looked like: ")

    @staticmethod
    def print_computer_win():
        print("Bad luck! The computer shot down all your planes. You lost! This is how the boards looked like: ")

    def start(self):
        """
        Main function
        """
        self.ai_menu()
        ai_option = self.ai_input()

        self.__services.generate_computer_board()

        # Used for delaying the computer move when the user input is invalid
        cont = 1
        cells = []
        queue = []

        while True:
            self.print_main_menu()
            if self.__services.repository.user_board.number_of_planes < 3:
                # The first part of the game implies the placement of the planes by the user.

                self.print_user_board()

                try:
                    x, y, orientation = self.place_plane()
                    plane = self.__services.repository.create_plane(x, y, orientation)
                    try:
                        self.__services.add_plane(plane, "user")
                    except PlanePlacementError:
                        self.print_plane_placement_error()
                except InputError:
                    self.print_input_error()
                if self.__services.repository.user_board.number_of_planes == 3:
                    self.__setup = True
            else:
                # The second part of the game implies attacks from both players.
                try:
                    if cont == 1:
                        if ai_option == 1:
                            x, y = self.__ai.easy(0, self.__services.repository.user_board.height - 1, 0, self.__services.repository.user_board.width - 1)
                            message = self.__services.hit_cell(x, y, "user")
                            self.print_user_board()
                            self.print_computer_shot(x, y, message)
                        elif ai_option == 2:
                            x, y = self.__ai.medium(cells)
                            message = self.__services.hit_cell(x, y, "user")
                            self.print_user_board()
                            self.print_computer_shot(x, y, message)
                        else:
                            x, y = self.__ai.advanced(queue)
                            message = self.__services.hit_cell(x, y, "user")
                            self.print_user_board()
                            self.print_computer_shot(x, y, message)

                        if self.__services.repository.user_board.score == 3:
                            self.print_computer_win()
                            self.print_user_board()
                            self.print_computer_board_revealed()
                            return

                        self.print_computer_board()

                    if cont == -1:
                        cont *= -1

                    x, y = self.hit()
                    try:
                        message = self.__services.hit_cell(x, y, "computer")
                        self.print_shot_status(message)

                        if self.__services.repository.computer_board.score == 3:
                            self.print_user_win()
                            self.print_user_board()
                            self.print_computer_board_revealed()
                            return

                    except AlreadyHitError:
                        self.print_already_hit_error()
                        cont *= -1
                    except CellError:
                        self.print_cell_error()
                        cont *= -1
                except InputError:
                    self.print_input_error()
                    cont *= -1
