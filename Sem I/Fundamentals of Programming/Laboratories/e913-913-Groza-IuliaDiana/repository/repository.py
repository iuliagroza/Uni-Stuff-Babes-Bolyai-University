from domain.domain import Board


class Repository:
    def __init__(self):
        self.__board = Board()

    @property
    def board(self):
        return self.__board

    def add_piece(self, x, y, type):
        """
        Adds a piece on the board
        :param x: integer from [0-2]
        :param y: integer from [0-2]
        :param type: character
        """
        self.__board.board[x][y] = type

    def move_piece(self, x1, y1, x2, y2, type):
        """
        Moves a piece on the board.
        :param x1: integer from [0-2]
        :param y1: integer from [0-2]
        :param x2: integer from [0-2]
        :param y2: integer from [0-2]
        :param type: character
        """
        self.__board.board[x1][y1] = '-'
        self.__board.board[x2][y2] = type
