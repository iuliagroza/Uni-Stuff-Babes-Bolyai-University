from src.domain.student_domain import Student
from src.repository.base_repository.student_repository import StudentRepo
import pickle


class BinStudentRepo(StudentRepo):
    def __init__(self, file_path):
        StudentRepo.__init__(self)
        self.__file_path = file_path
        self.generate()

    def _read_file(self):
        """
        Reads lines from the file and converts them into Student objects.
        """
        with open(self.__file_path, "rb") as f:
            i = 0
            try:
                for obj in pickle.load(f):
                    if i < len(self._list):
                        self._list[i] = Student(obj["id"], obj["name"])
                    else:
                        self._list.append(Student(obj["id"], obj["name"]))
                        self.max_id = max(self.max_id, obj["id"])
                    i += 1
            except EOFError:
                pass

    def _write_file(self):
        """
        Writes to file.
        """
        with open(self.__file_path, "wb") as f:
            new_list = []

            for stud in self._list:
                dict = {
                    "id": stud.id,
                    "name": stud.name
                }
                new_list.append(dict)

            pickle.dump(new_list, f)

    def add(self, name, id=None):
        self._read_file()
        sid = StudentRepo.add(self, name, id)
        self._write_file()
        return sid

    def remove(self, sid):
        self._read_file()
        StudentRepo.remove(self, sid)
        self._write_file()

    def update(self, sid, new_name):
        self._read_file()
        StudentRepo.update(self, sid, new_name)
        self._write_file()

    def generate(self):
        self._read_file()
        if self.max_id == 0:
            names = ["Sterling", "Teodoro", "Erin", "Ariel", "Phillip", "Percy", "Zane", "Williams", "Richie", "Reuben", "Ricardo", "Dominick", "Maria", "Irving", "Michael", "Abel", "Solomon", "Marty", "Roscoe", "Rodrigo"]
            for name in names:
                self.add(name)
