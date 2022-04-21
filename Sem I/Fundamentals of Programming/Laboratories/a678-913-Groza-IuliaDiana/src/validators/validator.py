import re


class Validator:
    @staticmethod
    def validate_name(name):
        """
        Validates the name "name" of a student or discipline. It can only contain letters, whitespaces and hyphens.
        :param name: string
        :return: bool
        """
        for letter in name:
            if letter != ' ' and letter != '-' and not letter.isalpha():
                return False

        return True

    @staticmethod
    def id_found(n_id, n_list):
        """
        Searches the ID "n_id" into the list of Student/Discipline objects "n_list".
        :param n_id: integer
        :param n_list: list of Student/Discipline objects
        :return: bool
        """
        for element in n_list:
            if element.id == n_id:
                return True

        return False

    @staticmethod
    def validate_id(n_id):
        """
        Validates the ID "n_id". It can only be an integer with a non-zero first digit.
        :param n_id: string
        :return: bool
        """
        if not re.match("^[1-9][0-9]*$", n_id):
            return False

        return True

    @staticmethod
    def validate_grade(grade_value):
        """
        Validates the grade "grade_value". It can only be an integer from 0 to 10 or a float value having exactly two
        (non-zero - 00) decimals.
        :param grade_value: string
        :return: bool
        """
        if not re.match("^10$|^[0-9]$|^[0-9]\.(([0-9][1-9])|([1-9][0-9]))$", grade_value):
            return False

        return True
