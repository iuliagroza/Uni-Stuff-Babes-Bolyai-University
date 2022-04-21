import re


class Validator:
    @staticmethod
    def validate_number_of_taxis(number):
        if not re.match("^([0-9]|10){1}$", number):
            return False
        return True
