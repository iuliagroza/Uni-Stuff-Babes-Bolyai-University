class RepositoryError(Exception):
    pass


class Repository:
    def __init__(self):
        self._entities = {}

    def __len__(self):
        return len(self._entities)

    def get_all(self):
        return list(self._entities.values())

    def add(self, entity):
        if entity.entity_id in self._entities:
            raise RepositoryError("Existing entity.txt")

        self._entities[entity.entity_id] = entity

    def search_by_id(self, entity_id):
        if not entity_id in self._entities:
            raise RepositoryError("Entity does not exist.")

        return self._entities[entity_id]

    def delete_by_id(self, entity_id):
        if not entity_id in self._entities:
            raise RepositoryError("Entity does not exist.")

        del self._entities[entity_id]

    def update(self, new_entity):
        if not new_entity.entity_id in self._entities:
            raise RepositoryError("Entity does not exist.")

        self._entities[new_entity.entity_id] = new_entity
