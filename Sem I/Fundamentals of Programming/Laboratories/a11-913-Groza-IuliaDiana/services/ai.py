import random

from validators.validator import Validator


class AI:
    """
        Lame AI
        Random hits
    """
    def __init__(self, board):
        self.__board = board
        self.__validator = Validator()

    def easy(self, x1, x2, y1, y2):
        """
        Randomly chooses a valid cell to hit. This includes cells that were not already hit or cells that can contain a cabin.
        The algorithm is trivial, it chooses random valid cells, so he does not care about parts of planes being situated
        in cells. His only goal is to hit a cabin.
        :return: two integers (the coordinates)
        """
        # A cabin cannot be placed in such cell, because the plane would outrun the board. trivial_cells stores such cells.
        trivial_cells = [(0, 0), (0, 1), (1, 0), (1, 1), (0, 8), (0, 9), (1, 8), (1, 9), (8, 0), (8, 1), (9, 0), (9, 1), (8, 8), (8, 9), (9, 8), (9, 9)]

        x = random.randint(x1, x2)
        y = random.randint(y1, y2)
        while (self.__board.board[x][y] == "X") or ((x, y) in trivial_cells):
            x = random.randint(x1, x2)
            y = random.randint(y1, y2)
        return x, y

    def medium(self, cells):
        """
        Once the computer hits a cell that is part of a plane, the area of choice for the next move reduces to a 5x5
        square that has the center in the current cell. We use the algorithm from Easy AI for hitting a cell, but on a
        restricted area.
        :return: two integers (the coordinates)
        """
        if len(cells) == 0:
            curr_x, curr_y = self.easy(0, self.__board.height - 1, 0, self.__board.width - 1)
        else:
            x1 = max(0, cells[-1][0] - 2)
            y1 = max(0, cells[-1][1] - 2)
            x2 = min(self.__board.height - 1, cells[-1][0] + 2)
            y2 = min(self.__board.width - 1, cells[-1][1] + 2)
            curr_x, curr_y = self.easy(x1, x2, y1, y2)

        cells.clear()
        if self.__board.board[curr_x][curr_y] == "A" or self.__board.board[curr_x][curr_y] == "C":
            cells.append((curr_x, curr_y))

        return curr_x, curr_y

    def advanced(self, queue):
        """
        Once the computer hits a cell that is part of a plane, we could use a Lee Algorithm approach (BFS) to find the
        contour of the plane (progressively hitting neighbours of a cell until we find another part of the plane or,
        ideally, the cabin) . Once we find the cabin, we empty the queue, finish our search and in the next move a
        random cell is hit using Easy AI.
        :return: two integers (the coordinates)
        """
        if len(queue) == 0:
            curr_x, curr_y = self.easy(0, self.__board.height - 1, 0, self.__board.width - 1)
            if self.__board.board[curr_x][curr_y] == "A":
                for i in range(-1, 2):
                    for j in range(-1, 2):
                        if not (i == 0 and j == 0):
                            if self.__validator.validate_cell(curr_x + i, curr_y + j, self.__board) and self.__board.board[curr_x + i][curr_y + j] != "X":
                                queue.append((curr_x + i, curr_y + j))
        else:
            curr_x, curr_y = queue[0]
            queue.pop(0)
            if self.__board.board[curr_x][curr_y] == "C":
                queue.clear()
            elif self.__board.board[curr_x][curr_y] == "A":
                for i in range(-1, 2):
                    for j in range(-1, 2):
                        if not (i == 0 and j == 0):
                            if self.__validator.validate_cell(curr_x + i, curr_y + j, self.__board) and self.__board.board[curr_x + i][curr_y + j] != "X":
                                queue.append((curr_x + i, curr_y + j))

        return curr_x, curr_y
