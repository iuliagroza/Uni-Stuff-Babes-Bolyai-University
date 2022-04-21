class Grade:
    def __init__(self, grade_id, discipline_id, student_id, grade_value):
        self._id = grade_id
        self._discipline_id = discipline_id
        self._student_id = student_id
        self._grade_value = grade_value

    def __eq__(self, other):
        return isinstance(other, Grade) and self._id == other._id and self._discipline_id == other._discipline_id and self._student_id == other._student_id and self._grade_value == other._grade_value

    @property
    def id(self):
        return self._id

    @property
    def discipline_id(self):
        return self._discipline_id

    @property
    def student_id(self):
        return self._student_id

    @property
    def grade_value(self):
        return self._grade_value
