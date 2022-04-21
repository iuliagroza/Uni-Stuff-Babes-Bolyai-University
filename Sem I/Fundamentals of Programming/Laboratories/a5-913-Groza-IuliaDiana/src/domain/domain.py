import random


class Complex:
    def __init__(self, real, imaginary):
        self._real = real
        self._imaginary = imaginary

    def __str__(self):
        """
        Converts the number into string representation.
        :return: string
        """
        return f"{self.real} + {self.imaginary}i"

    # Getters
    @property
    def real(self):
        return self._real

    @property
    def imaginary(self):
        return self._imaginary

    # Setters
    @real.setter
    def real(self, new_real):
        self._real = new_real

    @imaginary.setter
    def imaginary(self, new_imaginary):
        self._imaginary = new_imaginary

    # Predefined
    @staticmethod
    def generate_numbers_list():
        """
        Function used to programmatically generate a list of 10 complex numbers,
        whose real and imaginary part are from range [-100, 100].
        :return: list of instances of Complex
        """
        numbers_list = []

        for i in range(10):
            real_part = random.randint(-100, 100)
            imaginary_part = random.randint(-100, 100)
            number = Complex(real_part, imaginary_part)
            numbers_list.append(number)

        return numbers_list
