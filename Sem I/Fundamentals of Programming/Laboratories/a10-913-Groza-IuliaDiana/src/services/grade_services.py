import random
from src.validators.validator import Validator
from src.validators.errors import IdError, NotFoundError, GradeError
from src.services.undo_redo_services import UndoElement


class GradeServices:
    def __init__(self, student_repo, discipline_repo, grade_repo, undo_services):
        self._students = student_repo
        self._disciplines = discipline_repo
        self._grades = grade_repo
        self._undo_services = undo_services
        self._validator = Validator()

    @property
    def students(self):
        return self._students.list

    @property
    def disciplines(self):
        return self._disciplines.list

    @property
    def grades(self):
        return self._grades.list

    def add_grade(self, discipline_id, student_id, grade_value):
        """
        Adds a grade with the given parameters to the list of grades using the function .add_grade() from
        repository/grade_repository.py. The IDs are validated using .validate_id() and .id_found() from
        validators/validator.py.
        :param discipline_id: integer
        :param student_id: integer
        :param grade_value: integer or float value with exactly two (non-zero - 00) decimals
        :return:
        """
        if not self._validator.validate_id(str(student_id)):
            raise IdError

        if not self._validator.validate_id(str(discipline_id)):
            raise IdError

        student_id = int(student_id)
        discipline_id = int(discipline_id)

        if not self._validator.id_found(student_id, self._students.list):
            raise NotFoundError

        if not self._validator.id_found(discipline_id, self._disciplines.list):
            raise NotFoundError

        if not self._validator.validate_grade(grade_value):
            raise GradeError

        id = self._grades.add(discipline_id, student_id, grade_value)

        self._undo_services.register_operation(UndoElement(lambda: self._grades.remove(id),
                                                           lambda: self._grades.add(discipline_id, student_id, grade_value, id), 3))

    @staticmethod
    def generate_grade_value():
        """
        Procedurally generates an integer or a float with exactly two non-zero (- 00) decimals.
        :return: string
        """
        grade_int = random.randint(0, 10)
        if grade_int != 10:
            grade_dec = random.randint(0, 99)
            if grade_dec < 10:
                grade_dec = "0" + str(grade_dec)
            grade_dec = "." + str(grade_dec)
            if grade_dec == ".00":
                grade_dec = ""
        else:
            grade_dec = ""

        return str(grade_int) + str(grade_dec)

    def generate_grades_list(self, ok=True):
        """
        Procedurally generates 20 instances of Grade and appends them to self._list.
        :param ok: initially True (for in-memory storage), boolean that allows the procedural generation of Grade instances
        """
        if ok and self._grades.max_id == 0:
            for i in range(20):
                discipline_id = random.randint(1, len(self._disciplines.list))
                student_id = random.randint(1, len(self._students.list))
                grade_value = self.generate_grade_value()

                self._grades.add(discipline_id, student_id, grade_value)

    def rep_string(self, index):
        """
        Generates a string used for displaying the list of grades with both the name of the discipline and the name of
        the student.
        :return: string
        """
        return f"Grade ID: {self._grades.list[index].id}; Discipline ID: {self._grades.list[index].discipline_id}; Discipline name: {self._disciplines.find_name(self._grades.list[index].discipline_id)}; Student ID: {self._grades.list[index].student_id}; Student name: {self._students.find_name(self._grades.list[index].student_id)}; Grade Value: {self._grades.list[index].grade_value}"
