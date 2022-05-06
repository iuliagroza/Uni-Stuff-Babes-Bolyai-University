from copy import deepcopy
from exceptions import VertexError, NonexistentVertexError, EdgeError, NonexistentEdgeError


class DirectedGraph:
    """
    CONSTRUCTOR
    """
    def __init__(self, vertices, edges):
        self.__vertices = []
        self.__edges = []
        self.__costs = {}
        self.__outbound = {}
        self.__inbound = {}

        for vertex in vertices:
            self.add_vertex(vertex)

        for edge in edges:
            self.add_edge(edge[0], edge[1], edge[2])

    """
    GETTERS
    """
    @property
    def edges(self):
        return self.__edges

    @property
    def costs(self):
        return self.__costs

    def get_number_of_vertices(self):
        return len(self.__vertices)

    def get_number_of_edges(self):
        return len(self.__edges)

    """
    ITERATORS
    """
    def parse_vertices(self):
        return [vertex for vertex in self.__vertices]

    def parse_edges(self):
        return [edge for edge in self.__edges]

    def parse_inbound(self, x):
        return [y for y in self.__inbound[x]]

    def parse_outbound(self, x):
        return [y for y in self.__outbound[x]]

    """
    FUNCTIONALITIES
    """
    def add_vertex(self, x):
        """
        Adds a vertex to the graph. If the vertex already exists in the graph, VertexError will be raised.
        Runtime: O(n), where n is the number of vertices (because of validation)
        :param x: integer (vertex)
        """
        if x in self.parse_vertices():
            raise VertexError
        self.__vertices.append(x)
        self.__outbound[x] = []
        self.__inbound[x] = []

    def add_vertex_valid(self, x):
        """
        Adds a vertex to the graph. If the vertex already exists in the graph, VertexError will be raised.
        Runtime: O(1)
        :param x: integer (vertex)
        """
        self.__vertices.append(x)
        self.__outbound[x] = []
        self.__inbound[x] = []

    def remove_vertex(self, x):
        """
        Removes a vertex from the graph. All edges containing x as the origin or target vertex, The outbound and inbound
        lists of x will be deleted (using self.remove_edge()). If x is not a vertex, an error will be raised.
        Runtime: O(max(n, m)), where n is the number of vertices and m the number of edges
        :param x: integer (vertex)
        """
        if x not in self.parse_vertices():
            raise NonexistentVertexError

        for edge in self.parse_edges():
            if edge[0] == x or edge[1] == x:
                self.remove_edge(edge[0], edge[1])
        del self.__outbound[x]
        del self.__inbound[x]
        self.__vertices.remove(x)

    def add_edge(self, x, y, c):
        """
        Adds an edge to the graph. If x or y are not vertices or the edge already exists in the graph, an error will be
        raised.
        Runtime: O(max(n, m)), where n is the number of vertices and m the number of edges (because of validation)
        :param x: integer (vertex)
        :param y: integer (vertex)
        :param c: integer
        """
        if x not in self.parse_vertices():
            raise NonexistentVertexError
        if y not in self.parse_vertices():
            raise NonexistentVertexError
        if (x, y) in self.parse_edges():
            raise EdgeError
        self.__edges.append((x, y))
        self.__outbound[x].append(y)
        self.__inbound[y].append(x)
        self.__costs[(x, y)] = c

    def add_edge_valid(self, x, y, c):
        """
        Adds an edge to the graph. If x or y are not vertices or the edge already exists in the graph, an error will be
        raised.
        Runtime: O(1)
        :param x: integer (vertex)
        :param y: integer (vertex)
        :param c: integer
        """
        self.__edges.append((x, y))
        self.__outbound[x].append(y)
        self.__inbound[y].append(x)
        self.__costs[(x, y)] = c

    def remove_edge(self, x, y):
        """
        Removes a given edge from the graph. Its cost, y as the outbound of x and x as the inbound of y will be deleted.
        If x or y are not vertices or (x, y) is not an edge, an error will be raised.
        Runtime: O(m), where m is the number of edges
        :param x:
        :param y:
        :return:
        """
        if x not in self.parse_vertices():
            raise NonexistentVertexError
        if y not in self.parse_vertices():
            raise NonexistentVertexError
        if (x, y) not in self.parse_edges():
            raise NonexistentEdgeError

        self.__edges.remove((x, y))
        del self.__costs[(x, y)]
        self.__outbound[x].remove(y)
        self.__inbound[y].remove(x)

    def update_edge(self, x, y, new_cost):
        """
        Updates the cost of an edge. If there is no x or y vertex or no (x, y) edge, an error is raised.
        Runtime: O(1)
        :param x: integer (vertex)
        :param y: integer (vertex)
        :param new_cost: integer
        """
        if x not in self.parse_vertices():
            raise NonexistentVertexError
        if y not in self.parse_vertices():
            raise NonexistentVertexError
        if (x, y) not in self.parse_edges():
            raise NonexistentEdgeError

        self.__costs[(x, y)] = new_cost

    def is_edge(self, x, y):
        """
        Checks if there is an edge in the graph that has the origin x and the target y (returns True if it finds the
        given edge, False otherwise). If x or y are not vertices, an error is raised.
        Runtime: O(deg(x) + deg(y)), where deg(i) = the degree of vertex i
        :param x: integer (vertex)
        :param y: integer (vertex)
        :return: boolean
        """
        if x not in self.parse_vertices():
            raise NonexistentVertexError
        if y not in self.parse_vertices():
            raise NonexistentVertexError

        if y in self.__outbound[x] and x in self.__inbound[y]:
            return True
        return False

    def in_degree(self, x):
        """
        Returns the in degree of a vertex x. If x is not a vertex, an error is raised.
        Runtime: O(1)
        :param x: integer (vertex)
        :return: integer
        """
        if x not in self.parse_vertices():
            raise NonexistentVertexError

        return len(self.__inbound[x])

    def out_degree(self, x):
        """
        Returns the out degree of a vertex x. If x is not a vertex, an error is raised.
        Runtime: O(1)
        :param x: integer (vertex)
        :return: integer
        """
        if x not in self.parse_vertices():
            raise NonexistentVertexError

        return len(self.__outbound[x])

    def copy(self):
        """
        Returns a deepcopy of the graph.
        Runtime: O(1)
        :return: DirectedGraph object
        """
        return deepcopy(self)
