import random

from validators.errors import PlacementError, MovementError
from validators.validator import Validator


class Services:
    def __init__(self, repo):
        self.__repo = repo
        self.__validator = Validator()

    @property
    def repo(self):
        return self.__repo

    def add_piece(self, x, y, type):
        """
        Adds a piece on the board. A placement is not valid when the cell is already occupied or it outruns the board.
        :param x: integer from [0-2]
        :param y: integer from [0-2]
        :param type: character
        """
        if not self.__validator.validate_cell_bounds(x, y, self.__repo.board.board):
            raise PlacementError()

        self.__repo.add_piece(x, y, type)

    def move_piece(self, x1, y1, x2, y2, type):
        """
        Moves a piece on the board. A movement is invalid when the destination cell is already occupied or it outruns the board
        or when the cells are not adjacent.
        :param x1: integer from [0-2]
        :param y1: integer from [0-2]
        :param x2: integer from [0-2]
        :param y2: integer from [0-2]
        :param type: character
        """
        if not self.__validator.validate_cell_bounds(x2, y2, self.__repo.board.board):
            raise MovementError()

        if not self.__validator.validate_adjacency(x1, y1, x2, y2):
            raise MovementError()

        self.__repo.move_piece(x1, y1, x2, y2, type)

    @staticmethod
    def check_win_computer(board):
        """
        Check if the computer won (any line, column or diagonal is fully filled with 'O').
        :param board: binary matrix
        :return: boolean
        """
        if board[0][0] == board[1][1] == board[2][2] == 'O':
            return True
        if board[0][2] == board[1][1] == board[2][0] == 'O':
            return True
        for i in range(3):
            if board[0][i] == board[1][i] == board[2][i] == 'O':
                return True
            if board[i][0] == board[i][1] == board[i][2] == 'O':
                return True
        return False

    @staticmethod
    def check_win_user(board):
        """
        Check if the user won (any line, column or diagonal is fully filled with 'X').
        :param board: matrix of chars
        :return: boolean
        """
        if board[0][0] == board[1][1] == board[2][2] == 'X':
            return True
        if board[0][2] == board[1][1] == board[2][0] == 'X':
            return True
        for i in range(3):
            if board[0][i] == board[1][i] == board[2][i] == 'X':
                return True
            if board[i][0] == board[i][1] == board[i][2] == 'X':
                return True
        return False

    def computer_placement(self, board):
        """
        Function that programmatically generates a placement of the computer.
        If the user is at one step of winning, the computer blocks the win.
        :param board: matrix of chars
        """
        check = 0

        if board[0][0] == 'X' and board[2][2] == 'X' and board[1][1] == '-':
            self.add_piece(1, 1, 'O')
            check += 1
        elif board[0][0] == 'X' and board[1][1] == 'X' and board[2][2] == '-':
            self.add_piece(2, 2, 'O')
            check += 1
        elif board[1][1] == 'X' and board[2][2] == 'X' and board[0][0] == '-':
            self.add_piece(0, 0, 'O')
            check += 1
        elif board[0][2] == 'X' and board[2][0] == 'X' and board[1][1] == '-':
            self.add_piece(1, 1, 'O')
            check += 1
        elif board[0][2] == 'X' and board[1][1] == 'X' and board[2][0] == '-':
            self.add_piece(2, 0, 'O')
            check += 1
        elif board[1][1] == 'X' and board[2][0] == 'X' and board[0][2] == '-':
            self.add_piece(0, 2, 'O')
            check += 1
        else:
            for i in range(3):
                if board[i][0] == 'X' and board[i][2] == 'X' and board[i][1] == '-':
                    self.add_piece(i, 1, 'O')
                    check += 1
                elif board[i][0] == 'X' and board[i][1] == 'X' and board[i][2] == '-':
                    self.add_piece(i, 2, 'O')
                    check += 1
                elif board[i][1] == 'X' and board[i][2] == 'X' and board[i][0] == '-':
                    self.add_piece(i, 0, 'O')
                    check += 1
                elif board[0][i] == 'X' and board[2][i] == 'X' and board[1][i] == '-':
                    self.add_piece(1, i, 'O')
                    check += 1
                elif board[0][i] == 'X' and board[1][i] == 'X' and board[2][i] == '-':
                    self.add_piece(2, i, 'O')
                    check += 1
                elif board[1][i] == 'X' and board[2][i] == 'X' and board[0][i] == '-':
                    self.add_piece(0, i, 'O')
                    check += 1
        if check == 0:
            x = -1
            y = -1

            while x == -1 or board[x][y] != '-':
                x = random.randint(0, 2)
                y = random.randint(0, 2)

            self.add_piece(x, y, 'O')

    @staticmethod
    def get_adjacent(x, y, board, notx1, noty1, notx2, noty2):
        """
        Function that returns the first adjacent cell of (x, y) that is not (notx1, noty1) or (notx2, noty2).
        Returns False if it is not found.
        :param x: int from [0-2]
        :param y: int from [0-2]
        :param board: matrix of chars
        :param notx1: int from [0-2]
        :param noty1: int from [0-2]
        :param notx2: int from [0-2]
        :param noty2: int from [0-2]
        :return: boolean | two int from [0-2]
        """
        for i in range(max(0, x-1), min(2, x+2)):
            for j in range(max(0, y-1), min(2, y+2)):
                if i != notx1 and i != notx2 and j != noty1 and j != noty2 and board[i][j] == '-':
                    return i, j
        return False

    def computer_movement(self, board):
        """
        Function that programmatically generates a movement of the computer.
        If the computer is at one step of winning, it makes the correct movement.
        :param board: matrix of chars
        """
        check_m = 0

        if board[0][0] == 'O' and board[2][2] == 'O' and board[1][1] == '-' and self.get_adjacent(1, 1, self.repo.board.board, 0, 0, 2, 2):
            ix, iy = self.get_adjacent(1, 1, self.repo.board.board, 0, 0, 2, 2)
            self.move_piece(ix, iy, 1, 1, 'O')
            check_m += 1
        elif board[0][0] == 'O' and board[1][1] == 'O' and board[2][2] == '-' and self.get_adjacent(2, 2, self.repo.board.board, 0, 0, 1, 1):
            ix, iy = self.get_adjacent(2, 2, self.repo.board.board, 0, 0, 1, 1)
            self.move_piece(ix, iy, 2, 2, 'O')
            check_m += 1
        elif board[1][1] == 'O' and board[2][2] == 'O' and board[0][0] == '-' and self.get_adjacent(0, 0, self.repo.board.board, 1, 1, 2, 2):
            ix, iy = self.get_adjacent(0, 0, self.repo.board.board, 1, 1, 2, 2)
            self.move_piece(ix, iy, 0, 0, 'O')
            check_m += 1
        elif board[0][2] == 'O' and board[2][0] == 'O' and board[1][1] == '-' and self.get_adjacent(1, 1, self.repo.board.board, 0, 2, 2, 0):
            ix, iy = self.get_adjacent(1, 1, self.repo.board.board, 0, 2, 2, 0)
            self.move_piece(ix, iy, 1, 1, 'O')
            check_m += 1
        elif board[0][2] == 'O' and board[1][1] == 'O' and board[2][0] == '-' and self.get_adjacent(2, 0, self.repo.board.board, 0, 2, 1, 1):
            ix, iy = self.get_adjacent(2, 0, self.repo.board.board, 0, 2, 1, 1)
            self.move_piece(ix, iy, 2, 0, 'O')
            check_m += 1
        elif board[1][1] == 'O' and board[2][0] == 'O' and board[0][2] == '-' and self.get_adjacent(0, 2, self.repo.board.board, 1, 1, 2, 0):
            ix, iy = self.get_adjacent(0, 2, self.repo.board.board, 1, 1, 2, 0)
            self.move_piece(ix, iy, 0, 2, 'O')
            check_m += 1
        else:
            for i in range(3):
                if board[i][0] == 'O' and board[i][2] == 'O' and board[i][1] == '-' and self.get_adjacent(i, 1, self.repo.board.board, i, 0, i, 2):
                    ix, iy = self.get_adjacent(i, 1, self.repo.board.board, i, 0, i, 2)
                    self.move_piece(ix, iy, i, 1, 'O')
                    check_m += 1
                elif board[i][0] == 'O' and board[i][1] == 'O' and board[i][2] == '-' and self.get_adjacent(i, 2, self.repo.board.board, i, 0, i, 1):
                    ix, iy = self.get_adjacent(i, 2, self.repo.board.board, i, 0, i, 1)
                    self.move_piece(ix, iy, i, 2, 'O')
                    check_m += 1
                elif board[i][1] == 'O' and board[i][2] == 'O' and board[i][0] == '-' and self.get_adjacent(i, 0, self.repo.board.board, i, 1, i, 2):
                    ix, iy = self.get_adjacent(i, 0, self.repo.board.board, i, 1, i, 2)
                    self.move_piece(ix, iy, i, 0, 'O')
                    check_m += 1
                elif board[0][i] == 'O' and board[2][i] == 'O' and board[1][i] == '-' and self.get_adjacent(1, i, self.repo.board.board, 0, i, 2, i):
                    ix, iy = self.get_adjacent(1, i, self.repo.board.board, 0, i, 2, i)
                    self.move_piece(ix, iy, 1, i, 'O')
                    check_m += 1
                elif board[0][i] == 'O' and board[1][i] == 'O' and board[2][i] == '-' and self.get_adjacent(2, i, self.repo.board.board, 0, i, 1, i):
                    ix, iy = self.get_adjacent(2, i, self.repo.board.board, 0, i, 1, i)
                    self.move_piece(ix, iy, 2, i, 'O')
                    check_m += 1
                elif board[1][i] == 'O' and board[2][i] == 'O' and board[0][i] == '-' and self.get_adjacent(0, i, self.repo.board.board, 1, i, 2, i):
                    ix, iy = self.get_adjacent(0, i, self.repo.board.board, 1, i, 2, i)
                    self.move_piece(ix, iy, 0, i, 'O')
                    check_m += 1

        if check_m == 0:
            x1 = -1
            y1 = -1
            x2 = -1
            y2 = -1

            while x2 == -1 or board[x2][y2] != '-':
                x1 = random.randint(0, 2)
                y1 = random.randint(0, 2)

                x2 = random.randint(max(0, x1-1), min(2, x1+1))
                y2 = random.randint(max(0, y1 - 1), min(2, y1 + 1))

            self.move_piece(x1, y1, x2, y2, 'O')
