from validators.errors import InputError
from validators.validator import Validator


class UI:
    def __init__(self, services):
        self.__validator = Validator()
        self.__services = services

    def generate_taxis_input(self):
        print("""Welcome to Taxicab Dispatch! Please enter the number of taxis you want to randomly generate (integer number from 0 to 10): """)
        ipt = input(">>> ")
        if len(ipt.split()) != 1:
            raise InputError

        if not self.__validator.validate_number_of_taxis(ipt):
            raise InputError

        return int(ipt)

    @staticmethod
    def generate_number_of_rides():
        print(
            """Welcome to Taxicab Dispatch! Please enter the number of rides you want to randomly generate (positive integer): """)
        ipt = input(">>> ")
        if len(ipt.split()) != 1:
            raise InputError

        return int(ipt)

    def print_taxis(self):
        self.__services.repository.list.sort(key=lambda x: x.fare, reverse=True)

        for i in self.__services.repository.list:
            print(i)

    @staticmethod
    def print_main_menu():
        print("""Welcome to Taxicab Dispatch! Choose one of the following commands by typing its corresponding number: 
    1. Add a ride.
    2. Simulate rides.
    3. Exit""")

    @staticmethod
    def input_option(end):
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
            pass

    @staticmethod
    def take_ride_coordinates():
        print("Enter the coordinates of the start point: ")
        ipt = input(">>> ")

        x_start = int(ipt.split()[0])
        y_start = int(ipt.split()[1])

        print("Enter the coordinates of the end point: ")
        ipt2 = input(">>> ")

        x_end = int(ipt2.split()[0])
        y_end = int(ipt2.split()[1])

        return x_start, y_start, x_end, y_end

    @staticmethod
    def print_ride_details(number, taxi_id, x1, y1, x2, y2):
        print(f"Ride #{number+1} details: Taxi ID: {taxi_id}; Start X: {x1}; Start Y: {y1}; End X: {x2}; End Y: {y2};")

    def simulate_rides(self, n):
        for i in range(n):
            coordinates = self.__services.generate_ride()
            lst = self.__services.find_closest_taxi(coordinates[0], coordinates[1], coordinates[2], coordinates[3])
            self.__services.process_ride(lst)
            self.print_ride_details(i, lst[0], coordinates[0], coordinates[1], coordinates[2], coordinates[3])

    def start(self):
        number_of_taxis = self.generate_taxis_input()
        self.__services.generate_random_taxis(number_of_taxis)
        self.print_taxis()
        while True:
            self.print_main_menu()
            option = self.input_option(3)

            if option == 1:
                x_start, y_start, x_end, y_end = self.take_ride_coordinates()
                self.__services.process_ride(self.__services.find_closest_taxi(x_start, y_start, x_end, y_end))
                self.print_taxis()
            elif option == 2:
                number_of_rides = self.generate_number_of_rides()
                self.simulate_rides(number_of_rides)
                self.print_taxis()
            elif option == 3:
                return
