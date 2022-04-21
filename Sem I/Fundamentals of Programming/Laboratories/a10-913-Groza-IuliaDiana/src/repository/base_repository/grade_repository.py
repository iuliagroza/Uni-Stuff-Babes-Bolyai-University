from src.domain.grade_domain import Grade
from src.utils.utils import Container


class GradeRepo:
    def __init__(self):
        self._list = Container()
        self._max_id = 0

    @property
    def list(self):
        return self._list

    @property
    def max_id(self):
        return self._max_id

    @max_id.setter
    def max_id(self, new_max_id):
        self._max_id = new_max_id

    def add(self, discipline_id, student_id, grade_value, id=None):
        """
        Adds a grade obtained by the student having the ID "student_id" at the discipline having the ID "discipline_id"
        with the value "grade_value". The maximum ID is incremented and the grade takes it as an ID.
        :param discipline_id: integer
        :param student_id: integer
        :param grade_value: integer or float having exactly two (non-zero - 00) decimals.
        :param id: initially None, otherwise an integer
        :return: integer
        """
        if id is None:
            self._max_id += 1
            grade = Grade(self._max_id, discipline_id, student_id, grade_value)
        else:
            grade = Grade(id, discipline_id, student_id, grade_value)

        self._list.append(grade)

        if id is None:
            return self._max_id
        else:
            return id

    def remove(self, grade_id):
        """
        Removes the grade having the ID "grade_id"
        :param grade_id: integer
        """
        for grade in self._list:
            if grade.id == grade_id:
                self._list.remove(grade)
