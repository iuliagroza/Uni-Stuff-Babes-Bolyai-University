import random


class TaxiServices:
    def __init__(self, repository):
        self.__repository = repository

    @property
    def repository(self):
        return self.__repository

    def add_taxi(self, x, y):
        self.__repository.add_taxi(x, y)

    def generate_random_taxis(self, n):
        while len(self.__repository.list) < n:
            x = random.randint(0, 100)
            y = random.randint(0, 100)

            ok = 0
            for taxi in self.__repository.list:
                manhattan = abs(taxi.position["x"]-x) + abs(taxi.position["y"]-y)

                if manhattan < 5:
                    ok += 1

            if not ok:
                self.add_taxi(x, y)

    def find_closest_taxi(self, x, y, x2, y2):
        """
        Function that finds the closest taxi to the start position (x, y). Returns the taxi such that the Manhattan distance between them is minimal.
        :param x: integer
        :param y: integer
        :param x2: integer
        :param y2: integer
        :return: list
        """
        min_dist = 100000
        taxi_id = 0

        for taxi in self.__repository.list:
            manhattan = abs(taxi.position["x"] - x) + abs(taxi.position["y"] - y)

            if manhattan < min_dist:
                min_dist = manhattan
                taxi_id = taxi.id

        return [taxi_id, min_dist, x2, y2]

    def process_ride(self, lst):
        """
        Processes a ride once the closest taxi has been found using the previous function. Updates the taxi's fare and position.
        :param lst: list
        """
        for taxi in self.__repository.list:
            if taxi.id == lst[0]:
                taxi.fare += lst[1]
                taxi.position["x"] = lst[2]
                taxi.position["y"] = lst[3]

    @staticmethod
    def generate_ride():
        x_start = random.randint(0, 100)
        y_start = random.randint(0, 100)
        x_end = random.randint(0, 100)
        y_end = random.randint(0, 100)
        return [x_start, y_start, x_end, y_end]
