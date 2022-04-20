from src.repository.base_repository.discipline_repository import DisciplineRepo
from src.domain.discipline_domain import Discipline
import pickle


class BinDisciplineRepo(DisciplineRepo):
    def __init__(self, file_path):
        DisciplineRepo.__init__(self)
        self.__file_path = file_path
        self.generate()

    def _read_file(self):
        """
        Reads lines from the file and converts them into Discipline objects.
        """
        with open(self.__file_path, "rb") as f:
            i = 0
            try:
                for obj in pickle.load(f):
                    if i < len(self._list):
                        self._list[i] = Discipline(obj["id"], obj["name"])
                    else:
                        self._list.append(Discipline(obj["id"], obj["name"]))
                        self.max_id = max(self.max_id, obj["id"])
                    i += 1
            except EOFError:
                pass

    def _write_file(self):
        """
        Saves all disciplines to the file as objects.
        """
        with open(self.__file_path, "wb") as f:
            new_list = []

            for disc in self._list:
                dict = {
                    "id": disc.id,
                    "name": disc.name
                }
                new_list.append(dict)

            pickle.dump(new_list, f)

    def add(self, name, id=None):
        self._read_file()
        did = DisciplineRepo.add(self, name, id)
        self._write_file()
        return did

    def remove(self, did):
        self._read_file()
        DisciplineRepo.remove(self, did)
        self._write_file()

    def update(self, did, new_name):
        self._read_file()
        DisciplineRepo.update(self, did, new_name)
        self._write_file()

    def generate(self):
        self._read_file()
        if self.max_id == 0:
            names = ["Programming fundamentals", "Design technology", "Machine learning", "Graph theory", "Operating systems", "Music", "Ancient Greek", "Computer studies", "French", "Information and communication technology", "Modern studies", "Art", "Geography", "Dance", "Physical education", "Arithmetic", "Biology", "Health and hygiene", "Food technology", "Logic"]
            for name in names:
                self.add(name)