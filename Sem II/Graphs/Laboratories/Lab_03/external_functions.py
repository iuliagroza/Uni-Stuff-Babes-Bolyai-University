import math
from random import randrange
from directed_graph import DirectedGraph
from exceptions import InvalidEdges


def generate_random_graph(n, m, file_path):
    """
    Function that generates a random graph with a given number of vertices and edges. The cost will be an integer from
    the interval [0, 1.000.000]. If the number of edges is invalid an error will be raised. The graph will be written in
    the text file having the path file_path.
    :param file_path: path of the file in which the graph will be saved
    :param n: integer (number of vertices)
    :param m: integer (number of edges)
    :return: DirectedGraph object
    """
    if m > n**2:
        raise InvalidEdges

    vertices = []
    for i in range(n):
        vertices.append(str(i))

    edges = []
    while len(edges) < m:
        x = randrange(n)
        y = randrange(n)
        cost = randrange(-1000000, 1000000)

        ok = 1
        for edge in edges:
            if edge[0] == x and edge[1] == y:
                ok *= -1

        if ok == 1:
            edges.append((x, y, cost))

    G = DirectedGraph(vertices, edges)

    with open(file_path, "w") as f:
        f.write(str(G.get_number_of_vertices()) + " ")
        f.write(str(G.get_number_of_edges()) + "\n")

        for edge in G.parse_edges():
            f.write(f"{edge[0]} {edge[1]} {G.costs[(edge[0], edge[1])]}\n")


def read_graph(file_path):
    """
    Function that reads a graph from a text file with the path file_path.
    :param file_path: the path of the file from which the graph will be read
    :return: DirectedGraph object
    """
    vertices = []
    edges = []

    G = DirectedGraph(vertices, edges)

    with open(file_path) as f:
        line = f.readline()
        line = line.strip(" \n")
        n = int(line.split(" ")[0])

        for i in range(n):
            G.add_vertex_valid(str(i))

        for line in f.readlines():
            line = line.strip(" \n")
            x = line.split(" ")[0]
            y = line.split(" ")[1]
            c = int(line.split(" ")[2])

            G.add_edge_valid(x, y, c)
    return G


def print_graph(G, option):
    """
    Function that prints a DirectedGraph object depending on the option of the user. If option == False, the graph will be
    displayed on the console. Otherwise, the graph will be written in the graph_modif.txt file. The graph is represented as
    a list of edges (associated to their costs).
    :param G: DirectedGraph object
    :param option: boolean
    """
    if not option:
        print(str(G.get_number_of_vertices()) + " " + str(G.get_number_of_edges()))

        for edge in G.parse_edges():
            print(f"{edge[0]} {edge[1]} {G.costs[(edge[0], edge[1])]}")
    else:
        with open("graph_modif.txt", "w") as f:
            f.write(str(G.get_number_of_vertices()) + " ")
            f.write(str(G.get_number_of_edges()) + "\n")

            for edge in G.parse_edges():
                f.write(f"{edge[0]} {edge[1]} {G.costs[(edge[0], edge[1])]}\n")


def negative_cycle_detection(G, source):
    """
    Function that checks if a directed graph (DirectedGraph object) contains a negative cycle, using the Bellman-Ford
    algorithm.
    Time-Complexity: O(V^2*E), where V is the number of vertices and E the number of edges
    :param G: DirectedGraph object
    :param source: string (later converted to integer)
    :return: boolean (True if a negative cycle was detected, False otherwise)
    """
    V = G.get_number_of_vertices()

    dp = [math.inf for x in range(V)]
    dp[int(source)] = 0

    for i in range(1, V):
        for vertex in G.parse_vertices():
            for neighbour in G.parse_outbound(vertex):
                cost = G.costs[(vertex, neighbour)]
                if dp[int(vertex)] + cost < dp[int(neighbour)] and dp[int(vertex)] != math.inf:
                    dp[int(neighbour)] = dp[int(vertex)] + cost

    for vertex in G.parse_vertices():
        for neighbour in G.parse_outbound(vertex):
            cost = G.costs[(vertex, neighbour)]
            if dp[int(vertex)] + cost < dp[int(neighbour)] and dp[int(vertex)] != math.inf:
                return True

    return False


def lowest_cost_walk_dp(G, source, target):
    """
    Function that computes the lowest cost of a walk from source to target and builds the path of known length k, where
    k is from [1, V] (V is the number of the vertices), using dynamic programming. If no walk exists, the cost is
    math.inf as initialized.
    Recurrence relation:
        dp[s][0] = 0
        dp[i][j] = inf, for i=1,V, i!=s or i==s and j!=0, j=1,V-1
        dp[i][j] = dp[i-1][j-1] + min(costs[i-1][i]), i=1,V-1, and i is the outbound neighbor of i-1
    Time-Complexity: O(V^2*E), where E is the number of edges
    :param G: DirectedGraph object
    :param source: string (later converted to integer)
    :param target: string (later converted to integer)
    :return: the walk represented as a list and the minimum_cost as an integer
    """
    V = G.get_number_of_vertices()

    dp = [[math.inf for x in range(V + 1)] for y in range(V)]
    dp[int(source)][0] = 0

    previous = [[math.inf for x in range(V)] for y in range(V)]

    for length in range(1, V):
        for vertex in G.parse_vertices():
            if dp[int(vertex)][length - 1] != math.inf:
                for neighbour in G.parse_outbound(vertex):
                    if dp[int(neighbour)][length] > (dp[int(vertex)][length - 1] + G.costs[(vertex, neighbour)]):
                        dp[int(neighbour)][length] = dp[int(vertex)][length - 1] + G.costs[(vertex, neighbour)]
                        previous[int(neighbour)][length] = int(vertex)

    minimum_cost = math.inf
    minimum_length = 0
    for length in range(1, V):
        if dp[int(target)][length] < minimum_cost:
            minimum_cost = dp[int(target)][length]
            minimum_length = int(length)

    walk = [int(target)]
    current = int(target)

    for length in range(minimum_length, 0, -1):
        walk.insert(0, previous[int(current)][length])
        current = previous[int(current)][length]

    return walk, minimum_cost
