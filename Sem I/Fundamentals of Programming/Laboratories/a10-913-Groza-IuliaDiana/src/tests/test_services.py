import unittest
from src.domain.student_domain import Student
from src.domain.discipline_domain import Discipline
from src.domain.grade_domain import Grade
from src.repository.base_repository.student_repository import StudentRepo
from src.repository.base_repository.discipline_repository import DisciplineRepo
from src.repository.base_repository.grade_repository import GradeRepo
from src.services.undo_redo_services import UndoServices
from src.services.student_services import StudentServices
from src.services.discipline_services import DisciplineServices
from src.services.grade_services import GradeServices
from src.utils.utils import Container
from src.validators.errors import NamingError, IdError, NotFoundError, GradeError, UndoError


class TestServices(unittest.TestCase):
    def setUp(self) -> None:
        """
        Runs before every test method
        """
        stud_repo = StudentRepo()
        disc_repo = DisciplineRepo()
        grade_repo = GradeRepo()
        undo_serv = UndoServices()
        self._student_services = StudentServices(stud_repo, grade_repo, undo_serv)
        self._discipline_services = DisciplineServices(disc_repo, grade_repo, undo_serv)
        self._grade_services = GradeServices(stud_repo, disc_repo, grade_repo, undo_serv)

    def tearDown(self) -> None:
        """
        Runs after every test method
        """
        pass

    def test_add_student(self):
        """
        Tests .add_student() from services/student_services.py.
        """
        with self.assertRaises(NamingError):
            self._student_services.add_student("ana3-popescu")

        p1 = Student(1, "Popescu George")
        p2 = Student(2, "Popescu George")
        p3 = Student(3, "dutescu ana-maria")

        new_container = Container()
        new_container.append(p1)
        new_container.append(p2)
        new_container.append(p3)

        self._student_services.add_student("Popescu George")
        self._student_services.add_student("Popescu George")
        self._student_services.add_student("dutescu ana-maria")

        self.assertEqual(self._student_services.students, new_container)

    def test_add_discipline(self):
        """
        Tests .add_discipline() from services/discipline_services.py.
        """
        with self.assertRaises(NamingError):
            self._discipline_services.add_discipline("Matematica1")

        p1 = Discipline(1, "Informatica")
        p2 = Discipline(2, "Informatica")
        p3 = Discipline(3, "filosofie")

        new_container = Container()
        new_container.append(p1)
        new_container.append(p2)
        new_container.append(p3)

        self._discipline_services.add_discipline("Informatica")
        self._discipline_services.add_discipline("Informatica")
        self._discipline_services.add_discipline("filosofie")

        self.assertEqual(self._discipline_services.disciplines, new_container)

    def test_add_grade(self):
        """
        Tests .add_grade() from services/grade_services.py.
        """
        self._student_services.add_student("a")
        self._student_services.add_student("b")
        self._student_services.add_student("c")

        self._discipline_services.add_discipline("A")
        self._discipline_services.add_discipline("B")
        self._discipline_services.add_discipline("C")

        with self.assertRaises(IdError):
            self._grade_services.add_grade("01", 1, "9")

        with self.assertRaises(IdError):
            self._grade_services.add_grade(1, "edf", "9")

        with self.assertRaises(NotFoundError):
            self._grade_services.add_grade(123, 1, "9")

        with self.assertRaises(NotFoundError):
            self._grade_services.add_grade(1, 33, "9")

        with self.assertRaises(GradeError):
            self._grade_services.add_grade(1, 2, "9.00")

        g1 = Grade(1, 1, 2, "9")
        g2 = Grade(2, 3, 2, "7.33")
        g3 = Grade(3, 2, 2, "3.90")
        g4 = Grade(4, 3, 3, "10")
        g5 = Grade(5, 1, 2, "8.08")

        new_container = Container()
        new_container.append(g1)
        new_container.append(g2)
        new_container.append(g3)
        new_container.append(g4)
        new_container.append(g5)

        self._grade_services.add_grade(1, 2, "9")
        self._grade_services.add_grade(3, 2, "7.33")
        self._grade_services.add_grade(2, 2, "3.90")
        self._grade_services.add_grade(3, 3, "10")
        self._grade_services.add_grade(1, 2, "8.08")

        self.assertEqual(self._grade_services.grades, new_container)

    def test_remove_student(self):
        """
        Tests .remove_student() from services/student_services.py.
        """
        self._student_services.add_student("Big Foot")
        self._student_services.add_student("as faesg")
        self._student_services.add_student("aaa")
        self._student_services.add_student("Popescu George")
        self._student_services.add_student("Popescu George")
        self._student_services.add_student("dutescu ana-maria")

        self._discipline_services.add_discipline("Matematica")
        self._discipline_services.add_discipline("Limba Romana")
        self._discipline_services.add_discipline("Limba Chineza")

        self._grade_services.add_grade(2, 5, "9.99")
        self._grade_services.add_grade(1, 6, "10")
        self._grade_services.add_grade(3, 5, "7")

        with self.assertRaises(NotFoundError):
            self._student_services.remove_student(101)

        with self.assertRaises(IdError):
            self._student_services.remove_student("334d 3")

        p1 = Student(1, "Big Foot")
        p2 = Student(2, "as faesg")
        p3 = Student(3, "aaa")
        p4 = Student(4, "Popescu George")
        p5 = Student(6, "dutescu ana-maria")

        new_container = Container()
        new_container.append(p1)
        new_container.append(p2)
        new_container.append(p3)
        new_container.append(p4)
        new_container.append(p5)

        g1 = Grade(2, 1, 6, "10")

        new_grade_container = Container()
        new_grade_container.append(g1)

        self._student_services.remove_student(5)
        self.assertEqual(self._student_services.students, new_container)
        self.assertEqual(self._student_services.grades, new_grade_container)

        with self.assertRaises(NotFoundError):
            self._student_services.remove_student(5)

        self._student_services.remove_student(4)
        new_container.remove(p4)
        self.assertEqual(self._student_services.students, new_container)
        self.assertEqual(self._student_services.grades, new_grade_container)

        self._student_services.remove_student(6)
        new_container.remove(p5)
        new_grade_container.remove(g1)
        self.assertEqual(self._student_services.students, new_container)
        self.assertEqual(self._student_services.grades, new_grade_container)

    def test_remove_discipline(self):
        """
        Tests .remove_discipline() from services/discipline_services.py.
        """
        self._student_services.add_student("aa")
        self._student_services.add_student("bb")
        self._student_services.add_student("cc")

        self._discipline_services.add_discipline("sport")
        self._discipline_services.add_discipline("Limba Romana")
        self._discipline_services.add_discipline("chimie")
        self._discipline_services.add_discipline("fizica")
        self._discipline_services.add_discipline("Informatica")
        self._discipline_services.add_discipline("filosofie")

        self._grade_services.add_grade(6, 1, "3.99")
        self._grade_services.add_grade(6, 2, "10")
        self._grade_services.add_grade(2, 2, "7")
        self._grade_services.add_grade(4, 2, "9.99")
        self._grade_services.add_grade(6, 3, "6.90")

        with self.assertRaises(NotFoundError):
            self._discipline_services.remove_discipline(7)

        with self.assertRaises(IdError):
            self._discipline_services.remove_discipline("334d 3")

        p1 = Discipline(1, "sport")
        p2 = Discipline(2, "Limba Romana")
        p3 = Discipline(3, "chimie")
        p4 = Discipline(5, "Informatica")
        p5 = Discipline(6, "filosofie")

        new_container = Container()
        new_container.append(p1)
        new_container.append(p2)
        new_container.append(p3)
        new_container.append(p4)
        new_container.append(p5)

        g1 = Grade(1, 6, 1, "3.99")
        g2 = Grade(2, 6, 2, "10")
        g3 = Grade(3, 2, 2, "7")
        g4 = Grade(5, 6, 3, "6.90")

        new_grade_container = Container()
        new_grade_container.append(g1)
        new_grade_container.append(g2)
        new_grade_container.append(g3)
        new_grade_container.append(g4)

        self._discipline_services.remove_discipline(4)
        self.assertEqual(self._discipline_services.disciplines, new_container)
        self.assertEqual(self._discipline_services.grades, new_grade_container)

        with self.assertRaises(NotFoundError):
            self._discipline_services.remove_discipline(4)

        self._discipline_services.remove_discipline(6)
        new_container.remove(p5)
        new_grade_container.remove(g1)
        new_grade_container.remove(g2)
        new_grade_container.remove(g4)
        self.assertEqual(self._discipline_services.disciplines, new_container)
        self.assertEqual(self._discipline_services.grades, new_grade_container)

        self._discipline_services.remove_discipline(2)
        new_container.remove(p2)
        new_grade_container.remove(g3)
        self.assertEqual(self._discipline_services.disciplines, new_container)
        self.assertEqual(self._discipline_services.grades, new_grade_container)

    def test_update_student(self):
        """
        Tests .update_student() from services/student_services.py.
        """
        self._student_services.add_student("Big Foot")
        self._student_services.add_student("aaa")
        self._student_services.add_student("maria p")
        self._student_services.add_student("popop")

        with self.assertRaises(NamingError):
            self._student_services.update_student(4, "add3")

        with self.assertRaises(IdError):
            self._student_services.update_student("03", "add")

        with self.assertRaises(NotFoundError):
            self._student_services.update_student(9, "add")

        p1 = Student(1, "Big Foot")
        p2 = Student(2, "aaa")
        p3 = Student(3, "AAA")
        p4 = Student(4, "BBB")

        new_container = Container()
        new_container.append(p1)
        new_container.append(p2)
        new_container.append(p3)
        new_container.append(p4)

        self._student_services.update_student(3, "AAA")
        self._student_services.update_student(4, "BBB")

        self.assertEqual(self._student_services.students, new_container)

    def test_update_discipline(self):
        """
        Tests .update_discipline() from services/discipline_services.py.
        """
        self._discipline_services.add_discipline("aaddad")
        self._discipline_services.add_discipline("chimie")
        self._discipline_services.add_discipline("as safa-s")

        with self.assertRaises(NamingError):
            self._discipline_services.update_discipline(4, "add3")

        with self.assertRaises(IdError):
            self._discipline_services.update_discipline("03", "add")

        with self.assertRaises(NotFoundError):
            self._discipline_services.update_discipline(7, "add")

        p1 = Discipline(1, "AAA")
        p2 = Discipline(2, "chimie")
        p3 = Discipline(3, "BBB")

        new_container = Container()
        new_container.append(p1)
        new_container.append(p2)
        new_container.append(p3)

        self._discipline_services.update_discipline(1, "AAA")
        self._discipline_services.update_discipline(3, "BBB")

        self.assertEqual(self._discipline_services.disciplines, new_container)

    def test_search_by_id_stud(self):
        """
        Tests .search_by_id() from services/student_services.py
        """
        self._student_services.add_student("Ana")
        self._student_services.add_student("Bogdan")
        self._student_services.add_student("Carina")
        self._student_services.add_student("Anaa")
        self._student_services.add_student("Bogdann")
        self._student_services.add_student("Carinaa")
        self._student_services.add_student("Anaaa")
        self._student_services.add_student("Bogdannn")
        self._student_services.add_student("Carinaaa")
        self._student_services.add_student("Anaaaa")
        self._student_services.add_student("Bogdannnn")
        self._student_services.add_student("Carinaaaa")

        p1 = Student(1, "Ana")
        p2 = Student(10, "Anaaaa")
        p3 = Student(11, "Bogdannnn")
        p4 = Student(12, "Carinaaaa")

        new_container = Container()
        new_container.append(p1)
        new_container.append(p2)
        new_container.append(p3)
        new_container.append(p4)

        new_second_container = Container()

        with self.assertRaises(IdError):
            self._student_services.search_by_id("sdq111")

        self.assertEqual(self._student_services.search_by_id(1), new_container)
        self.assertEqual(self._student_services.search_by_id(19), new_second_container)

    def test_search_by_name_stud(self):
        """
        Tests .search_by_name() from services/student_services.py
        """
        self._student_services.add_student("Ana")
        self._student_services.add_student("Bogdan")
        self._student_services.add_student("Carina")
        self._student_services.add_student("Anaa")
        self._student_services.add_student("Bogdann")
        self._student_services.add_student("Carinaa")
        self._student_services.add_student("Anaaa")
        self._student_services.add_student("Bogdannn")
        self._student_services.add_student("Carinaaa")
        self._student_services.add_student("Anaaaa")
        self._student_services.add_student("Bogdannnn")
        self._student_services.add_student("Carinaaaa")

        p1 = Student(1, "Ana")
        p2 = Student(4, "Anaa")
        p3 = Student(7, "Anaaa")
        p4 = Student(10, "Anaaaa")

        new_container = Container()
        new_container.append(p1)
        new_container.append(p2)
        new_container.append(p3)
        new_container.append(p4)

        new_second_container = Container()

        with self.assertRaises(NamingError):
            self._student_services.search_by_name("ana-mari4")

        self.assertEqual(self._student_services.search_by_name("aNA"), new_container)
        self.assertEqual(self._student_services.search_by_name("anastasia"), new_second_container)

    def test_compute_average_stud(self):
        """
        Tests .compute_average() from services/student_services.py
        """
        grades = {
            "Maths": [7.89, 4.50, 9, 10],
            "CS": [5, 5],
            "Biology": [10, 4.56],
            "Physics": [9.85]
        }

        self.assertEqual(self._student_services.compute_average(grades, "Maths"), (7.89 + 4.50 + 9 + 10) / 4)

    def test_compute_all_averages_stud(self):
        """
        Tests .compute_all_averages() from services/student_services.py
        """
        self._student_services.add_student("a")
        self._student_services.add_student("b")
        self._student_services.add_student("c")

        self._discipline_services.add_discipline("A")
        self._discipline_services.add_discipline("B")
        self._discipline_services.add_discipline("C")

        self._grade_services.add_grade(1, 1, "7.89")
        self._grade_services.add_grade(2, 3, "10")
        self._grade_services.add_grade(3, 1, "7.90")
        self._grade_services.add_grade(1, 1, "10")
        self._grade_services.add_grade(3, 1, "3.90")
        self._grade_services.add_grade(1, 1, "9.45")
        self._grade_services.add_grade(2, 2, "9.99")

        averages = {
            1: (7.89 + 10 + 9.45) / 3,
            3: (7.90 + 3.90) / 2
        }

        self.assertEqual(self._student_services.compute_all_averages(1), averages)

    def test_failed(self):
        """
        Tests .failed() in services/student_services.py
        """
        student_one = {
            "Maths": 9.90,
            "Biology": 5
        }

        self.assertEqual(self._student_services.failed(student_one), [])

        student_two = {
            "Maths": 9.90,
            "Biology": 5,
            "Logic": 4.99,
            "Chemistry": 10,
            "English": 3.50
        }

        self.assertEqual(self._student_services.failed(student_two), [("Logic", 4.99), ("English", 3.50)])

    def test_students_failing(self):
        """
        Tests .students_failing() from services/student_services.py
        """
        self._student_services.add_student("a")
        self._student_services.add_student("b")
        self._student_services.add_student("c")

        self._discipline_services.add_discipline("A")
        self._discipline_services.add_discipline("B")
        self._discipline_services.add_discipline("C")

        self._grade_services.add_grade(1, 1, "7.89")
        self._grade_services.add_grade(2, 3, "5")
        self._grade_services.add_grade(3, 1, "7.90")
        self._grade_services.add_grade(1, 1, "10")
        self._grade_services.add_grade(3, 1, "1.90")
        self._grade_services.add_grade(1, 1, "9.45")
        self._grade_services.add_grade(2, 2, "9.99")
        self._grade_services.add_grade(2, 3, "3.90")
        self._grade_services.add_grade(1, 3, "4.60")

        p1 = Student(1, "a")
        p2 = Student(3, "c")

        self.assertEqual(self._student_services.students_failing(), [(p1, [(3, (1.90 + 7.90) / 2)]), (p2, [(2, (5 + 3.90) / 2), (1, 4.60)])])

    def test_compute_gpa(self):
        """
        Tests .compute_gpa() from services/student_services.py
        """
        student_one = {
            "Maths": 3.90,
            "Science": 8.90,
            "Literature": 10
        }

        self.assertEqual(self._student_services.compute_gpa(student_one), (3.90 + 8.90 + 10) / 3)

        student_two = {}

        self.assertEqual(self._student_services.compute_gpa(student_two), -1.00)

    def test_best_students(self):
        """
        Tests .best_students() from services/student_services.py
        """
        self._student_services.add_student("a")
        self._student_services.add_student("b")
        self._student_services.add_student("c")

        self._discipline_services.add_discipline("A")
        self._discipline_services.add_discipline("B")
        self._discipline_services.add_discipline("C")

        self._grade_services.add_grade(1, 1, "7.89")
        self._grade_services.add_grade(2, 3, "5")
        self._grade_services.add_grade(3, 1, "7.90")
        self._grade_services.add_grade(1, 1, "10")
        self._grade_services.add_grade(3, 1, "1.90")
        self._grade_services.add_grade(1, 1, "9.45")
        self._grade_services.add_grade(2, 2, "9.99")
        self._grade_services.add_grade(2, 3, "3.90")
        self._grade_services.add_grade(1, 3, "4.60")

        self.assertEqual(self._student_services.best_students(), [(2, "b", 9.99), (1, "a", 7.006666666666667), (3, "c", 4.525)])

    def test_rep_string(self):
        """
        Tests .rep_string() from services/grade_services.py
        """
        self._student_services.add_student("a")

        self._discipline_services.add_discipline("A")

        self._grade_services.add_grade(1, 1, "6.88")

        self.assertEqual(self._grade_services.rep_string(0), f"Grade ID: {self._grade_services.grades[0].id}; Discipline ID: {self._grade_services.grades[0].discipline_id}; Discipline name: {self._discipline_services.disciplines_met.find_name(self._grade_services.grades[0].discipline_id)}; Student ID: {self._grade_services.grades[0].student_id}; Student name: {self._student_services.students_met.find_name(self._grade_services.grades[0].student_id)}; Grade Value: {self._grade_services.grades[0].grade_value}")

    def test_search_by_id_disc(self):
        """
        Tests .search_by_id() from services/discipline_services.py
        """
        self._discipline_services.add_discipline("Maths")
        self._discipline_services.add_discipline("Computer Science")
        self._discipline_services.add_discipline("Romanian")
        self._discipline_services.add_discipline("Mathss")
        self._discipline_services.add_discipline("Computer Sciencee")
        self._discipline_services.add_discipline("Romaniann")
        self._discipline_services.add_discipline("Mathsss")
        self._discipline_services.add_discipline("Computer Scienceee")
        self._discipline_services.add_discipline("Romaniannn")
        self._discipline_services.add_discipline("Mathssss")
        self._discipline_services.add_discipline("Computer Scienceeee")
        self._discipline_services.add_discipline("Romaniannnn")

        p1 = Discipline(1, "Maths")
        p2 = Discipline(10, "Mathssss")
        p3 = Discipline(11, "Computer Scienceeee")
        p4 = Discipline(12, "Romaniannnn")

        new_container = Container()
        new_container.append(p1)
        new_container.append(p2)
        new_container.append(p3)
        new_container.append(p4)

        new_second_container = Container()

        with self.assertRaises(IdError):
            self._discipline_services.search_by_id("sdq111")

        self.assertEqual(self._discipline_services.search_by_id(1), new_container)
        self.assertEqual(self._discipline_services.search_by_id(19), new_second_container)

    def test_search_by_name_disc(self):
        """
        Tests .search_by_name() from services/discipline_services.py
        """
        self._discipline_services.add_discipline("Maths")
        self._discipline_services.add_discipline("Computer Science")
        self._discipline_services.add_discipline("Romanian")
        self._discipline_services.add_discipline("Mathss")
        self._discipline_services.add_discipline("Computer Sciencee")
        self._discipline_services.add_discipline("Romaniann")
        self._discipline_services.add_discipline("Mathsss")
        self._discipline_services.add_discipline("Computer Scienceee")
        self._discipline_services.add_discipline("Romaniannn")
        self._discipline_services.add_discipline("Mathssss")
        self._discipline_services.add_discipline("Computer Scienceeee")
        self._discipline_services.add_discipline("Romaniannnn")

        p1 = Discipline(1, "Maths")
        p2 = Discipline(4, "Mathss")
        p3 = Discipline(7, "Mathsss")
        p4 = Discipline(10, "Mathssss")

        new_container = Container()
        new_container.append(p1)
        new_container.append(p2)
        new_container.append(p3)
        new_container.append(p4)

        new_second_container = Container()

        with self.assertRaises(NamingError):
            self._discipline_services.search_by_name("ana-mari4")

        self.assertEqual(self._discipline_services.search_by_name("MAt"), new_container)
        self.assertEqual(self._discipline_services.search_by_name("Mathematics"), new_second_container)

    def test_compute_average_disc(self):
        """
        Tests .compute_average() from services/discipline_services.py
        """
        grades = [1.23, 10, 7, 4.99, 8.50, 6.69]

        empty_grades = []

        self.assertEqual(self._discipline_services.compute_average(grades), (1.23 + 7 + 4.99 + 10 + 8.50 + 6.69) / 6)
        self.assertEqual(self._discipline_services.compute_average(empty_grades), -1)

    def test_compute_all_averages_disc(self):
        """
        Tests .compute_all_averages() from services/discipline_services.py
        """
        self._student_services.add_student("a")
        self._student_services.add_student("b")
        self._student_services.add_student("c")

        self._discipline_services.add_discipline("A")
        self._discipline_services.add_discipline("B")
        self._discipline_services.add_discipline("C")

        self._grade_services.add_grade(1, 1, "7.89")
        self._grade_services.add_grade(2, 3, "10")
        self._grade_services.add_grade(3, 1, "7.90")
        self._grade_services.add_grade(1, 1, "10")
        self._grade_services.add_grade(3, 1, "3.90")
        self._grade_services.add_grade(1, 1, "9.45")
        self._grade_services.add_grade(2, 2, "9.99")

        self.assertEqual(self._discipline_services.compute_all_averages(1), (7.89 + 10 + 9.45) / 3)

    def test_best_disciplines(self):
        """
        Tests .best_disciplines() from services/discipline_services.py
        """
        self._student_services.add_student("a")
        self._student_services.add_student("b")
        self._student_services.add_student("c")

        self._discipline_services.add_discipline("A")
        self._discipline_services.add_discipline("B")
        self._discipline_services.add_discipline("C")

        self._grade_services.add_grade(1, 1, "7.89")
        self._grade_services.add_grade(2, 3, "10")
        self._grade_services.add_grade(3, 1, "7.90")
        self._grade_services.add_grade(1, 1, "10")
        self._grade_services.add_grade(3, 1, "3.90")
        self._grade_services.add_grade(1, 1, "9.45")
        self._grade_services.add_grade(2, 2, "9.99")

        self.assertEqual(self._discipline_services.best_disciplines(), [(2, "B", (10 + 9.99) / 2), (1, "A", (7.89 + 10 + 9.45) / 3), (3, "C", (7.90 + 3.90) / 2)])

    def test_generate_students_list(self):
        """
        Tests .generate_students_list() from services/student_services.py
        """
        self._student_services.generate_students_list()

        self.assertEqual(len(self._student_services.students), 20)

    def test_generate_discipline_list(self):
        """
        Tests .generate_disciplines_list() from services/discipline_services.py
        """
        self._discipline_services.generate_disciplines_list()

        self.assertEqual(len(self._discipline_services.disciplines), 20)

    def test_generate_grade_value(self):
        """
        Tests .generate_grade_value() from services/grade_services.py
        """
        grade = self._grade_services.generate_grade_value()

        self.assertEqual(type(grade), str)

    def test_generate_grades_list(self):
        """
        Tests .generate_grades_list() from services/grade_services.py
        """
        self._student_services.add_student("a")
        self._discipline_services.add_discipline("A")

        self._grade_services.generate_grades_list()

        self.assertEqual(len(self._grade_services.grades), 20)

    def test_discipline_undo_redo(self):
        """
        Tests .undo() and .redo() from services/discipline_services.py
        """
        self._discipline_services.add_discipline("sddf")
        self._discipline_services.add_discipline("Anato-Anato dfg")
        self._discipline_services.update_discipline(1, "xcsvd")
        self._discipline_services.remove_discipline(1)

        p1 = Discipline(1, "sddf")
        p2 = Discipline(2, "Anato-Anato dfg")
        p3 = Discipline(1, "xcsvd")

        new_container = Container()
        new_container.append(p2)
        new_container.append(p3)

        self._discipline_services.undo()
        self.assertEqual(self._discipline_services.disciplines, new_container)

        self._discipline_services.undo()
        new_container.remove(p3)
        new_container.append(p1)
        self.assertEqual(self._discipline_services.disciplines, new_container)

        self._discipline_services.undo()
        new_container.remove(p2)
        self.assertEqual(self._discipline_services.disciplines, new_container)

        self._discipline_services.undo()
        new_container.remove(p1)
        self.assertEqual(self._discipline_services.disciplines, new_container)

        with self.assertRaises(UndoError):
            self._discipline_services.undo()

        self._discipline_services.redo()
        new_container.append(p1)
        self.assertEqual(self._discipline_services.disciplines, new_container)

        self._discipline_services.redo()
        new_container.append(p2)
        self.assertEqual(self._discipline_services.disciplines, new_container)

        self._discipline_services.redo()
        new_container.__setitem__(0, p3)
        self.assertEqual(self._discipline_services.disciplines, new_container)

        self._discipline_services.redo()
        new_container.remove(p3)
        self.assertEqual(self._discipline_services.disciplines, new_container)

        with self.assertRaises(UndoError):
            self._discipline_services.redo()
