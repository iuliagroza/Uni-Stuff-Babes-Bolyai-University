from repository.repository import Repository


class CSVRepository(Repository):
    def __init__(self, file_path):
        Repository.__init__(self)
        self.__file_path = file_path
        with open(self.__file_path, "r") as f:
            for line in f.readlines():
                line = line.strip(" \n")
                row = []
                for i in line:
                    row.append(i)
                self.__board.board.append(row)

    def _read_file(self):
        with open(self.__file_path, "r") as f:
            i = 0
            for line in f.readlines():
                line = line.strip(" \n")
                row = []
                for j in line:
                    row.append(j)
                self.__board.append(row)
                i += 1

    def _write_file(self):
        with open(self.__file_path, "w") as f:
            for i in range(3):
                for j in range(3):
                    f.write("{0},".format(self.__board.board[i][j]))

    def add_piece(self, x, y, type):
        """
        Adds a piece on the board
        :param x: integer from [0-2]
        :param y: integer from [0-2]
        :param type: character
        """
        self._read_file()
        self.__board.board[x][y] = type
        self._write_file()

    def move_piece(self, x1, y1, x2, y2, type):
        """
        Moves a piece on the board.
        :param x1: integer from [0-2]
        :param y1: integer from [0-2]
        :param x2: integer from [0-2]
        :param y2: integer from [0-2]
        :param type: character
        """
        self._read_file()
        self.__board.board[x1][y1] = '-'
        self.__board.board[x2][y2] = type
        self._write_file()
