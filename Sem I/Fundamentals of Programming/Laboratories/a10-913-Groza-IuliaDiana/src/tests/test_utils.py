import unittest
from src.utils.utils import Container, gnome_sort


class TestUtils(unittest.TestCase):
    def setUp(self) -> None:
        """
        Runs before every test method
        """
        self._lst = Container()

    def tearDown(self) -> None:
        """
        Runs after every test method
        """
        pass

    def test_gnome_sort(self):
        """
        Tests gnome_sort() function from utils.py
        """
        numbers = [19, -2, 5, 0, 66, 1]

        self.assertEqual(gnome_sort(numbers, reverse=True), [66, 19, 5, 1, 0, -2])

    def test_del(self):
        """
        Tests __delitem__() property of the Container class from utils.py
        """
        lst = Container()
        lst.append(1)
        lst.append(2)

        lst.__delitem__(0)

        new_lst = Container()
        new_lst.append(2)

        self.assertEqual(lst, new_lst)
