import unittest

from domain.taxi_domain import Taxi
from repository.taxi_repository import TaxiRepository
from services.taxi_services import TaxiServices


class TestRepository(unittest.TestCase):
    def setUp(self) -> None:
        """
        Runs before every test method
        """
        self.__repo = TaxiRepository()
        self.__services = TaxiServices(self.__repo)

    def tearDown(self) -> None:
        """
        Runs after every test method
        """
        pass

    def test_find_closest_taxi(self):
        self.__services.add_taxi(2, 4)
        self.__services.add_taxi(4, 6)
        self.__services.add_taxi(25, 50)
        self.assertEqual(self.__services.find_closest_taxi(1, 2, 3, 4), [1, 3, 3, 4])

    def test_process_ride(self):
        self.__services.add_taxi(2, 4)
        self.__services.add_taxi(4, 6)
        self.__services.add_taxi(25, 50)
        lst = self.__services.find_closest_taxi(1, 2, 3, 4)
        self.__services.process_ride(lst)
        t1 = Taxi(1, 2, 4)
        t2 = Taxi(2, 4, 6)
        t3 = Taxi(3, 25, 50)

        t1.fare += 3

        self.assertEqual(self.__repo.list, self.__repo.list)
