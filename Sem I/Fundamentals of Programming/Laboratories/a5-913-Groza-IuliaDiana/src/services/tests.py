from src.domain.domain import Complex
from src.services.services import Services


class Tests:
    def __init__(self):
        self._services = Services()

    # Getters
    @property
    def services(self):
        return self._services

    def test_numbers(self):
        """
        Tests numbers getter.
        """
        assert(self.services._numbers == self.services.numbers)

    def test_history(self):
        """
        Tests history getter.
        """
        assert(self.services._history == self.services.history)

    def test_set_numbers(self):
        """
        Tests numbers setter.
        """
        n1 = Complex(0, -1)
        n2 = Complex(12, 7)
        n3 = Complex(11, -6)
        self.services.numbers = [n1, n2, n3]

        assert(self.services._numbers == self.services.numbers)

        self.services.numbers = []

    def test_add_undo(self):
        """
        Tests add_undo() function.
        """
        n1 = Complex(0, -1)
        n2 = Complex(12, 7)
        n3 = Complex(11, -6)

        self.services.numbers = [str(n1), str(n2), str(n3)]
        self.services.add_undo()

        assert(list(self.services.history) == [[str(n1), str(n2), str(n3)]])

        self.services.undo()
        self.services.numbers = []

    def test_add_number(self):
        """
        Tests add_number() function.
        """
        self.services.add_number("0 + -4i")

        assert(str(self.services.numbers[-1]) == str(Complex(0, -4)))

        self.services.numbers.pop()

    def test(self):
        """
        Main test function
        """
        self.test_add_undo()
        self.test_add_number()
        self.test_numbers()
        self.test_history()
        self.test_set_numbers()
