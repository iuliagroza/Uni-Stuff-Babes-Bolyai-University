from src.domain.student_domain import Student
from src.utils.utils import Container


class StudentRepo:
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

    def add(self, name, id=None):
        """
        Appends a student named "name" to the list of students. The maximum ID is incremented and the student takes it
        as an ID.
        :param name: string
        :param id: initially None, otherwise an integer
        :return: integer
        """
        if id is None:
            self._max_id += 1
            student = Student(self._max_id, name)
        else:
            student = Student(id, name)

        self._list.append(student)

        if id is None:
            return self._max_id
        else:
            return id

    def remove(self, sid):
        """
        Removes the student with the ID "sid" from the list of students.
        :param sid: integer
        """
        for student in self._list:
            if student.id == sid:
                self._list.remove(student)

    def update(self, sid, new_name):
        """
        Updates the name of the student having the ID "sid" with "new_name".
        :param sid: integer
        :param new_name: string
        """
        for student in self._list:
            if student.id == sid:
                student.name = new_name

    def find_name(self, sid):
        """
        Finds a student's name based on the given id.
        :param sid: integer
        :return: string
        """
        for student in self._list:
            if student.id == sid:
                return student.name
