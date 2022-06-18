from copy import deepcopy

from exceptions import VertexError, NonexistentVertexError, EdgeError, NonexistentEdgeError


class UndirectedGraph:
    def __init__(self, vertices, edges):
        self.__vertices = []
        self.__edges = []
        self.__costs = {}
        self.__neighbours = {}

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

    def parse_neighbours(self, x):
        return [neighbour for neighbour in self.__neighbours[x]]

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
        self.__neighbours[x] = []

    def add_vertex_valid(self, x):
        """
        Adds a vertex to the graph. If the vertex already exists in the graph, VertexError will be raised.
        Runtime: O(1)
        :param x: integer (vertex)
        """
        self.__vertices.append(x)
        self.__neighbours[x] = []

    def remove_vertex(self, x):
        """
        Removes a vertex from the graph. All edges containing x as a vertex, the neighbours
        lists of x will be deleted (using self.remove_edge()). If x is not a vertex, an error will be raised.
        Runtime: O(max(n, m)), where n is the number of vertices and m the number of edges
        :param x: integer (vertex)
        """
        if x not in self.parse_vertices():
            raise NonexistentVertexError

        for edge in self.parse_edges():
            if edge[0] == x or edge[1] == x:
                self.remove_edge(edge[0], edge[1])
        del self.__neighbours[x]
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

        if y < x:
            x, y = y, x
        if (x, y) in self.parse_edges():
            raise EdgeError

        self.__edges.append((x, y))
        self.__neighbours[x].append(y)
        self.__neighbours[y].append(x)
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
        if y < x:
            x, y = y, x
        self.__edges.append((x, y))
        self.__neighbours[x].append(y)
        self.__neighbours[y].append(x)
        self.__costs[(x, y)] = c

    def remove_edge(self, x, y):
        """
        Removes a given edge from the graph. Its cost, y as the neighbour of x and x as the neighbour of y will be deleted.
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

        if y < x:
            x, y = y, x
        if (x, y) not in self.parse_edges():
            raise NonexistentEdgeError

        self.__edges.remove((x, y))
        del self.__costs[(x, y)]
        self.__neighbours[x].remove(y)
        self.__neighbours[y].remove(x)

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

        if y < x:
            x, y = y, x
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

        if y in self.__neighbours[x] and x in self.__neighbours[y]:
            return True
        return False

    def degree(self, x):
        """
        Returns the degree of a vertex x. If x is not a vertex, an error is raised.
        Runtime: O(1)
        :param x: integer (vertex)
        :return: integer
        """
        if x not in self.parse_vertices():
            raise NonexistentVertexError

        return len(self.__neighbours[x])

    def copy(self):
        """
        Returns a deepcopy of the graph.
        Runtime: O(1)
        :return: UndirectedGraph object
        """
        return deepcopy(self)

    def get_vertex_root(self, vertex, vertex_root):
        """
        Function that returns the vertex_root[] value on the position vertex.
        Runtime: O(M), where M is the maximum length of the path from a vertex to its root.
        :param vertex: integer (vertex)
        :param vertex_root: list of integers
        :return: integer (vertex)
        """
        if vertex_root[vertex] == vertex:
            return vertex
        return self.get_vertex_root(vertex_root[vertex], vertex_root)

    def edge_can_be_added(self, vertex_root, first_vertex, second_vertex):
        """
        Checks if an edge can be added into the Hamiltonian cycle of low cost (the vertices don't have the same root and
        their degree is one).
        Runtime: O(1)
        :param vertex_root: list of integers
        :param first_vertex: integer (vertex)
        :param second_vertex: integer (vertex)
        :return: boolean
        """
        degree_of_first_vertex = self.degree(first_vertex)
        degree_of_second_vertex = self.degree(second_vertex)
        root_of_first_vertex = self.get_vertex_root(first_vertex, vertex_root)
        root_of_second_vertex = self.get_vertex_root(second_vertex, vertex_root)

        return root_of_first_vertex != root_of_second_vertex and degree_of_first_vertex < 2 and degree_of_second_vertex < 2

    def change_vertex_parent_array(self, vertex_root, first_vertex, second_vertex):
        """
        Updates the root of a vertex when it is added to a Hamiltonian cycle (it receives the root of its neighbour).
        Runtime: O(1)
        :param vertex_root: list of integers
        :param first_vertex: integer (vertex)
        :param second_vertex: integer (vertex)
        """
        if self.degree(first_vertex) > 0:
            vertex_root[second_vertex] = vertex_root[first_vertex]
        elif self.degree(second_vertex) > 0:
            vertex_root[first_vertex] = vertex_root[second_vertex]
        elif vertex_root[first_vertex] > vertex_root[second_vertex]:
            vertex_root[second_vertex] = vertex_root[first_vertex]
        else:
            vertex_root[first_vertex] = vertex_root[second_vertex]

    def get_hamiltonian_cycle(self):
        """
        Function that determines a Hamiltonian cycle of low cost (approximate TSP). We sort the edges and initially set
        each of the vertices root to be themselves. Then, for each edge, we check if it does not already belong to the
        cycle and that it won't "mess up" the cycle (each of its vertex should have the degree one, so once added, the
        vertices will have exactly two neighbours, just like in a cycle). In this case, we add the edge to the cycle by
        changing each of its vertices their root, so that they'll belong to the same cycle.
        Runtime: O(E*logE), where E is the number of edges of the undirected graph
        :return: UndirectedGraph object and integer
        """
        ordered_edges = dict(sorted(self.__costs.items(), key=lambda v: v[1]))
        cost = 0

        cycle_H = UndirectedGraph(self.__vertices, [])

        vertex_root = {}
        for vertex in cycle_H.parse_vertices():
            vertex_root[vertex] = vertex

        for edge in ordered_edges:
            if cycle_H.get_number_of_edges() == cycle_H.get_number_of_vertices() - 1:
                break
            if cycle_H.edge_can_be_added(vertex_root, edge[0], edge[1]):
                cycle_H.change_vertex_parent_array(vertex_root, edge[0], edge[1])
                if edge[0] > edge[1]:
                    edge[0], edge[1] = edge[1], edge[0]
                cycle_H.add_edge(edge[0], edge[1], self.__costs[edge])
                cost += self.__costs[edge]

        start_vertex = -1
        end_vertex = -1
        for vertex in cycle_H.__neighbours:
            if cycle_H.degree(vertex) == 1:
                if start_vertex == -1:
                    start_vertex = vertex
                else:
                    end_vertex = vertex
                    break
        if end_vertex > start_vertex:
            start_vertex, end_vertex = end_vertex, start_vertex
        cycle_H.add_edge(end_vertex, start_vertex, self.__costs[(end_vertex, start_vertex)])
        cost += cycle_H.__costs[(end_vertex, start_vertex)]

        hamiltonian_cycle = [start_vertex]
        vertex = cycle_H.__neighbours[start_vertex][0]
        while vertex != start_vertex:
            hamiltonian_cycle.append(vertex)
            if cycle_H.__neighbours[vertex][0] in hamiltonian_cycle:
                vertex = cycle_H.__neighbours[vertex][1]
            else:
                vertex = cycle_H.__neighbours[vertex][0]
        hamiltonian_cycle.append(start_vertex)

        return hamiltonian_cycle, cost
