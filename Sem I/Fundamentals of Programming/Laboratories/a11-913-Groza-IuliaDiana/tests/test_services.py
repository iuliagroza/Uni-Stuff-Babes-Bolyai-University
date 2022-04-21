import unittest

from domain.board_domain import Board
from domain.plane_domain import Plane
from repository.repository import Repository
from services.services import Services
from validators.errors import PlanePlacementError, AlreadyHitError, CellError


class TestServices(unittest.TestCase):
    def setUp(self) -> None:
        """
        Runs before every test method
        """
        self.__computer_board = Board(10, 10, "computer")
        self.__user_board = Board(10, 10, "user")
        self.__repository = Repository(self.__computer_board, self.__user_board)
        self.__services = Services(self.__repository)

    def tearDown(self) -> None:
        """
        Runs after every test method
        """
        pass

    def test_add_plane(self):
        """
        Tests .add_plane() from services/services.py
        """
        plane1 = Plane(1, 3, "up")
        plane2 = Plane(0, 0, "up")
        plane3 = Plane(5, 9, "right")
        plane4 = Plane(2, 3, "left")

        self.__services.add_plane(plane1, "user")

        with self.assertRaises(PlanePlacementError):
            self.__services.add_plane(plane2, "user")

        self.__services.add_plane(plane3, "computer")
        self.__services.add_plane(plane4, "computer")

        self.assertEqual(self.__services.repository.user_board.number_of_planes, 1)
        self.assertEqual(self.__services.repository.computer_board.number_of_planes, 2)

    def test_hit_cell(self):
        """
        Tests .hit_cell() from services/services.py
        """
        plane1 = Plane(3, 3, "down")
        plane2 = Plane(3, 3, "up")

        self.__services.add_plane(plane1, "computer")
        self.__services.add_plane(plane2, "user")

        self.assertEqual(self.__services.hit_cell(1, 1, "computer"), "air")
        self.assertEqual(self.__services.hit_cell(3, 3, "computer"), "shot down")
        self.assertEqual(self.__services.hit_cell(2, 3, "computer"), "hit")

        with self.assertRaises(AlreadyHitError):
            self.__services.hit_cell(1, 1, "computer")

        with self.assertRaises(CellError):
            self.__services.hit_cell(0, 10, "computer")

        self.assertEqual(self.__services.hit_cell(7, 1, "user"), "air")
        self.assertEqual(self.__services.hit_cell(3, 3, "user"), "shot down")
        self.assertEqual(self.__services.hit_cell(4, 3, "user"), "hit")

        with self.assertRaises(AlreadyHitError):
            self.__services.hit_cell(7, 1, "user")

        with self.assertRaises(CellError):
            self.__services.hit_cell(-1, 9, "user")

    def test_generate_computer_board(self):
        """
        Tests .generate_computer_board() from services/services.py
        """
        self.__services.generate_computer_board()

        self.assertEqual(self.__services.repository.computer_board.number_of_planes, 3)
