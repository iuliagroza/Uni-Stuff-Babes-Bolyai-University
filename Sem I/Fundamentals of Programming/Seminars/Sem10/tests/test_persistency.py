import unittest
from domain.entity import Entity
from domain.student import Student
from persistency.file_repository import FileRepository
from persistency.repositories import RepositoryError


class TestPersistency(unittest.TestCase):
    def setUp(self) -> None:
        with open("entity.txt", "w") as f:
            f.write("")
        with open("students.txt", "w") as f:
            f.write("")
        self.__repo = FileRepository("entity.txt", Entity.line_to_entity, Entity.entity_to_line)
        self.__student_repo = FileRepository("students_pickle", Student.line_to_student, Student.student_to_line)

    def tearDown(self) -> None:
        pass

    def test_add(self):
        e1 = Entity(1)
        e2 = Entity(2)
        e3 = Entity(3)

        self.__repo.add(e1)
        self.__repo.add(e2)
        self.__repo.add(e3)

        self.assertEqual(self.__repo.__len__(), 3)

        all = self.__repo.get_all()
        all.sort(key=lambda x: x.entity_id)

        self.assertEqual(all, [e1, e2, e3])

        with self.assertRaises(RepositoryError):
            self.__repo.add(e1)

    def test_add_student(self):
        e1 = Student(1, "dffg")
        e2 = Student(2, "frgethr")
        e3 = Student(3, "dasfg")

        self.__student_repo.add(e1)
        self.__student_repo.add(e2)
        self.__student_repo.add(e3)

        self.assertEqual(self.__student_repo.__len__(), 3)

        all = self.__student_repo.get_all()
        all.sort(key=lambda x: x.entity_id)

        self.assertEqual(all, [e1, e2, e3])

        with self.assertRaises(RepositoryError):
            self.__student_repo.add(e1)

    """
    def test_search_by_id(self):
        e1 = Entity(1)
        e2 = Entity(2)
        e3 = Entity(3)

        self.__repo.add(e1)
        self.__repo.add(e2)
        self.__repo.add(e3)

        with self.assertRaises(RepositoryError):
            self.__repo.search_by_id(4)

        self.assertEqual(self.__repo.search_by_id(2), e2)

    def test_delete_by_id(self):
        e1 = Entity(1)
        e2 = Entity(2)
        e3 = Entity(3)

        self.__repo.add(e1)
        self.__repo.add(e2)
        self.__repo.add(e3)

        with self.assertRaises(RepositoryError):
            self.__repo.delete_by_id(4)

        self.__repo.delete_by_id(2)
        self.assertEqual(self.__repo.entities, {1: e1, 3: e3})

        self.__repo.delete_by_id(1)
        self.assertEqual(self.__repo.entities, {3: e3})

        self.__repo.delete_by_id(3)
        self.assertEqual(self.__repo.entities, {})

    def test_update(self):
        e1 = Entity(1)
        e2 = Entity(2)
        e3 = Entity(3)
        e4 = Entity(1)
        e5 = Entity(25)

        with self.assertRaises(RepositoryError):
            self.__repo.update(e5)
            
    """