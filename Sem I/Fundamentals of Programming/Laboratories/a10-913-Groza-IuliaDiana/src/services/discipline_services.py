from src.validators.validator import Validator
from src.validators.errors import NamingError, IdError, NotFoundError
from src.services.undo_redo_services import UndoElement
from src.utils.utils import gnome_sort, custom_filter


class DisciplineServices:
    def __init__(self, discipline_repo, grade_repo, undo_services):
        self._disciplines = discipline_repo
        self._grades = grade_repo
        self._undo_services = undo_services
        self._validator = Validator()

    @property
    def disciplines_met(self):
        return self._disciplines

    @property
    def disciplines(self):
        return self._disciplines.list

    @property
    def grades(self):
        return self._grades.list

    def add_discipline(self, name):
        """
        Appends a discipline named "name" to the list of disciplines using the function .add() from
        repository/discipline_repository.py. The name is validated using .validate_name() from validators/validator.py.
        :param name: string
        """
        if not self._validator.validate_name(name):
            raise NamingError

        id = self._disciplines.add(name)

        self._undo_services.register_operation(UndoElement(lambda: self._disciplines.remove(id),
                                                           lambda: self._disciplines.add(name, id), 2))

    def remove_discipline(self, did):
        """
        Removes the discipline having the ID "did" from the list of disciplines using the function .remove() from
        repository/discipline_repository.py. The name is validated using .validate_id() and .id_found() from
        validators/validator.py. Removing a discipline implies removing its grades, so the grades having "discipline_id"
        equal to "did" are removed from _grades.list.
        :param did: string
        """
        if not self._validator.validate_id(str(did)):
            raise IdError

        did = int(did)

        if not self._validator.id_found(did, self._disciplines.list):
            raise NotFoundError

        grades = list(filter(lambda x: x.discipline_id == did, self._grades.list))
        discipline_name = self._disciplines.find_name(did)

        def undo_function():
            self._disciplines.add(discipline_name, did)
            for grade in grades:
                self._grades.add(grade.discipline_id, grade.student_id, grade.grade_value, grade.id)

        def redo_function():
            self._disciplines.remove(did)
            for grade in grades:
                self._grades.remove(grade.id)

        self._undo_services.register_operation(UndoElement(undo_function, redo_function, 2))

        self._disciplines.remove(did)

        index = 0
        while index < len(self._grades.list):
            if self._grades.list[index].discipline_id == did:
                self._grades.remove(self._grades.list[index].id)
            else:
                index += 1

    def update_discipline(self, did, name):
        """
        Updates the name of the discipline having the ID "did" with "name" using the function .update() from
        repository/discipline_repository.py. The name is validated using .validate_name() and the ID using .validate_id()
        and .id_found() from validators/validator.py.
        :param did: string
        :param name: string
        """
        if not self._validator.validate_name(name):
            raise NamingError

        if not self._validator.validate_id(str(did)):
            raise IdError

        did = int(did)

        if not self._validator.id_found(did, self._disciplines.list):
            raise NotFoundError

        old_name = self._disciplines.find_name(did)

        self._undo_services.register_operation(UndoElement(lambda: self._disciplines.update(did, old_name),
                                                           lambda: self._disciplines.update(did, name), 2))

        self._disciplines.update(did, name)

    def generate_disciplines_list(self, ok=True):
        """
        Procedurally generates 20 instances of Discipline and appends them to self._list.
        :param ok: initially True (for in-memory storage), boolean that allows the procedural generation of Discipline instances
        """
        if ok and self._disciplines.max_id == 0:
            letter = "A"

            for i in range(20):
                name = "Discipline " + letter
                letter = chr(ord(letter) + 1)
                self._disciplines.add(name)

    def search_by_id(self, did):
        """
        Search a discipline based on its ID. If the ID is invalid, IdError is raised. Otherwise, partial string matching
        search is done.
        :param did: integer
        :return: list of objects
        """
        did = str(did)

        if not self._validator.validate_id(did):
            raise IdError

        def fil(discipline):
            if did in str(discipline.id):
                return True
            return False

        return custom_filter(self._disciplines.list, accept=fil)

    def search_by_name(self, name):
        """
        Search a discipline based on its ID. If the name is invalid, NamingError is raised. Otherwise, case-insensitive
        partial string matching search is done.
        :param name: string
        :return: list of objects
        """
        if not self._validator.validate_name(name):
            raise NamingError

        name = name.lower()

        def fil(discipline):
            if name in discipline.name.lower():
                return True
            return False

        return custom_filter(self._disciplines.list, accept=fil)

    @staticmethod
    def compute_average(grades):
        """
        Computes the averages of the elements of grades.
        :param grades: list of floats
        :return: float
        """
        avg = 0
        for grade in grades:
            avg += float(grade)

        if len(grades) == 0:
            return -1.00

        avg /= len(grades)

        return avg

    def compute_all_averages(self, did):
        """
        Computes the averages of all the grades received at the discipline having the id "did".
        :param did: integer
        :return: float
        """
        grades = []
        for grade in self._grades.list:
            if grade.discipline_id == did:
                grades.append(grade.grade_value)

        return self.compute_average(grades)

    def best_disciplines(self):
        """
        Creates statistics for the grades received at every discipline, sorted in descending order.
        :return: dictionary
        """
        disciplines = []

        for discipline in self._disciplines.list:
            disciplines.append((discipline.id, discipline.name, self.compute_all_averages(discipline.id)))

        def cmp(discipline1, discipline2):
            return discipline1[2] > discipline2[2]

        return gnome_sort(disciplines, function=cmp)

    def undo(self):
        """
        Undo function from service.
        """
        self._undo_services.undo()

    def redo(self):
        """
        Redo function from service.
        """
        self._undo_services.redo()
