import unittest
from src.domain.student_domain import Student
from src.domain.discipline_domain import Discipline
from src.domain.grade_domain import Grade
from src.repository.base_repository.student_repository import StudentRepo
from src.repository.base_repository.discipline_repository import DisciplineRepo
from src.repository.base_repository.grade_repository import GradeRepo
from src.utils.utils import Container


class TestRepository(unittest.TestCase):
    def setUp(self) -> None:
        """
        Runs before every test method
        """
        self._stud_repo = StudentRepo()
        self._disc_repo = DisciplineRepo()
        self._grade_repo = GradeRepo()

    def tearDown(self) -> None:
        """
        Runs after every test method
        """
        pass

    def test_add_sr(self):
        """
        Tests .add() from repository/student_repository.py.
        """
        self._stud_repo.add("Popescu Maria")
        self._stud_repo.add("Bob John Carol")
        self._stud_repo.add("Ion")

        p1 = Student(1, "Popescu Maria")
        p2 = Student(2, "Bob John Carol")
        p3 = Student(3, "Ion")

        new_container = Container()
        new_container.append(p1)
        new_container.append(p2)
        new_container.append(p3)

        self.assertEqual(self._stud_repo.list, new_container)
        self.assertEqual(self._stud_repo.max_id, 3)

    def test_remove_sr(self):
        """
        Tests .remove() from repository/student_repository.py.
        """
        self._stud_repo.add("Popescu Maria")
        self._stud_repo.add("Bob John Carol")
        self._stud_repo.add("Ion")

        p1 = Student(1, "Popescu Maria")
        p2 = Student(3, "Ion")

        new_container = Container()
        new_container.append(p1)
        new_container.append(p2)

        self._stud_repo.remove(2)
        self.assertEqual(self._stud_repo.list, new_container)

        self._stud_repo.remove(3)
        new_container.remove(p2)
        self.assertEqual(self._stud_repo.list, new_container)

        self._stud_repo.remove(1)
        new_container.remove(p1)
        self.assertEqual(self._stud_repo.list, new_container)

        self.assertEqual(self._stud_repo.max_id, 3)

    def test_update_sr(self):
        """
        Tests .update() from repository/student_repository.py.
        """
        self._stud_repo.add("Tom Tom")
        self._stud_repo.add("Big Foot")
        self._stud_repo.add("asfgfg")

        p1 = Student(1, "Popa Ilie")
        p2 = Student(2, "Big Foot")
        p3 = Student(3, "as faesg")

        new_container = Container()
        new_container.append(p1)
        new_container.append(p2)
        new_container.append(p3)

        self._stud_repo.update(1, "Popa Ilie")
        self._stud_repo.update(3, "as faesg")

        self.assertEqual(self._stud_repo.list, new_container)
        self.assertEqual(self._stud_repo.max_id, 3)

    def test_add_dr(self):
        """
        Tests .add() from repository/discipline_repository.py.
        """
        self._disc_repo.add("Matematica")
        self._disc_repo.add("Istorie")
        self._disc_repo.add("Stiinte ale naturii")

        p1 = Discipline(1, "Matematica")
        p2 = Discipline(2, "Istorie")
        p3 = Discipline(3, "Stiinte ale naturii")

        new_container = Container()
        new_container.append(p1)
        new_container.append(p2)
        new_container.append(p3)

        self.assertEqual(self._disc_repo.list, new_container)
        self.assertEqual(self._disc_repo.max_id, 3)

    def test_remove_dr(self):
        """
        Tests .remove() from repository/discipline_repository.py.
        """
        self._disc_repo.add("Matematica")
        self._disc_repo.add("Istorie")
        self._disc_repo.add("Stiinte ale naturii")

        p1 = Discipline(1, "Matematica")
        p2 = Discipline(3, "Stiinte ale naturii")

        new_container = Container()
        new_container.append(p1)
        new_container.append(p2)

        self._disc_repo.remove(2)
        self.assertEqual(self._disc_repo.list, new_container)

        self._disc_repo.remove(3)
        new_container.remove(p2)
        self.assertEqual(self._disc_repo.list, new_container)

        self._disc_repo.remove(1)
        new_container.remove(p1)
        self.assertEqual(self._disc_repo.list, new_container)

        self.assertEqual(self._disc_repo.max_id, 3)

    def test_update_dr(self):
        """
        Tests .update() from repository/discipline_repository.py.
        """
        self._disc_repo.add("Educatie fizica")
        self._disc_repo.add("Limba Romana")
        self._disc_repo.add("Fizica")

        p1 = Discipline(1, "sport")
        p2 = Discipline(2, "Limba Romana")
        p3 = Discipline(3, "chimie")

        new_container = Container()
        new_container.append(p1)
        new_container.append(p2)
        new_container.append(p3)

        self._disc_repo.update(1, "sport")
        self._disc_repo.update(3, "chimie")

        self.assertEqual(self._disc_repo.list, new_container)
        self.assertEqual(self._disc_repo.max_id, 3)

    def test_add_gr(self):
        """
        Tests .add() from repository/grade_repository.py.
        """
        self._grade_repo.add(4, 4, 9.70)
        self._grade_repo.add(5, 4, 10)
        self._grade_repo.add(4, 6, 3)

        p1 = Grade(1, 4, 4, 9.70)
        p2 = Grade(2, 5, 4, 10)
        p3 = Grade(3, 4, 6, 3)

        new_container = Container()
        new_container.append(p1)
        new_container.append(p2)
        new_container.append(p3)

        self.assertEqual(self._grade_repo.list, new_container)
        self.assertEqual(self._grade_repo.max_id, 3)

    def test_remove_gr(self):
        """
        Tests .remove() from repository/grade_repository.py.
        """
        self._grade_repo.add(4, 4, 9.70)
        self._grade_repo.add(5, 4, 10)
        self._grade_repo.add(4, 6, 3)

        p1 = Grade(1, 4, 4, 9.70)
        p2 = Grade(3, 4, 6, 3)

        new_container = Container()
        new_container.append(p1)
        new_container.append(p2)

        self._grade_repo.remove(2)
        self.assertEqual(self._grade_repo.list, new_container)

        self._grade_repo.remove(3)
        new_container.remove(p2)
        self.assertEqual(self._grade_repo.list, new_container)

        self._grade_repo.remove(1)
        new_container.remove(p1)
        self.assertEqual(self._grade_repo.list, new_container)

        self.assertEqual(self._grade_repo.max_id, 3)
