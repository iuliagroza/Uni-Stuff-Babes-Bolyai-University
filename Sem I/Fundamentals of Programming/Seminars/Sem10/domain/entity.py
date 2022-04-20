class Entity:
    def __init__(self, entity_id):
        self._entity_id = entity_id

    def __eq__(self, other):
        return self._entity_id == other._entity_id

    @property
    def entity_id(self):
        return self._entity_id

    @staticmethod
    def entity_to_line(entity):
        return f"{entity._entity_id}"

    @staticmethod
    def line_to_entity(line):
        return Entity(int(line[0]))
