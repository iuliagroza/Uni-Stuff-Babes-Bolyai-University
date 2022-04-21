from src.repository.base_repository.discipline_repository import DisciplineRepo
from src.domain.discipline_domain import Discipline


class CSVDisciplineRepo(DisciplineRepo):
    def __init__(self, file_path):
        DisciplineRepo.__init__(self)
        self.__file_path = file_path
        with open(self.__file_path, "r") as f:
            for line in f.readlines():
                line = line.strip(" \n")
                discipline = line.split(",")
                self._list.append(Discipline(int(discipline[0]), discipline[1]))
                self.max_id = max(self.max_id, int(discipline[0]))

    def _read_file(self):
        """
        Reads lines from the file and converts them into Discipline objects.
        """
        with open(self.__file_path, "r") as f:
            i = 0
            for line in f.readlines():
                line = line.strip(" \n")
                discipline = line.split(",")
                self._list[i] = Discipline(int(discipline[0]), discipline[1])
                i += 1

    def _append_to_file(self, discipline):
        """
        Appends line to file.
        """
        with open(self.__file_path, "a") as f:
            f.write(f"{discipline.id},{discipline.name}\n")

    def _write_file(self):
        """
        Saves all disciplines to the file as csv objects.
        """
        with open(self.__file_path, "w") as f:
            for discipline in self.list:
                f.write("{0},{1}\n".format(discipline.id, discipline.name))

    def add(self, name, id=None):
        self._read_file()
        did = DisciplineRepo.add(self, name, id)
        self._append_to_file(self.list[-1])
        return did

    def remove(self, did):
        self._read_file()
        DisciplineRepo.remove(self, did)
        self._write_file()

    def update(self, did, new_name):
        self._read_file()
        DisciplineRepo.update(self, did, new_name)
        self._write_file()
