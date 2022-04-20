import pickle

from persistency.repositories import Repository


class FileRepository(Repository):
    def __init__(self, file_path, entity_from_line, line_from_entity):
        Repository.__init__(self)
        self.__file_path = file_path
        self.__entity_from_line = entity_from_line
        self.__line_from_entity = line_from_entity

    def __read_all_from_file(self):
        with open(self.__file_path, "rb") as f:
            try:
                self._entities = pickle.load(f)
            except EOFError:
                pass
        """
        with open(self.__file_path, "r") as f:
            self._entities.clear()
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if len(line) > 0:
                    entity = self.__entity_from_line(line)
                    self._entities[entity.entity_id] = entity
        """

    def __append_to_file(self, entity):
        with open(self.__file_path, "wb") as f:
            pickle.dump(self._entities, f)
        """
        with open(self.__file_path, "a") as f:
            f.write(self.__line_from_entity(entity)+"\n")
        """

    def __write_all_to_file(self):
        with open(self.__file_path, "w") as f:
            for entity_id in self._entities:
                f.write(self.__line_from_entity(self._entities[entity_id])+"\n")

    def add(self, entity):
        self.__read_all_from_file()
        Repository.add(self, entity)
        self.__append_to_file(entity)

    def search_by_id(self, entity_id):
        self.__read_all_from_file()
        return Repository.search_by_id(self, entity_id)

    def delete_by_id(self, entity_id):
        self.__read_all_from_file()
        Repository.delete_by_id(self, entity_id)
        self.__write_all_to_file()

    def update(self, new_entity):
        self.__read_all_from_file()
        Repository.update(self, new_entity)
        self.__write_all_to_file()

    def get_all(self):
        self.__read_all_from_file()
        return Repository.get_all(self)

    def __len__(self):
        self.__read_all_from_file()
        return Repository.__len__(self)
