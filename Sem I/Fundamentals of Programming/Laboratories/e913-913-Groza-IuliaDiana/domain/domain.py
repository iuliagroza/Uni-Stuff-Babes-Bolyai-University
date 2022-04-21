class Board:
    """
    The Board domain. Here the board is initialized.
    """
    def __init__(self):
        self.__board = []
        for i in range(3):
            row = []
            for j in range(3):
                row.append("-")
            self.__board.append(row)

    @property
    def board(self):
        return self.__board
