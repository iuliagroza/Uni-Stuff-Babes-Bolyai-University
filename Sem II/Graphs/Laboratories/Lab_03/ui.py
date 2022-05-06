import math
import re
from exceptions import InputError, InvalidEdges, VertexError, NonexistentVertexError, EdgeError, NonexistentEdgeError
from directed_graph import DirectedGraph
from external_functions import read_graph, generate_random_graph, print_graph, lowest_cost_walk_dp, negative_cycle_detection


class UI:
    def __init__(self):
        vertices = []
        edges = []
        self.__g = DirectedGraph(vertices, edges)

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
11. Print the in-degree of a vertex.
12. Print the out-degree of a vertex.
13. Print the inbound neighbors of a given vertex.
14. Print the outbound neighbors of a given vertex.
15. Display the current graph on the console.
16. Write the representation of the current graph as a list of edges in graph_modif.txt.
17. Copy the graph.
18. Find a lowest cost walk between two given vertices.
19. Exit.""")

    @staticmethod
    def get_option():
        while True:
            try:
                ipt = input(">>> ")
                if not re.match("(^[1-9]$)|(^1[0-9]$)", ipt):
                    raise InputError
                break
            except InputError:
                print("Invalid input.")
        return int(ipt)

    def read(self):
        print("Please type the name of the file (input.txt, graph1k.txt, graph10k.txt, graph100k.txt or graph1m.txt):")
        while True:
            try:
                file_path = input(">>> ")

                if not re.match("(^input.txt$)|(^graph1k.txt$)|(^graph10k.txt$)|(^graph100k.txt)|(^graph1m.txt$)", file_path):
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

    def in_degree(self):
        print("Please provide the vertex:")
        vertex = input(">>> ")

        try:
            print(self.__g.in_degree(vertex))
        except NonexistentVertexError:
            print("The vertex you provided is not in the graph.")

    def out_degree(self):
        print("Please provide the vertex:")
        vertex = input(">>> ")

        try:
            print(self.__g.out_degree(vertex))
        except NonexistentVertexError:
            print("The vertex you provided is not in the graph.")

    def inbound(self):
        print("Please provide the vertex:")
        vertex = input(">>> ")

        try:
            if vertex not in self.__g.parse_vertices():
                raise NonexistentVertexError
            print(self.__g.parse_inbound(vertex))
        except NonexistentVertexError:
            print("The vertex you provided is not in the graph.")

    def outbound(self):
        print("Please provide the vertex:")
        vertex = input(">>> ")

        try:
            if vertex not in self.__g.parse_vertices():
                raise NonexistentVertexError
            print(self.__g.parse_outbound(vertex))
        except NonexistentVertexError:
            print("The vertex you provided is not in the graph.")

    def print_file(self):
        print_graph(self.__g, True)

    def print_console(self):
        print_graph(self.__g, False)

    def copy(self):
        G = self.__g.copy()
        print("Graph copied successfully.")

    def lowest_cost_walk(self):
        print("Please provide the source vertex:")
        source = input(">>> ")

        try:
            if source not in self.__g.parse_vertices():
                raise NonexistentVertexError
        except NonexistentVertexError:
            print("The source vertex does not exist.")

        print("Please provide the target vertex:")
        target = input(">>> ")

        try:
            if target not in self.__g.parse_vertices():
                raise NonexistentVertexError
        except NonexistentVertexError:
            print("The target vertex does not exist.")

        walk, minimum_cost = lowest_cost_walk_dp(self.__g, int(source), int(target))

        if negative_cycle_detection(self.__g, source):
            print("Negative cycle detected.")
        elif minimum_cost == math.inf:
            print(f"Vertex {target} is not accesible from vertex {source}.")
        else:
            print(f"The length of the lowest cost walk from {source} to {target} is of length {len(walk)-1} and of cost {minimum_cost}")
            print("The walk is:")
            for i in range(len(walk)-1):
                print(walk[i], end="-")
            print(walk[-1])

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
                self.in_degree()
            elif option == 12:
                self.out_degree()
            elif option == 13:
                self.inbound()
            elif option == 14:
                self.outbound()
            elif option == 15:
                self.print_console()
            elif option == 16:
                self.print_file()
            elif option == 17:
                self.copy()
            elif option == 18:
                self.lowest_cost_walk()
            else:
                break
