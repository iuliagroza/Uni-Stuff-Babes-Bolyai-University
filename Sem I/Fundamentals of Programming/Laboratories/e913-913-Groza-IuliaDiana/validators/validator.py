import re


class Validator:
    @staticmethod
    def validate_input(ipt):
        if not re.match("^[0-2]{1} [0-2]{1}$", ipt):
            return False
        return True

    @staticmethod
    def validate_movement_input(ipt):
        if not re.match("^[0-2]{1} [0-2]{1} [0-2]{1} [0-2]{1}$", ipt):
            return False
        return True

    @staticmethod
    def validate_cell_bounds(x, y, board):
        if x < 0 or x > 2:
            return False
        if y < 0 or y > 2:
            return False

        if board[x][y] != '-':
            return False

        return True

    @staticmethod
    def validate_adjacency(x1, y1, x2, y2):
        if abs(x1-x2) > 1 or abs(y1-y2) > 1:
            return False
        return True
