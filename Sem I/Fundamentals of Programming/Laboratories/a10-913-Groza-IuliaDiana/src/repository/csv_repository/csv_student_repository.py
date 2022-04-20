from src.domain.student_domain import Student
from src.repository.base_repository.student_repository import StudentRepo


class CSVStudentRepo(StudentRepo):
    def __init__(self, file_path):
        StudentRepo.__init__(self)
        self.__file_path = file_path
        with open(self.__file_path, "r") as f:
            for line in f.readlines():
                line = line.strip(" \n")
                student = line.split(",")
                self._list.append(Student(int(student[0]), student[1]))
                self.max_id = max(self.max_id, int(student[0]))

    def _read_file(self):
        """
        Reads lines from the file and converts them into Student objects.
        """
        with open(self.__file_path, "r") as f:
            i = 0
            for line in f.readlines():
                line = line.strip(" \n")
                student = line.split(",")
                if i < len(self._list):
                    self._list[i] = Student(int(student[0]), student[1])
                else:
                    self._list.append(Student(int(student[0]), student[1]))
                    self.max_id = max(self.max_id, int(student[0]))
                i += 1

    def _append_to_file(self, student):
        """
        Appends line to file.
        """
        with open(self.__file_path, "a") as f:
            f.write(f"{student.id},{student.name}\n")

    def _write_file(self):
        """
        Saves all students to the file as csv objects.
        """
        with open(self.__file_path, "w") as f:
            for student in self.list:
                f.write("{0},{1}\n".format(student.id, student.name))

    def add(self, name, id=None):
        self._read_file()
        sid = StudentRepo.add(self, name, id)
        self._append_to_file(self.list[-1])
        return sid
        
    def remove(self, sid):
        self._read_file()
        StudentRepo.remove(self, sid)
        self._write_file()

    def update(self, sid, new_name):
        self._read_file()
        StudentRepo.update(self, sid, new_name)
        self._write_file()
