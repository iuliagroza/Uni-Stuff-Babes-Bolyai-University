from src.validators.validator import Validator
from src.validators.errors import NamingError, IdError, NotFoundError
from src.services.undo_redo_services import UndoElement
from src.utils.utils import gnome_sort, custom_filter


class StudentServices:
    def __init__(self, student_repo, grade_repo, undo_services):
        self._students = student_repo
        self._grades = grade_repo
        self._validator = Validator()
        self._undo_services = undo_services

    @property
    def students_met(self):
        return self._students

    @property
    def students(self):
        return self._students.list

    @property
    def grades(self):
        return self._grades.list

    @property
    def undo_services(self):
        return self._undo_services

    def add_student(self, name):
        """
        Appends a student named "name" to the list of students using the function .add() from
        repository/student_repository.py. The name is validated using .validate_name() from validators/validator.py.
        :param name: string
        """
        if not self._validator.validate_name(name):
            raise NamingError

        id = self._students.add(name)

        self._undo_services.register_operation(UndoElement(lambda: self._students.remove(id),
                                                           lambda: self._students.add(name, id), 1))

    def remove_student(self, sid):
        """
        Removes the student having the ID "sid" from the list of students using the function .remove() from
        repository/student_repository.py. The name is validated using .validate_id() and .id_found() from
        validators/validator.py. Removing a student implies removing their grades, so the grades having "student_id"
        equal to "sid" are removed from _grades.list.
        :param sid: string
        """
        if not self._validator.validate_id(str(sid)):
            raise IdError

        sid = int(sid)

        if not self._validator.id_found(sid, self._students.list):
            raise NotFoundError

        grades = list(filter(lambda x: x.student_id == sid, self._grades.list))
        student_name = self._students.find_name(sid)

        def undo_function():
            self._students.add(student_name, sid)
            for grade in grades:
                self._grades.add(grade.discipline_id, grade.student_id, grade.grade_value, grade.id)

        def redo_function():
            self._students.remove(sid)
            for grade in grades:
                self._grades.remove(grade.id)

        self._undo_services.register_operation(UndoElement(undo_function, redo_function, 1))

        self._students.remove(sid)

        index = 0
        while index < len(self._grades.list):
            if self._grades.list[index].student_id == sid:
                self._grades.remove(self._grades.list[index].id)
            else:
                index += 1

    def update_student(self, sid, name):
        """
        Updates the name of the student having the ID "sid" with "name" using the function .update() from
        repository/student_repository.py. The name is validated using .validate_name() and the ID using .validate_id()
        and .id_found() from validators/validator.py.
        :param sid: string
        :param name: string
        """
        if not self._validator.validate_name(name):
            raise NamingError

        if not self._validator.validate_id(str(sid)):
            raise IdError

        sid = int(sid)

        if not self._validator.id_found(sid, self._students.list):
            raise NotFoundError

        old_name = self._students.find_name(sid)

        self._undo_services.register_operation(UndoElement(lambda: self._students.update(sid, old_name),
                                                           lambda: self._students.update(sid, name), 1))

        self._students.update(sid, name)

    def generate_students_list(self, ok=True):
        """
        Procedurally generates 20 instances of Student and appends them to self._list.
        :param ok: initially True (for in-memory storage), boolean that allows the procedural generation of Student instances
        """
        if ok and self._students.max_id == 0:
            letter = "A"

            for i in range(20):
                name = "Student " + letter
                letter = chr(ord(letter) + 1)
                self._students.add(name)

    def search_by_id(self, sid):
        """
        Search a student based on its ID. If the ID is invalid, IdError is raised. Otherwise, partial string matching
        search is done.
        :param sid: integer
        :return: list of objects
        """
        sid = str(sid)

        if not self._validator.validate_id(sid):
            raise IdError

        def fil(student):
            if sid in str(student.id):
                return True
            return False

        return custom_filter(self._students.list, accept=fil)

    def search_by_name(self, name):
        """
        Search a student based on its ID. If the name is invalid, NamingError is raised. Otherwise, case-insensitive
        partial string matching search is done.
        :param name: string
        :return: list of objects
        """
        if not self._validator.validate_name(name):
            raise NamingError

        name = name.lower()

        def fil(student):
            if name in student.name.lower():
                return True
            return False

        return custom_filter(self._students.list, accept=fil)

    @staticmethod
    def compute_average(grades, discipline):
        """
        Computes the averages of the elements of grades[discipline].
        :param grades: dictionary
        :param discipline: string
        :return: float
        """
        avg = 0
        for grade in grades[discipline]:
            avg += float(grade)
        avg /= len(grades[discipline])

        return avg

    def compute_all_averages(self, sid):
        """
        Computes the averages of the student having the id "sid" at all disciplines.
        :param sid: integer
        :return: dictionary
        """
        grades = {}
        averages = {}
        for grade in self._grades.list:
            if grade.student_id == sid:
                if not grade.discipline_id in grades.keys():
                    grades.update({grade.discipline_id: []})
                grades[grade.discipline_id].append(grade.grade_value)

        for discipline in grades.keys():
            avg = self.compute_average(grades, discipline)
            averages.update({discipline: avg})

        return averages

    @staticmethod
    def failed(averages):
        """
        Checks if a student has failed (they have an average <5 at at least one discipline)
        :param averages: dictionary
        :return: bool
        """
        failed = []

        for discipline in averages.keys():
            if averages[discipline] < 5:
                failed.append((discipline, averages[discipline]))

        return failed

    def students_failing(self):
        """
        Creates statistics of the students that have failed.
        :return: list of objects
        """
        results = []

        for student in self._students.list:
            failed_at = self.failed(self.compute_all_averages(student.id))
            if len(failed_at) != 0:
                results.append((student, failed_at))

        return results

    @staticmethod
    def compute_gpa(averages):
        """
        Compute the aggregated average of a student.
        :param averages: dictionary
        :return: float
        """
        gpa = 0

        for discipline in averages.keys():
            gpa += averages[discipline]

        if len(averages.keys()) == 0:
            return -1.00

        gpa /= len(averages.keys())

        return gpa

    def best_students(self):
        """
        Creates statistics of best students, sorted in descending order by their aggregated average (GPA).
        :return: dictionary
        """
        students = []

        for student in self._students.list:
            students.append((student.id, student.name, self.compute_gpa(self.compute_all_averages(student.id))))

        def cmp(student1, student2):
            return student1[2] > student2[2]

        return gnome_sort(students, function=cmp)

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
