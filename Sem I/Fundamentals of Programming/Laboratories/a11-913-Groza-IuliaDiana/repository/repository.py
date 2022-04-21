from domain.plane_domain import Plane


class Repository:
    def __init__(self, computer_board, user_board):
        self._computer_board = computer_board
        self._user_board = user_board

    @property
    def computer_board(self):
        return self._computer_board

    @property
    def user_board(self):
        return self._user_board

    @staticmethod
    def add_by_orientation(plane, var_board, i1, i2, r1, r2, reverse=False):
        """
        Function that adds a plane with a certain orientation. In this way, we can use the same function for any orientation.
        :param plane: Plane object
        :param var_board: Board object
        :param i1: integer (classically from [0, 9])
        :param i2: integer (classically from [0, 9])
        :param r1: integer (classically from [0, 9])
        :param r2: integer (classically from [0, 9])
        :param reverse: boolean
        """
        for i in range(r1, r2):
            left = 0
            right = 0
            if i == i1:
                left -= 2
                right += 2
            elif i == i2:
                left -= 1
                right += 1

            for j in range(left, right + 1):
                if reverse:
                    var_board.board[plane.cabin["x"] + j][plane.cabin["y"] + i] = "A"
                else:
                    var_board.board[plane.cabin["x"] + i][plane.cabin["y"] + j] = "A"

    def add_by_owner(self, plane, var_board):
        """
        Adds a plane on a certain board (the computer's or the owner's).
        :param plane: Plane object
        :param var_board: Board object
        """
        var_board.board[plane.cabin["x"]][plane.cabin["y"]] = "C"
        var_board.number_of_planes += 1

        if plane.orientation == "up":
            self.add_by_orientation(plane, var_board, 1, 3, 1, 4)
        elif plane.orientation == "down":
            self.add_by_orientation(plane, var_board, -1, -3, -3, 0)
        if plane.orientation == "left":
            self.add_by_orientation(plane, var_board, 1, 3, 1, 4, reverse=True)
        if plane.orientation == "right":
            self.add_by_orientation(plane, var_board, -1, -3, -3, 0, reverse=True)

    def add_plane(self, plane, owner):
        """
        Main function of adding a plane.
        :param plane: Plane object
        :param owner: string ("computer"|"user")
        """
        if owner == "computer":
            self.add_by_owner(plane, self._computer_board)
        else:
            self.add_by_owner(plane, self._user_board)

    def hit_cell(self, x, y, owner):
        """
        Hits a cell. If the cell is a cabin, we increment the score of the computer board. We mark the cell with "X"
        other way.
        :param x: integer (classically from [0, 9])
        :param y: integer (classically from [0, 9])
        :param owner: string ("computer"|"user")
        :return: string("air"|"hit"|"shot down")
        """
        if owner == "computer":
            if self._computer_board.board[x][y] == "C":
                self._computer_board.board[x][y] = "X"
                self._computer_board.score += 1
                return "shot down"
            elif self._computer_board.board[x][y] == "A":
                self._computer_board.board[x][y] = "X"
                return "hit"
            else:
                self._computer_board.board[x][y] = "X"
                return "air"
        else:
            if self._user_board.board[x][y] == "C":
                self._user_board.board[x][y] = "X"
                self._user_board.score += 1
                return "shot down"
            elif self._user_board.board[x][y] == "A":
                self._user_board.board[x][y] = "X"
                return "hit"
            else:
                self._user_board.board[x][y] = "X"
                return "air"

    @staticmethod
    def create_plane(x, y, orientation):
        """
        Function that creates a plane so we can respect the Layered Architecture principles (creates a Plane object
        that can be used in the services or UI).
        :param x: integer (classically from [0, 9])
        :param y: integer (classically from [0, 9])
        :param orientation: string ("up"|"down"|"left"|"right")
        :return: Plane object
        """
        plane = Plane(x, y, orientation)
        return plane
