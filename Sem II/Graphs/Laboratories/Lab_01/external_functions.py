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
