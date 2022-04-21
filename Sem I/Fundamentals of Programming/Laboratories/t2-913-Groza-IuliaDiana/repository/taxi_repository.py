from domain.taxi_domain import Taxi


class TaxiRepository:
    def __init__(self):
        self.__list = []
        self.__max_id = 0

    @property
    def list(self):
        return self.__list

    @property
    def max_id(self):
        return self.__max_id

    @max_id.setter
    def max_id(self, new_max_id):
        self.__max_id = new_max_id

    def add_taxi(self, x, y, id=None):
        if id is None:
            self.__max_id += 1
            taxi = Taxi(self.__max_id, x, y)
        else:
            taxi = Taxi(id, x, y)

        self.__list.append(taxi)

