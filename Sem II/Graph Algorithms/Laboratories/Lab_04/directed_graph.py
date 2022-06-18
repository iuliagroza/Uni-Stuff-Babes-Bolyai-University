from collections import deque
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
        self.__duration = [] * len(vertices)  # the duration of activity i
        self.__earliest_start = [-999999] * len(vertices)  # the earliest time when activity i begins
        self.__earliest_end = [-999999] * len(vertices)  # the earliest time when activity i ends
        self.__latest_start = [999999] * len(vertices)  # the time at the latest when activity i begins
        self.__latest_end = [999999] * len(vertices)  # the time at the latest when activity i ends

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

    def set_duration(self, times):
        self.__duration = times

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
        Runtime: O(V), where V is the number of vertices (because of validation)
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
        Runtime: O(max(V, E)), where V is the number of vertices and E the number of edges
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
        Runtime: O(max(V, E)), where V is the number of vertices and E the number of edges (because of validation)
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
        Runtime: O(E), where E is the number of edges
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

    def topological_sorting(self):
        """
        Checks if the corresponding graph is a DAG and performs a topological sorting of the
        activities using the algorithm based on predecessor counters.
        Firstly, we add to the queue (implemented with a deque) the vertices whose in-degree is 0 (they do not have any
        inbound edges). These are the activities with no predecessor. Then, we repeatedly extract the front of the queue
        the first activity with no predecessor, add it to sorted_list and "eliminate" it from the graph (mark it with -1
        in the counter dictionary) until the queue is not empty. Finally, if the sorted_list does not contain all the
        vertices, it means that the graph is not a DAG (thus, topological sorting cannot be applied).
        Runtime: O(V+E), where V is the number of vertices and E the number of edges in the graph
        :return: list() of sorted vertices
        """
        sorted_vertices = list()
        Q = deque()
        counter = {}

        for vertex in self.parse_vertices():
            counter[vertex] = self.in_degree(vertex)
            if counter[vertex] == 0:
                Q.append(vertex)

        while len(Q) != 0:
            vertex = Q.popleft()
            sorted_vertices.append(vertex)
            for neighbour in self.parse_outbound(vertex):
                counter[neighbour] -= 1
                if counter[neighbour] == 0:
                    Q.append(neighbour)

        if len(sorted_vertices) < self.get_number_of_vertices():
            sorted_vertices = []

        return sorted_vertices

    def get_times(self):
        """
        Finds the earliest and the latest starting time for each activity and the total time of the project.
        Firstly, we topologically sort the graph associated to the list of activities and for each activity, we check
        what is the maximum earliest end date for one of its predecessors and that will be the earliest start date of
        the current activity. If the activity has no predecessors, its earliest start time is 0. Finally, knowing the
        duration, we can compute the earliest end time. We proceed similarly for the latest start/end time.
        Runtime: O(V+E), where V is the number of vertices and E the number of edges in the graph
        :return: -1 5 times, if the graph is a DAG
                 5 integers (the earliest start time, the earliest end time, the latest start time, the latest end time and the
                 total duration of the project), otherwise
        """
        sorted_vertices = self.topological_sorting()
        self.__earliest_start = [-999999] * self.get_number_of_vertices()
        self.__earliest_end = [-999999] * self.get_number_of_vertices()
        self.__latest_start = [999999] * self.get_number_of_vertices()
        self.__latest_end = [999999] * self.get_number_of_vertices()

        for vertex in sorted_vertices:
            if self.in_degree(vertex) == 0:
                self.__earliest_start[vertex] = 0
            else:
                for neighbour in self.parse_inbound(vertex):
                    self.__earliest_start[vertex] = max(self.__earliest_start[vertex], self.__earliest_end[neighbour])
            self.__earliest_end[vertex] = self.__earliest_start[vertex] + self.__duration[vertex]

        sorted_vertices.reverse()
        for vertex in sorted_vertices:
            if self.out_degree(vertex) == 0:
                self.__latest_end[vertex] = self.__earliest_end[sorted_vertices[0]]
            for neighbour in self.parse_outbound(vertex):
                self.__latest_end[vertex] = min(self.__latest_end[vertex], self.__latest_start[neighbour])
            self.__latest_start[vertex] = self.__latest_end[vertex] - self.__duration[vertex]

        if not sorted_vertices:
            return -1, -1, -1, -1, -1
        return self.__earliest_start, self.__earliest_end, self.__latest_start, self.__latest_end, self.__latest_end[
            sorted_vertices[0]]

    def critical_activities(self):
        """
        Returns a list of the critical activities. A critical activity has a total time reserve of 0 (that means that
        its earliest start time is equal to the latest start time - it can only be done at that certain time).
        Runtime: O(V+E), where V is the number of vertices and E the number of edges in the graph
        :return: list of integers (activities/vertices of the DAG)
        """
        a = self.get_times()
        critical = []

        for i in range(self.get_number_of_vertices()):
            if self.__earliest_start[i] == self.__latest_start[i]:
                critical.append(i)

        return critical
