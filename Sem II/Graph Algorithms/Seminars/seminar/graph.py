import copy
import random
import time
import queue


class Graph:
    # self.out_neighbors = dict from vertex to list of neighbors
    def __init__(self, vertices=[], edges=[]):
        self.out_neighbors = {}
        for vertex in vertices:
            self.add_vertex(vertex)
        for edge in edges:
            self.add_edge(edge[0], edge[1])

    def parse_vertices(self):
        return [x for x in self.out_neighbors.keys()]

    def outbound(self, x):
        return copy.deepcopy(self.out_neighbors[x])

    def inbound(self, x):
        l = []

        for y in self.out_neighbors.keys():
            if x in self.out_neighbors[y]:
                l.append(y)

        return l

    def is_edge(self, x, y):
        return y in self.out_neighbors[x]

    def add_vertex(self, x):
        if x not in self.out_neighbors.keys():
            self.out_neighbors[x] = []
        else:
            raise ValueError("Vertex already in the graph!")

    def add_edge(self, x, y):
        if x not in self.out_neighbors.keys():
            raise ValueError(f"{x} vertex is not in the graph!")
        if y not in self.out_neighbors.keys():
            raise ValueError(f"{y} vertex is not in the graph!")
        if y in self.out_neighbors[x]:
            raise ValueError(f"Edge ({x}, {y}) is already in the graph!")

        self.out_neighbors[x].append(y)


class WolfGoatCabbageGraph:
    def parse_vertices(self):
        pass

    @staticmethod
    def outbound(x):
        return x.neighbor_states()

    @staticmethod
    def inbound(x):
        return x.neighbor_states()

    def is_edge(self, x, y):
        pass

    @staticmethod
    def initial_state():
        return WolfGoatCabbageState({x: False for x in ['W', 'G', 'C', 'B']})

    @staticmethod
    def final_state():
        return WolfGoatCabbageState({x: True for x in ['W', 'G', 'C', 'B']})


class WolfGoatCabbageState:
    def __init__(self, dict):
        self.__objects = copy.copy(dict)

    def __str__(self):
        init_string = "-"
        for key in self.__objects:
            if self.__objects[key]:
                init_string += key + init_string
        return init_string

    def __repr__(self):
        return self.__str__()

    def __eq__(self, other):
        return isinstance(other, WolfGoatCabbageState) and self.__objects == other.__objects

    def __hash__(self):
        n = 0
        powers = {
            'W': 1,
            'G': 2,
            'C': 3,
            'B': 4
        }
        for key in self.__objects:
            if self.__objects[key]:
                n += 2**powers[key]

        return n

    def is_valid(self):
        """
        Returns True if the state is valid in the sense that nobody eats anybody else.
        """
        if self.__objects['G'] == self.__objects['B']:
            return True

        if self.__objects['W'] == self.__objects['B']:
            return False

        if self.__objects['C'] == self.__objects['B']:
            return False

        return True

    def neighbor_states(self):
        """
        Returns an iterable that contains all the states reachable in one move
        """
        for key in self.__objects:
            if self.__objects[key] == self.__objects['B']:
                temp = copy.copy(self.__objects)
                temp[key] = not temp[key]
                if key != 'B':
                    temp['B'] = not temp['B']
                theState = WolfGoatCabbageState(temp)
                if theState.is_valid():
                    yield theState


def print_graph(g):
    print("Outbound")
    for x in g.parse_vertices():
        print("%s: %s" % (x, [y for y in g.outbound(x)]))
    print("Inbound")
    for x in g.parse_vertices():
        print("%s: %s" % (x, [y for y in g.inbound(x)]))


def parse_graph(g):
    print("Outbound")
    start = time.time()
    for x in g.parse_vertices():
        for y in g.outbound(x):
            pass
    print("Took %sms" % (1000 * (time.time() - start),))
    print("Inbound")
    for x in g.parse_vertices():
        for y in g.inbound(x):
            pass
    print("Took %sms" % (1000 * (time.time() - start),))


def build_graph1():
    g = Graph()
    g.add_vertex("A")
    g.add_vertex("B")
    g.add_edge("A", "B")
    return g


def build_graph2():
    g = Graph(["A", "B"])
    g.add_edge("A", "B")
    return g


def build_graph3():
    g = Graph(["A", "B", "C"], [("A", "B"), ("A", "C")])
    return g


def build_random_graph(n, m):
    g = Graph([x for x in range(n)])
    while m > 0:
        x = random.randrange(n)
        y = random.randrange(n)
        if not g.is_edge(x, y):
            g.add_edge(x, y)
            m -= 1
    return g


def shortest_path(g, s, t):
    """
    Finds the shortest path (minimum number of edges) in the graph g from vertex s to vertex t.
    Returns the path as a list of vertices starting with s and ending with t.
    If s==t, we return [s]. If there are multiple path of the same minimum length, the function will return one of them.
    Returns None if no path exists.
    """
    path = []
    distance = bfs(g, s)
    vertex = t
    path.append(vertex)

    if not t in distance.keys():
        return None

    while vertex != s:
        for neighbor in g.inbound(vertex):
            if distance[neighbor] == distance[vertex] - 1:
                vertex = neighbor
                path.append(vertex)
                break
    path.reverse()
    return path


def bfs(g, s):
    """
    Executes a BFS parse of graph
    :param g:
    :param s:
    :return:
    """
    distance = {}
    q = queue.Queue()
    q.put(s)
    while not q.empty():
        first = q.get()
        for neighbor in g.outbound(first):
            if not neighbor in distance.keys():
                distance[neighbor] = distance[first] + 1
                q.put(neighbor)
    return distance


def test_wolf_goat_cabbage():
    g = WolfGoatCabbageGraph()
    s = g.initial_state()
    t = g.final_state()
    print(s == t)
    print(s == WolfGoatCabbageState({x: False for x in ['W', 'G', 'C', 'B']}))
    print(s == 1)
    print(s)
    print(t)
    print(shortest_path(g, s, t))


def main():
    #n = 10000
    #g = build_random_graph(n, 10*n)
    #parse_graph(g)
    test_wolf_goat_cabbage()


main()
