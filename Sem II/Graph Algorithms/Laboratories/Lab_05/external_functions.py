import queue
from random import randrange

from exceptions import InvalidEdges
from undirected_graph import UndirectedGraph


def generate_random_graph(n, m, file_path):
    """
    Function that generates a random graph with a given number of vertices and edges. The cost will be an integer from
    the interval [0, 1.000.000]. If the number of edges is invalid an error will be raised. The graph will be written in
    the text file having the path file_path.
    :param file_path: path of the file in which the graph will be saved
    :param n: integer (number of vertices)
    :param m: integer (number of edges)
    :return: UndirectedGraph object
    """
    if m > n ** 2 / 2:
        raise InvalidEdges

    vertices = []
    for i in range(n):
        vertices.append(str(i))

    edges = []
    while len(edges) < m:
        x = str(randrange(n))
        y = str(randrange(n))
        if x < y:
            x, y = y, x
        cost = randrange(-1000000, 1000000)

        ok = 1
        for edge in edges:
            if edge[0] == x and edge[1] == y:
                ok *= -1

        if ok == 1:
            edges.append((x, y, cost))

    G = UndirectedGraph(vertices, edges)

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

    G = UndirectedGraph(vertices, edges)

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
    Function that prints an UndirectedGraph object depending on the option of the user. If option == False, the graph will be
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


def bfs(G, s, visited):
    """
    Executes a BFS traversal of the undirected graph G.
    Time Complexity: O(n + m), where n is the number of vertices and m the number of edges
    :param G: UndirectedGraph object
    :param s: source vertex
    :param visited: dictionary of booleans
    :return: UndirectedGraph object that represents the connected component
    """
    vertices = []
    edges = []
    q = queue.Queue()

    q.put(s)
    visited[s] = True
    vertices.append(s)
    while not q.empty():
        first = q.get()
        for neighbour in G.parse_neighbours(first):
            if not neighbour in visited.keys():
                visited[neighbour] = True
                q.put(neighbour)

                if G.is_edge(neighbour, neighbour):
                    edges.append((neighbour, neighbour, G.costs[(neighbour, neighbour)]))
                for vertex in vertices:
                    if vertex < neighbour:
                        x, y = vertex, neighbour
                    else:
                        y, x = vertex, neighbour
                    if G.is_edge(x, y) and ((x, y, G.costs[(x, y)]) not in edges):
                        edges.append((x, y, G.costs[(x, y)]))
                vertices.append(neighbour)
    return UndirectedGraph(vertices, edges)


def bfs_connected_components(G):
    """
    Function that returns a list of the connected components of an undirected graph as UndirectedGraph objects. It uses
    Breadth-First Search traversal.
    Time Complexity: O(V+E), where V is the number of vertices and E the number of edges
    :param G: UndirectedGraph object
    :return: list of UndirectedGraph objects (list of the connected components)
    """
    visited = {}
    connected_components = []

    for vertex in G.parse_vertices():
        if not vertex in visited.keys():
            connected_component = bfs(G, vertex, visited)
            connected_components.append(connected_component)

    return connected_components


def get_hamiltonian_cycle(G):
    """
        Returns a Hamiltonian cycle of low cost (approximate TSP).
        Runtime: O(E*logE), where E is the number of edges in the provided undirected graph.
        :param G: UndirectedGraph object
        :return: UndirectedGraph object and integer
    """

    vertices_number = G.get_number_of_vertices()
    edges_number = G.get_number_of_edges()

    if edges_number != (vertices_number * (vertices_number - 1)) / 2:
        raise InvalidEdges

    return G.get_hamiltonian_cycle()
