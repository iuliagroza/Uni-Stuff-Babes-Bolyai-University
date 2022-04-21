from src.services.services import Services
from src.domain.domain import Complex
from src.services.tests import Tests
import re


class RegexError(Exception):
    """
    Raised when a string doesn't match a given regex
    """
    pass


class UI:
    def __init__(self):
        self._services = Services()

    # Getters
    @property
    def services(self):
        return self._services

    # I/O
    @staticmethod
    def print_add():
        print("""Please introduce the number in an "a + bi" form.""")

    @staticmethod
    def print_filter():
        print("Please type the values of start and end separated by a whitespace (null or positive integers).")

    @staticmethod
    def print_menu():
        print("""Please select an option by typing its corresponding number:
            1. Add a number in an "a + bi" form.
            2. Display the list of numbers.
            3. Filter the list so that it contains only the numbers between indices start and end.
            4. Undo the last operation.
            5. Exit""")

    @staticmethod
    def read_option(regex):
        """
        Reads and validates the input of options by checking if they match with a given regex.
        :param regex: string
        """
        command = input(">>> ")

        if re.match(regex, command):
            return command

        raise RegexError

    @staticmethod
    def invalid_input():
        print("Invalid input.")

    @staticmethod
    def invalid_range():
        print("The indices either are reversed or at least one of them does not exist.")

    @staticmethod
    def undo_error():
        print("There are no more operations to undo.")

    def print_numbers(self):
        """
        Implements the display functionality. Formatting is used.
        """
        if len(self.services.numbers) == 1:  # The list contains one element
            num = Complex(self.services.numbers[0].real, self.services.numbers[0].imaginary)
            print("[" + str(num) + "i]")
        else:
            for i in range(len(self.services.numbers)):
                num = Complex(self.services.numbers[i].real, self.services.numbers[i].imaginary)
                if i == 0:  # First element of the list
                    print("[" + str(num) + ", ", end="")
                elif i == len(self.services.numbers) - 1:  # Last element of the list
                    print(str(num) + "]")
                else:  # Middle element
                    print(str(num) + ", ", end="")

    # Start
    def start(self):
        """
        Main function
        """
        while True:
            self.print_menu()

            try:
                option = int(self.read_option("^[1-5]{1}$"))

                # First functionality
                if option == 1:
                    self.print_add()
                    number = self.read_option("^-?[0-9]+ \+ -?[0-9]+i$")
                    self.services.add_number(number)
                # Second functionality
                elif option == 2:
                    self.print_numbers()
                # Third functionality
                elif option == 3:
                    self.print_filter()
                    number = self.read_option("^[0-9]+ [0-9]+$")

                    try:
                        self.services.filter_numbers(number)
                    except IndexError:
                        self.invalid_range()
                # Fourth functionality
                elif option == 4:
                    try:
                        self.services.undo()
                    except IndexError:
                        self.undo_error()
                # Exit
                else:
                    return
            except RegexError:
                self.invalid_input()


if __name__ == "__main__":
    test = Tests()
    test.test()
    ui = UI()
    # Main call
    ui.start()
