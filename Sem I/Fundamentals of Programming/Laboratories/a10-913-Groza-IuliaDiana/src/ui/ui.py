from src.validators.errors import NamingError, IdError, GradeError, NotFoundError, InputError, UndoError


class UI:
    def __init__(self, student_services, discipline_services, grade_services, ok):
        self._student_services = student_services
        self._discipline_services = discipline_services
        self._grade_services = grade_services
        self.ok = ok

    @staticmethod
    def print_main_menu():
        print("""Welcome to Students Management Register! Choose one of the following commands by typing its corresponding number:
        1. Manage the list of students.
        2. Manage the list of disciplines.
        3. Grade student at a given discipline.
        4. Search disciplines/students.
        5. Display statistics.
        6. Undo the last operation.
        7. Redo the last operation.
        8. Exit""")

    @staticmethod
    def print_first_submenu():
        print("""Choose one of the following commands by typing its corresponding number:
        1. Add a student.
        2. Remove a student.
        3. Update a student's name.
        4. Display the list of students.
        5. Return to the main menu.
        """)

    @staticmethod
    def print_second_submenu():
        print("""Choose one of the following commands by typing its corresponding number:
        1. Add a discipline.
        2. Remove a discipline.
        3. Update a discipline's name.
        4. Display the list of disciplines.
        5. Return to the main menu.
        """)

    @staticmethod
    def print_third_submenu():
        print("""Choose one of the following commands by typing its corresponding number:
        1. Add a grade
        2. Display the list of grades.
        3. Return to the main menu.
        """)

    @staticmethod
    def print_fourth_submenu():
        print("""Choose one of the following commands by typing its corresponding number:
        1. Search a student by ID.
        2. Search a student by name.
        3. Search a discipline by ID.
        4. Search a discipline by name.
        5. Return to the main menu.
        """)

    @staticmethod
    def print_fifth_submenu():
        print("""Choose one of the following commands by typing its corresponding number:
        1. Display all students failing at one or more disciplines.
        2. Display students with the best school situation, sorted in descending order of their aggregated average.
        3. Display all disciplines at which there is at least one grade, sorted in descending order of the average grade(s) received by all students.
        4. Return to the main menu.
        """)

    def display_students_list(self):
        """
        Displays the list of students. If there are no more students an appropriate message is displayed.
        """
        if len(self._student_services.students) == 0:
            print("There are no students.")
        else:
            for student in self._student_services.students:
                print(student)

    def display_disciplines_list(self):
        """
        Displays the list of disciplines. If there are no more disciplines an appropriate message is displayed.
        """
        if len(self._discipline_services.disciplines) == 0:
            print("There are no disciplines.")
        else:
            for discipline in self._discipline_services.disciplines:
                print(discipline)

    def display_grades_list(self):
        """
        Displays the list of grades. If there are no more grades an appropriate message is displayed.
        """
        if len(self._grade_services.grades) == 0:
            print("There are no grades.")
        else:
            for index in range(len(self._grade_services.grades)):
                print(self._grade_services.rep_string(index))

    @staticmethod
    def print_search_results(results):
        """
        Prints the results from search commands.
        :param results: list of objects
        """
        if len(results) == 0:
            print("No results found.")
        else:
            for result in results:
                print(result)

    def print_stats_results_one(self, results):
        """
        Prints the results from the first statistics command.
        :param results:
        :return:
        """
        for result in results:
            print(f"Student ID: {result[0].id}; Student Name: {result[0].name}; Failed at:", end=" ")
            for index in range(len(result[1])):
                if index == len(result[1])-1:
                    print(f"{self._discipline_services.disciplines_met.find_name(result[1][index][0])} ({result[1][index][1]})")
                else:
                    print(f"{self._discipline_services.disciplines_met.find_name(result[1][index][0])} ({result[1][index][1]})", end=", ")

    @staticmethod
    def print_stats_results_two(results):
        """
        Prints the results from the second statistics command.
        :param results: list of objects
        """
        for result in results:
            if result[2] == -1.00:
                print(f"Student ID: {result[0]}; Student Name: {result[1]}; Aggregated average: Not graded yet")
            else:
                print(
                    f"Student ID: {result[0]}; Student Name: {result[1]}; Aggregated average: {'{:.2f}'.format(result[2])}")

    @staticmethod
    def print_stats_results_three(results):
        """
        Prints the results from third statistics command.
        :param results: list of objects
        """
        for result in results:
            if result[2] == -1.00:
                print(f"Discipline ID: {result[0]}; Discipline Name: {result[1]}; Average: No grades yet")
            else:
                print(f"Discipline ID: {result[0]}; Discipline Name: {result[1]}; Average: {'{:.2f}'.format(result[2])}")

    @staticmethod
    def print_input_error():
        print("Invalid option.")

    @staticmethod
    def print_name_error():
        print("Invalid name.")

    @staticmethod
    def print_id_error():
        print("Invalid ID.")

    @staticmethod
    def print_id_not_found():
        print("We couldn't find anything with the given id.")

    @staticmethod
    def print_grade_error():
        print("Invalid grade.")

    @staticmethod
    def print_undo_error():
        print("There are no more operations to undo.")

    @staticmethod
    def print_redo_error():
        print("There are no more operations to redo.")

    def input_option(self, end):
        """
        Obtains the input from the user. If the input is not an integer from [1, end] it will raise InputError.
        :param end: integer
        :return: string
        """
        try:
            command = input(">>> ")

            options = []
            for i in range(end):
                options.append(str(i+1))

            if command not in options:
                raise InputError

            return int(command)
        except InputError:
            self.print_input_error()

    @staticmethod
    def add_student_menu():
        """
        Obtains the input from the add_student command (the name).
        :return: string
        """
        option = input("Please type the name of the student: ")
        return option

    @staticmethod
    def remove_student_menu():
        """
        Obtains the input from the remove_student command (the ID).
        :return: string
        """
        option = input("Please type the ID of the student: ")
        return option

    @staticmethod
    def update_student_menu():
        """
        Obtains the input from the update_student command (the ID and the name).
        :return: string
        """
        ipt = input("Please introduce the ID and the new name of the student: ")

        if ipt.count(' ') < 1:
            raise InputError

        sid = ipt.split()[0]
        name = ipt.split(maxsplit=1)[1]
        return sid, name

    @staticmethod
    def add_discipline_menu():
        """
        Obtains the input from the add_discipline command (the name).
        :return: string
        """
        option = input("Please type the name of the discipline: ")
        return option

    @staticmethod
    def remove_discipline_menu():
        """
        Obtains the input from the remove_discipline command (the ID).
        :return: string
        """
        option = input("Please type the ID of the discipline: ")
        return option

    @staticmethod
    def update_discipline_menu():
        """
        Obtains the input from the update_discipline command (the ID and the name).
        :return: string
        """
        ipt = input("Please introduce the ID and the new name of the discipline: ")

        if ipt.count(' ') < 1:
            raise InputError

        sid = ipt.split()[0]
        name = ipt.split(maxsplit=1)[1]
        return sid, name

    @staticmethod
    def add_grade_menu():
        """
        Obtains the input from the add_grade command (the student id, the discipline id and the value).
        :return: string
        """
        ipt = input("Please introduce the ID of the discipline, the ID of the student and the grade as an integer or as a float with exactly two decimals: ")

        if ipt.count(' ') < 2:
            raise InputError

        discipline_id = ipt.split()[0]
        student_id = ipt.split()[1]
        grade_value = ipt.split()[2]
        return discipline_id, student_id, grade_value

    @staticmethod
    def search_by_id():
        """
        Obtains the input from the search-by-ID commands (for both students and disciplines).
        :return: string
        """
        ipt = input("Please introduce the ID: ")

        return ipt

    @staticmethod
    def search_by_name():
        """
        Obtains the input from the search-by-name commands (for both students and disciplines).
        :return: string
        """
        ipt = input("Please introduce the name: ")

        return ipt

    def start(self):
        """
        Main function
        """
        self._student_services.generate_students_list(self.ok)
        self._discipline_services.generate_disciplines_list(self.ok)
        self._grade_services.generate_grades_list(self.ok)

        while True:
            self.print_main_menu()
            first_option = self.input_option(8)

            # Student
            if first_option == 1:
                self.print_first_submenu()
                second_option = self.input_option(5)

                # Add
                if second_option == 1:
                    try:
                        name = self.add_student_menu()
                        self._student_services.add_student(name)
                    except NamingError:
                        self.print_name_error()
                # Remove
                elif second_option == 2:
                    try:
                        sid = self.remove_student_menu()
                        self._student_services.remove_student(sid)
                    except IdError:
                        self.print_id_error()
                    except NotFoundError:
                        self.print_id_not_found()
                # Update
                elif second_option == 3:
                    try:
                        sid, name = self.update_student_menu()
                        self._student_services.update_student(sid, name)
                    except NamingError:
                        self.print_name_error()
                    except IdError:
                        self.print_id_error()
                    except NotFoundError:
                        self.print_id_not_found()
                    except InputError:
                        self.print_input_error()
                # Display
                elif second_option == 4:
                    self.display_students_list()
                # Back
                else:
                    continue
            # Discipline
            elif first_option == 2:
                self.print_second_submenu()
                second_option = self.input_option(5)

                # Add
                if second_option == 1:
                    try:
                        name = self.add_discipline_menu()
                        self._discipline_services.add_discipline(name)
                    except NamingError:
                        self.print_name_error()
                # Remove
                elif second_option == 2:
                    try:
                        did = self.remove_discipline_menu()
                        self._discipline_services.remove_discipline(did)
                    except IdError:
                        self.print_id_error()
                    except NotFoundError:
                        self.print_id_not_found()
                # Update
                elif second_option == 3:
                    try:
                        did, name = self.update_discipline_menu()
                        self._discipline_services.update_discipline(did, name)
                    except NamingError:
                        self.print_name_error()
                    except IdError:
                        self.print_id_error()
                    except NotFoundError:
                        self.print_id_not_found()
                    except InputError:
                        self.print_input_error()
                # Display
                elif second_option == 4:
                    self.display_disciplines_list()
                # Back
                else:
                    continue
            # Grade
            elif first_option == 3:
                self.print_third_submenu()
                second_option = self.input_option(3)

                # Add
                if second_option == 1:
                    try:
                        discipline_id, student_id, grade_value = self.add_grade_menu()
                        self._grade_services.add_grade(discipline_id, student_id, grade_value)
                    except IdError:
                        self.print_id_error()
                    except NotFoundError:
                        self.print_id_not_found()
                    except GradeError:
                        self.print_grade_error()
                    except InputError:
                        self.print_input_error()
                # Display
                elif second_option == 2:
                    self.display_grades_list()
                # Back
                else:
                    continue
            # Search
            elif first_option == 4:
                self.print_fourth_submenu()
                second_option = self.input_option(5)

                # Search student by ID
                if second_option == 1:
                    try:
                        student_id = self.search_by_id()
                        results = self._student_services.search_by_id(student_id)
                        self.print_search_results(results)
                    except IdError:
                        self.print_id_error()
                # Search student by name
                elif second_option == 2:
                    try:
                        student_name = self.search_by_name()
                        results = self._student_services.search_by_name(student_name)
                        self.print_search_results(results)
                    except NamingError:
                        self.print_name_error()
                # Search discipline by ID
                elif second_option == 3:
                    try:
                        discipline_id = self.search_by_id()
                        results = self._discipline_services.search_by_id(discipline_id)
                        self.print_search_results(results)
                    except IdError:
                        self.print_id_error()
                # Search discipline by name
                elif second_option == 4:
                    try:
                        discipline_name = self.search_by_name()
                        results = self._discipline_services.search_by_name(discipline_name)
                        self.print_search_results(results)
                    except NamingError:
                        self.print_name_error()
                # Back
                else:
                    continue
            # Stats
            elif first_option == 5:
                self.print_fifth_submenu()
                second_option = self.input_option(4)

                if second_option == 1:
                    results = self._student_services.students_failing()
                    self.print_stats_results_one(results)
                elif second_option == 2:
                    results = self._student_services.best_students()
                    self.print_stats_results_two(results)
                elif second_option == 3:
                    results = self._discipline_services.best_disciplines()
                    self.print_stats_results_three(results)
                # Back
                else:
                    continue
            # Undo
            elif first_option == 6:
                try:
                    if len(self._student_services.undo_services.undo_stack) == 0:
                        raise UndoError
                    if self._student_services.undo_services.undo_stack[self._student_services.undo_services.undo_pointer - 1].type == 1:
                        self._student_services.undo()
                    elif self._student_services.undo_services.undo_stack[self._student_services.undo_services.undo_pointer - 1].type == 2:
                        self._discipline_services.undo()
                    else:
                        self._discipline_services.undo()
                except UndoError:
                    self.print_undo_error()
            # Redo
            elif first_option == 7:
                try:
                    if len(self._student_services.undo_services.undo_stack) == 0:
                        raise UndoError
                    if self._student_services.undo_services.undo_stack[self._student_services.undo_services.undo_pointer - 1].type == 1:
                        self._student_services.redo()
                    elif self._student_services.undo_services.undo_stack[self._student_services.undo_services.undo_pointer - 1].type == 2:
                        self._discipline_services.redo()
                    else:
                        self._discipline_services.redo()
                except UndoError:
                    self.print_redo_error()
            # Exit
            elif first_option == 8:
                return
