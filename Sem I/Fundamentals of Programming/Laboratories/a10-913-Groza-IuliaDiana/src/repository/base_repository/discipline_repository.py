from src.domain.discipline_domain import Discipline
from src.utils.utils import Container


class DisciplineRepo:
    def __init__(self):
        self._list = Container()
        self._max_id = 0

    @property
    def list(self):
        return self._list

    @property
    def max_id(self):
        return self._max_id

    @max_id.setter
    def max_id(self, new_max_id):
        self._max_id = new_max_id

    def add(self, name, id=None):
        """
        Appends a discipline named "name" to the list of disciplines. The maximum ID is incremented and the discipline
        takes it as an ID.
        :param name: string
        :param id: initially None, otherwise an integer
        :return: integer
        """
        if id is None:
            self._max_id += 1
            discipline = Discipline(self._max_id, name)
        else:
            discipline = Discipline(id, name)

        self._list.append(discipline)

        if id is None:
            return self._max_id
        else:
            return id

    def remove(self, did):
        """
        Removes the discipline with the ID "did" from the list of disciplines.
        :param did: integer
        """
        for discipline in self._list:
            if discipline.id == did:
                self._list.remove(discipline)

    def update(self, did, new_name):
        """
        Updates the name of the discipline having the ID "did" with "new_name".
        :param did: integer
        :param new_name: string:
        """
        for discipline in self._list:
            if discipline.id == did:
                discipline.name = new_name

    def find_name(self, did):
        """
        Finds a discipline's name based on the given id.
        :param did: integer
        :return: string
        """
        for discipline in self._list:
            if discipline.id == did:
                return discipline.name
