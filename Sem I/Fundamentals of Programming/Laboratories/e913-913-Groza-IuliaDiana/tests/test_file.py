import unittest

from repository.repository import Repository
from services.services import Services
from validators.errors import PlacementError, MovementError


class TestAll(unittest.TestCase):
    def setUp(self) -> None:
        """
        Runs before every test method
        """
        self.__repo = Repository()
        self.__services = Services(self.__repo)

    def tearDown(self) -> None:
        """
        Runs after every test method
        """
        pass

    def test_add_piece(self):
        self.__services.add_piece(0, 1, "X")
        self.__services.add_piece(0, 0, "X")
        self.__services.add_piece(2, 2, "O")

        with self.assertRaises(PlacementError):
            self.__services.add_piece(-1, 3, "O")

        with self.assertRaises(PlacementError):
            self.__services.add_piece(0, 1, "O")

        self.assertEqual(self.__repo.board.board, [["X", "X", "-"], ["-", "-", "-"], ["-", "-", "O"]])

    def test_move_piece(self):
        self.__services.add_piece(0, 1, "X")
        self.__services.add_piece(0, 0, "X")
        self.__services.add_piece(2, 2, "O")

        self.__services.move_piece(0, 1, 1, 1, "X")
        self.__services.move_piece(2, 2, 2, 1, "O")

        with self.assertRaises(MovementError):
            self.__services.move_piece(0, 1, 2, 1, "X")

        with self.assertRaises(MovementError):
            self.__services.move_piece(0, 1, 0, 0, "X")

        self.assertEqual(self.__repo.board.board, [["X", "-", "-"], ["-", "X", "-"], ["-", "O", "-"]])

    def test_check_win_computer(self):
        self.__services.add_piece(0, 1, "O")
        self.__services.add_piece(0, 0, "O")
        self.__services.add_piece(0, 2, "O")

        self.assertEqual(self.__services.check_win_computer(self.__repo.board.board), True)

    def test_check_win_user(self):
        self.__services.add_piece(0, 1, "X")
        self.__services.add_piece(0, 0, "X")
        self.__services.add_piece(0, 2, "X")

        self.assertEqual(self.__services.check_win_user(self.__repo.board.board), True)
