class Board:
    def __init__(self, height, width, owner):
        """
        Board domain
        :param height: integer (classically equal to 10)
        :param width: integer (classically equal to 10)
        :param owner: string ("computer"|"owner")
        """
        self._board = []

        # Board matrix generation
        for i in range(height):
            row = []
            for j in range(width):
                row.append("0")
            self._board.append(row)

        self._number_of_planes = 0
        self._height = height
        self._width = width
        self.__owner = owner
        self.__score = 0

    # Getters and setters
    @property
    def board(self):
        return self._board

    @property
    def number_of_planes(self):
        return self._number_of_planes

    @number_of_planes.setter
    def number_of_planes(self, value):
        self._number_of_planes = value

    @property
    def score(self):
        return self.__score

    @score.setter
    def score(self, value):
        self.__score = value

    @property
    def height(self):
        return self._height

    @property
    def width(self):
        return self._width
