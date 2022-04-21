class Taxi:
    def __init__(self, tid, x, y):
        self.__id = tid
        self.__position = {
            "x": x,
            "y": y
        }
        self.__fare = 0

    def __str__(self):
        return f"Taxi ID: {self.__id}; Taxi Current X: {self.__position['x']}; Taxi Current Y: {self.__position['y']}; Taxi total fare: {self.__fare}"

    def __eq__(self, other):
        return isinstance(other, Taxi) and self.__position == other.__position and self.__id == other.__id and self.__fare == other.__fare

    @property
    def id(self):
        return self.__id

    @property
    def position(self):
        return self.__position

    @property
    def fare(self):
        return self.__fare

    @fare.setter
    def fare(self, value):
        self.__fare = value
