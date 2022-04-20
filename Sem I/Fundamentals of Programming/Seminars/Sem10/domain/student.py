from domain.entity import Entity


class Student(Entity):
    def __init__(self, entity_id, name):
        super().__init__(entity_id)
        self.__name = name

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, new_name):
        self.__name = new_name

    @staticmethod
    def student_to_line(student):
        return f"{student._entity_id}, {student.__name}"

    @staticmethod
    def line_to_student(line):
        return Student(int(line[0]), line[1])
