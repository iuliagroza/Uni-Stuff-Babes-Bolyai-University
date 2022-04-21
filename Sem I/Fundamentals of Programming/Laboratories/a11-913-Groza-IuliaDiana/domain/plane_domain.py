class Plane:
    def __init__(self, cabin_x, cabin_y, orientation):
        """
        Plane domain
        :param cabin_x: X coordinate of the position of the cabin
        :param cabin_y: Y coordinate of the position of the cabin
        :param orientation: string ("up"|"down"|"left"|"right")
        """
        self._cabin = {
            "x": cabin_x,
            "y": cabin_y
        }
        self._orientation = orientation

    # Getters and setters
    @property
    def cabin(self):
        return self._cabin

    @property
    def orientation(self):
        return self._orientation
