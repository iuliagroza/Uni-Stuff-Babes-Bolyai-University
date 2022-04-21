import unittest
from src.validators.validator import Validator
from src.repository.base_repository.student_repository import StudentRepo


class TestValidator(unittest.TestCase):
    def setUp(self) -> None:
        """
        Runs before every test method
        """
        self._validator = Validator()
        self._stud_repo = StudentRepo()

    def tearDown(self) -> None:
        """
        Runs after every test method
        """
        pass

    def test_validate_name(self):
        """
        Tests .validate_name() from validators/validator.py.
        """
        self.assertEqual(self._validator.validate_name("Popescu George"), True)
        self.assertEqual(self._validator.validate_name("xaea12"), False)
        self.assertEqual(self._validator.validate_name("x-ae-a12"), False)
        self.assertEqual(self._validator.validate_name("dutescu ana-maria"), True)
        self.assertEqual(self._validator.validate_name("stiinte ale naturii"), True)

    def test_id_found(self):
        """
        Tests .id_found() from validators/validator.py.
        """
        self._stud_repo.add("aaa")
        self._stud_repo.add("bbb")
        self._stud_repo.add("ccc")
        self._stud_repo.remove(1)
        self._stud_repo.add("aaa")
        self.assertEqual(self._validator.id_found(3, self._stud_repo.list), True)
        self.assertEqual(self._validator.id_found(1, self._stud_repo.list), False)
        self.assertEqual(self._validator.id_found(100, self._stud_repo.list), False)
        self.assertEqual(self._validator.id_found(4, self._stud_repo.list), True)
        self.assertEqual(self._validator.id_found("-sadsf", self._stud_repo.list), False)

    def test_validate_id(self):
        """
        Tests .validate_id() from validators/validator.py.
        """
        self.assertEqual(self._validator.validate_id("10066"), True)
        self.assertEqual(self._validator.validate_id("010"), False)
        self.assertEqual(self._validator.validate_id("9"), True)
        self.assertEqual(self._validator.validate_id("a123b"), False)
        self.assertEqual(self._validator.validate_id("  344454"), False)

    def test_validate_grade(self):
        """
        Tests .validate_grade() from validators/validator.py.
        """
        self.assertEqual(self._validator.validate_grade("3.90"), True)
        self.assertEqual(self._validator.validate_grade("10"), True)
        self.assertEqual(self._validator.validate_grade("3"), True)
        self.assertEqual(self._validator.validate_grade("0"), True)
        self.assertEqual(self._validator.validate_grade("9.00"), False)
        self.assertEqual(self._validator.validate_grade("9.703"), False)
        self.assertEqual(self._validator.validate_grade("9.7"), False)
        self.assertEqual(self._validator.validate_grade("13"), False)
        self.assertEqual(self._validator.validate_grade("-9.70"), False)
        self.assertEqual(self._validator.validate_grade("s9"), False)
        self.assertEqual(self._validator.validate_grade("9."), False)
