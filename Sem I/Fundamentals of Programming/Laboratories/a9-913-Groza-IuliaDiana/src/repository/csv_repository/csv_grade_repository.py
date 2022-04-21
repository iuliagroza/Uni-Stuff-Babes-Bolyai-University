from src.domain.grade_domain import Grade
from src.repository.base_repository.grade_repository import GradeRepo


class CSVGradeRepo(GradeRepo):
    def __init__(self, file_path, stud_repo, disc_repo):
        GradeRepo.__init__(self)
        self.__file_path = file_path
        self._stud_repo = stud_repo
        self._disc_repo = disc_repo
        with open(self.__file_path, "r") as f:
            for line in f.readlines():
                line = line.strip(" \n")
                grade = line.split(",")
                self._list.append(Grade(int(grade[0]), int(grade[1]), int(grade[3]), grade[5]))
                self.max_id = max(self.max_id, int(grade[0]))

    def _read_file(self):
        """
        Reads lines from the file and converts them into Grade objects.
        """
        with open(self.__file_path, "r") as f:
            i = 0
            for line in f.readlines():
                line = line.strip(" \n")
                grade = line.split(",")
                self._list[i] = Grade(int(grade[0]), int(grade[1]), int(grade[3]), grade[5])
                i += 1

    def _append_to_file(self, grade):
        """
        Appends line to file.
        """
        with open(self.__file_path, "a") as f:
            f.write(f"{grade.id},{grade.discipline_id},{self._disc_repo.find_name(grade.discipline_id)},{grade.student_id},{self._stud_repo.find_name(grade.student_id)},{grade.grade_value}\n")

    def _write_file(self):
        """
        Saves all grades to the file as csv objects.
        """
        with open(self.__file_path, "w") as f:
            for grade in self.list:
                f.write("{0},{1},{2},{3},{4},{5}\n".format(grade.id, grade.discipline_id, self._disc_repo.find_name(grade.discipline_id), grade.student_id, self._stud_repo.find_name(grade.student_id), grade.grade_value))

    def add(self, discipline_id, student_id, grade_value, id=None):
        self._read_file()
        gid = GradeRepo.add(self, discipline_id, student_id, grade_value, id)
        self._append_to_file(self.list[-1])
        return gid

    def remove(self, grade_id):
        self._read_file()
        GradeRepo.remove(self, grade_id)
        self._write_file()
