import re
from exceptions import InputError, InvalidEdges, VertexError, NonexistentVertexError, EdgeError, NonexistentEdgeError
from external_functions import read_graph, generate_random_graph, print_graph, bfs_connected_components, \
    get_hamiltonian_cycle
from undirected_graph import UndirectedGraph


class UI:
    def __init__(self):
        vertices = []
        edges = []
        self.__g = UndirectedGraph(vertices, edges)

    @staticmethod
    def print_main_menu():
        print("""Choose one of the following operations:
1. Read a graph from a file (and overwrite the current graph).
2. Generate a random graph with a given number of vertices and edges (and overwrite the current graph).
3. Add a vertex to the current graph.
4. Remove a vertex from the current graph.
5. Add an edge to the current graph.
6. Remove an edge from the current graph.
7. Update the cost of an edge of the current graph.
8. Check if an edge exists in the current graph.
9. Print the number of vertices of the current graph.
10. Print the vertices of the current graph.
11. Print the degree of a vertex.
12. Print the neighbors of a given vertex.
13. Display the current graph on the console.
14. Write the representation of the current graph as a list of edges in graph_modif.txt.
15. Copy the graph.
16. Find the connected components of an undirected graph using BFS.
17. Find a Hamiltonian cycle of low cost (approximate TSP).
18. Exit.""")

    @staticmethod
    def get_option():
        while True:
            try:
                ipt = input(">>> ")
                if not re.match("(^[1-9]$)|(^1[0-8]$)", ipt):
                    raise InputError
                break
            except InputError:
                print("Invalid input.")
        return int(ipt)

    def read(self):
        print("Please type the name of the file (input1.txt/input2.txt):")
        while True:
            try:
                file_path = input(">>> ")

                if not re.match("(^input1.txt$)|(^input2.txt$)", file_path):
                    raise InputError
                break
            except InputError:
                print("Invalid input.")
        self.__g = read_graph(file_path)
        print("Graph read successfully.")

    @staticmethod
    def generate():
        l = []
        while True:
            try:
                print("Please type the number of vertices:")
                n = input(">>> ")

                if not n.isnumeric():
                    raise InputError

                n = int(n)

                if n < 0 or n > 1000000:
                    raise InputError

                l.append(n)
                break
            except InputError:
                print("Invalid number.")

        while True:
            try:
                print("Please type the number of edges:")
                m = input(">>> ")

                if not m.isnumeric():
                    raise InputError

                m = int(m)

                if m < 0 or m > 1000000000000:
                    raise InputError

                l.append(m)
                break
            except InputError:
                print("Invalid number.")

        while True:
            try:
                print("Please type the name of the file in which you would like the graph to be saved (random_graph1.txt or random_graph2.txt):")
                file_path = input(">>> ")

                if not re.match("(^random_graph1.txt$)|(^random_graph2.txt$)", file_path):
                    raise InputError

                l.append(file_path)
                break
            except InputError:
                print("Invalid input.")

        try:
            generate_random_graph(l[0], l[1], l[2])
            print("Generation done.")
        except InvalidEdges:
            print("The number of edges must be smaller or equal to the number of vertices squared (m <= n^2).")

    def add_vertex(self):
        print("Please provide the new vertex:")
        vertex = input(">>> ")

        try:
            self.__g.add_vertex(vertex)
            print("Vertex added successfully.")
        except VertexError:
            print("The vertex you provided already exists in the graph.")

    def remove_vertex(self):
        print("Please provide the vertex:")
        vertex = input(">>> ")

        try:
            self.__g.remove_vertex(vertex)
            print("Vertex deleted successfully.")
        except NonexistentVertexError:
            print("The vertex you provided does not exist in the graph.")

    def add_edge(self):
        print("Please provide the source:")
        x = input(">>> ")

        print("Please provide the target:")
        y = input(">>> ")

        print("Please provide the cost:")
        while True:
            try:
                c = input(">>> ")

                if not c.isnumeric():
                    raise InputError

                c = int(c)
                break
            except InputError:
                print("Invalid cost. Please provide an integer.")

        try:
            self.__g.add_edge(x, y, c)
            print("Edge added successfully.")
        except NonexistentVertexError:
            print("At least one of the vertices you provided are not in the graph.")
        except EdgeError:
            print("The edge already exists in the graph.")

    def remove_edge(self):
        print("Please provide the source:")
        x = input(">>> ")

        print("Please provide the target:")
        y = input(">>> ")

        try:
            self.__g.remove_edge(x, y)
            print("Edge removed successfully.")
        except NonexistentVertexError:
            print("The vertices you provided do not exist.")
        except NonexistentEdgeError:
            print("The edge you provided does not exist.")

    def update_edge(self):
        print("Please provide the source:")
        x = input(">>> ")

        print("Please provide the target:")
        y = input(">>> ")

        print("Please provide the new cost:")
        while True:
            try:
                c = input(">>> ")

                if not c.isnumeric() and c[0] != "-":
                    raise InputError

                c = int(c)
                break
            except InputError:
                print("Invalid cost. Please provide an integer.")

        try:
            self.__g.update_edge(x, y, c)
            print("Edge updated successfully.")
        except NonexistentVertexError:
            print("At least one of the vertices you provided are not in the graph.")
        except NonexistentEdgeError:
            print("The edge does not exist in the graph.")

    def is_edge(self):
        print("Please provide the source:")
        x = input(">>> ")

        print("Please provide the target:")
        y = input(">>> ")

        try:
            result = self.__g.is_edge(x, y)
            if result:
                print(f"There is an edge between {x} and {y}.")
            else:
                print(f"There is no edge between {x} and {y}.")
        except NonexistentVertexError:
            print("At least one of the vertices you provided are not in the graph.")

    def number_vertices(self):
        print(self.__g.get_number_of_vertices())

    def vertices(self):
        print(self.__g.parse_vertices())

    def degree(self):
        print("Please provide the vertex:")
        vertex = input(">>> ")

        try:
            print(self.__g.degree(vertex))
        except NonexistentVertexError:
            print("The vertex you provided is not in the graph.")

    def neighbours(self):
        print("Please provide the vertex:")
        vertex = input(">>> ")

        try:
            if vertex not in self.__g.parse_vertices():
                raise NonexistentVertexError
            print(self.__g.parse_neighbours(vertex))
        except NonexistentVertexError:
            print("The vertex you provided is not in the graph.")

    def print_file(self):
        print_graph(self.__g, True)

    def print_console(self):
        print_graph(self.__g, False)

    def copy(self):
        G = self.__g.copy()
        print("Graph copied successfully.")

    def connected_components(self):
        connected_components = bfs_connected_components(self.__g)
        count = 1

        for component in connected_components:
            print(f"Connected component #{count}:")
            count += 1
            print("Vertices:")
            for vertex in component.parse_vertices():
                print(vertex)
            print("Edges:")
            for edge in component.parse_edges():
                print(f"{edge[0]} {edge[1]} {self.__g.costs[(edge[0], edge[1])]}")
            if component.get_number_of_edges() == 0:
                print("There are no edges.")
            print_graph(component, True)

    def get_hamiltonian_cycle(self):
        vertices_number = self.__g.get_number_of_vertices()
        if vertices_number == 0:
            print("The graph is empty.")
        else:
            try:
                cycle, cost = get_hamiltonian_cycle(self.__g)
                print("The hamiltonian cycle has the cost:", cost)
                print("The hamiltonian cycle is:")
                i = 0
                while i < len(cycle) - 1:
                    print(cycle[i], "- ", end='')
                    i += 1
                print(cycle[i])
                print()
            except InvalidEdges:
                print("The provided graph is not complete.")

    def start(self):
        while True:
            self.print_main_menu()
            option = self.get_option()
            if option == 1:
                self.read()
            elif option == 2:
                self.generate()
            elif option == 3:
                self.add_vertex()
            elif option == 4:
                self.remove_vertex()
            elif option == 5:
                self.add_edge()
            elif option == 6:
                self.remove_edge()
            elif option == 7:
                self.update_edge()
            elif option == 8:
                self.is_edge()
            elif option == 9:
                self.number_vertices()
            elif option == 10:
                self.vertices()
            elif option == 11:
                self.degree()
            elif option == 12:
                self.neighbours()
            elif option == 13:
                self.print_console()
            elif option == 14:
                self.print_file()
            elif option == 15:
                self.copy()
            elif option == 16:
                self.connected_components()
            elif option == 17:
                self.get_hamiltonian_cycle()
            else:
                break
