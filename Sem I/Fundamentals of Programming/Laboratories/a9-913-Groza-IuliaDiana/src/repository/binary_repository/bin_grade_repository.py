from src.domain.grade_domain import Grade
from src.repository.base_repository.grade_repository import GradeRepo
import pickle


class BinGradeRepo(GradeRepo):
    def __init__(self, file_path, stud_repo, disc_repo):
        GradeRepo.__init__(self)
        self.__file_path = file_path
        self._stud_repo = stud_repo
        self._disc_repo = disc_repo
        self.generate()

    def _read_file(self):
        """
        Reads lines from the file and converts them into Grade objects.
        """
        with open(self.__file_path, "rb") as f:
            i = 0
            try:
                for obj in pickle.load(f):
                    if i < len(self._list):
                        self._list[i] = Grade(obj["id"], obj["discipline_id"], obj["student_id"], obj["grade_value"])
                    else:
                        self._list.append(Grade(obj["id"], obj["discipline_id"], obj["student_id"], obj["grade_value"]))
                        self.max_id = max(self.max_id, obj["id"])
                    i += 1
            except EOFError:
                pass

    def _write_file(self):
        """
        Saves all grades to the file as csv objects.
        """
        with open(self.__file_path, "wb") as f:
            new_list = []

            for grade in self._list:
                dict = {
                    "id": grade.id,
                    "discipline_id": grade.discipline_id,
                    "student_id": grade.student_id,
                    "grade_value": grade.grade_value
                }
                new_list.append(dict)

            pickle.dump(new_list, f)

    def add(self, discipline_id, student_id, grade_value, id=None):
        self._read_file()
        gid = GradeRepo.add(self, discipline_id, student_id, grade_value, id)
        self._write_file()
        return gid

    def remove(self, grade_id):
        self._read_file()
        GradeRepo.remove(self, grade_id)
        self._write_file()

    def generate(self):
        self._read_file()
        if self.max_id == 0:
            grades = [(1, 1, "10"), (2, 14, "3.45"), (3, 6, "6.89"), (13, 12, "3.89"), (6, 6, "2.50"), (4, 2, "3.45"), (1, 1, "7"), (10, 18, "5"), (9, 8, "7.77"), (13, 17, "9.80"), (10, 19, "5.67"), (20, 20, "9.99"), (18, 11, "2"), (2, 7, "9"), (13, 17, "6.78"), (10, 18, "10"), (6, 6, "2"), (5, 6, "4.99"), (18, 17, "8.70"), (10, 10, "10")]
            for grade in grades:
                self.add(grade[0], grade[1], grade[2])
