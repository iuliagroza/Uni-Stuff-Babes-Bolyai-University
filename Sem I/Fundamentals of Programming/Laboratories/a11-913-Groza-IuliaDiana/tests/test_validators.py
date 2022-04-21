import unittest

from domain.board_domain import Board
from domain.plane_domain import Plane
from repository.repository import Repository
from services.services import Services
from validators.validator import Validator


class TestValidator(unittest.TestCase):
    def setUp(self) -> None:
        """
        Runs before every test method
        """
        self._validator = Validator()
        self._computer_board = Board(10, 10, "computer")
        self._user_board = Board(10, 10, "user")
        self._repository = Repository(self._computer_board, self._user_board)
        self._services = Services(self._repository)

    def tearDown(self) -> None:
        """
        Runs after every test method
        """
        pass

    def test_orientation_regex(self):
        """
        Tests .orientation_regex() from validators/validator.py.
        """
        self.assertEqual(self._validator.orientation_regex("upu"), False)
        self.assertEqual(self._validator.orientation_regex("right"), True)

    def test_coordinate_regex(self):
        """
            Tests .coordination_regex() from validators/validator.py.
        """
        self.assertEqual(self._validator.coordinate_regex("10"), False)
        self.assertEqual(self._validator.coordinate_regex("2"), True)

    def test_validate_cell(self):
        """
            Tests .validate_cell() from validators/validator.py.
        """
        board = Board(10, 10, "computer")
        self.assertEqual(self._validator.validate_cell(0, 10, board), False)
        self.assertEqual(self._validator.validate_cell(-1, 9, board), False)
        self.assertEqual(self._validator.validate_cell(0, 9, board), True)

    def test_validate_coordinate(self):
        """
            Tests .validate_coordinate() from validators/validator.py.
        """
        self.assertEqual(self._validator.validate_coordinate(2, 1, 3), True)
        self.assertEqual(self._validator.validate_coordinate(3, 1, 2), False)

    def test_can_add_plane(self):
        """
            Tests .can_add_plane() from validators/validator.py.
        """
        plane1 = Plane(3, 4, "down")
        plane2 = Plane(3, 3, "down")
        plane3 = Plane(5, 5, "left")
        plane4 = Plane(0, 0, "up")
        plane5 = Plane(8, 9, "down")
        plane6 = Plane(1, 0, "left")
        plane7 = Plane(1, 9, "right")
        plane8 = Plane(4, 6, "up")
        plane9 = Plane(5, 9, "right")

        plane_added = Plane(3, 4, "up")
        self._services.add_plane(plane_added, "computer")

        self.assertEqual(self._validator.can_add_plane(plane1, self._services.repository.computer_board), False)
        self.assertEqual(self._validator.can_add_plane(plane2, self._services.repository.computer_board), True)
        self.assertEqual(self._validator.can_add_plane(plane3, self._services.repository.computer_board), False)
        self.assertEqual(self._validator.can_add_plane(plane4, self._services.repository.computer_board), False)
        self.assertEqual(self._validator.can_add_plane(plane5, self._services.repository.computer_board), False)
        self.assertEqual(self._validator.can_add_plane(plane6, self._services.repository.computer_board), False)
        self.assertEqual(self._validator.can_add_plane(plane7, self._services.repository.computer_board), False)
        self.assertEqual(self._validator.can_add_plane(plane8, self._services.repository.computer_board), False)
        self.assertEqual(self._validator.can_add_plane(plane9, self._services.repository.computer_board), False)
