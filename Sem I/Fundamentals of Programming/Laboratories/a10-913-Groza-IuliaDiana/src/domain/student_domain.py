class Student:
    def __init__(self, student_id, name):
        self._id = student_id
        self._name = name

    def __str__(self):
        return f"Student ID: {self._id}; Student Name: {self._name}"

    def __eq__(self, other):
        return isinstance(other, Student) and self._name == other._name and self._id == other._id

    @property
    def id(self):
        return self._id

    @property
    def name(self):
        return self._name

    @name.setter
    def name(self, new_name):
        self._name = new_name
