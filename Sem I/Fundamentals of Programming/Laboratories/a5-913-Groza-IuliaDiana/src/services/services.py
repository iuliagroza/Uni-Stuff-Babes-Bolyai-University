from src.domain.domain import Complex
import copy


class Services:
    def __init__(self):
        self._numbers = Complex.generate_numbers_list()
        self._history = []

    # Getters
    @property
    def numbers(self):
        return self._numbers

    @property
    def history(self):
        return self._history

    # Setters
    @numbers.setter
    def numbers(self, new_numbers):
        self._numbers = new_numbers

    # Functionalities
    def add_number(self, command):
        """
        Appends a number to the list of complex numbers. Its properties are read from the console.
        :param command: string
        """
        self.add_undo()

        real = int(command.split()[0])
        imaginary = int(command.split()[2].strip("i"))
        number = Complex(real, imaginary)  # Create an instance of Complex

        self.numbers.append(number)

    def validate_range(self, start, end):
        """
        Function used to logically validate the input for the filter_numbers() function. If start and end are reversed
        or they're not in the [0, len(self.get_numbers()] range, we raise IndexError.
        :param start:
        :param end:
        :return:
        """
        if start < 0:
            raise IndexError
        if end > len(self.numbers):
            raise IndexError
        if start > end:
            raise IndexError

    def filter_numbers(self, command):
        """
        Implements the filter command.
        :param command: string
        """
        start = int(command.split()[0])
        end = int(command.split()[1])

        self.validate_range(start, end)

        self.add_undo()
        self.numbers = self.numbers[start:end+1]

    def add_undo(self):
        """
        Appends a list version to the history in the undo process.
        """
        self.history.append(copy.deepcopy(self.numbers))

    def undo(self):
        """
        Implements the undo operation. We remove the last version of the list from the history and append it to
        the current list.
        """
        if len(self.history) == 0:
            raise IndexError
        self.numbers = self.history.pop()
