import copy
from heapq import heappush, heappop

class UndirectedGraph:
    def __init__(self, vertices):
        self.vertices = dict()
        for i in vertices:
            self.vertices[i] = set()
        
    def add_edge(self, x, y):
        self.vertices[x].add(y)
        self.vertices[y].add(x)
    
    def is_edge(self, x, y):
        return (y in self.vertices[x])

    def parse_vertices(self):
        vertices_list = list()
        for key in self.vertices:
            vertices_list.append(key)
        return vertices_list
       
    def parse_n(self, x):
        n_vertices = list()
        for y in self.vertices[x]:
            n_vertices.append(y)
        return n_vertices 

def print_graph(g):
    print("Neighborss:")
    for x in g.parse_vertices():
        s = str(x) + ":"
        for y in g.parse_n(x):
            s = s + " " + str(y)
        print(s)

def create_graph_and_cost():
    g = UndirectedGraph(range(1,7))
    cost1 = {
        (1,2): 3,
        (1,3): 2,
        (1,4): 4,
        (2,3): 2,
        (2,6): 1,
        (3,4): 4,
        (3,5): 3,
        (3,6): 2,
        (4,5): 5,
        (5,6): 5,
    }
    cost = {}
    for edge in cost1.keys():
        g.add_edge(edge[0], edge[1])
        cost[edge] = cost1[edge]
        cost[(edge[1], edge[0])] = cost1[edge]
    return g, cost

def kruskal(g, cost):
    '''Returns a list of pairs representing the edges of the minimum tree
    '''
    sets = DisjointSets(g.parse_vertices())
    edges = list(cost.keys())
    edges.sort(key=lambda key : cost[key])
    #for e in edges:
    #    print(f"{e} : {cost[e]}")
    
    final = []
    for e in edges:
        if sets.checkAndJoin(e[0], e[1]):
            final.append(e)
    return final
    
class DisjointSets:
    def __init__(self, vertices):
        self.parent = {x : None for x in vertices}
        self.height = {x : 0 for x in vertices}

    def checkAndJoin(self, x, y):
        '''If x and y are in the same component, returns False. If they are in
        distinct components, it join the components and returns False
        '''
        rx = self.root(x)
        ry = self.root(y)
        if rx == ry:
            return False
        if self.height[rx] < self.height[ry]:
            self.parent[rx] = ry
        elif self.height[rx] > self.height[ry]:
            self.parent[ry] = rx
        else:
            self.parent[ry] = rx
            self.height[rx] += 1
        print(f"x={x}, y={y}, parent={self.parent}, height={self.height}")
        return True

    def root(self, x):
        while self.parent[x] is not None:
            x = self.parent[x]
        return x

class DisjointSetsSlow:
    def __init__(self, vertices):
        self.ls = dict()
        c = 1
        for v in vertices:
            self.ls[v] = c
            c += 1
            
    def checkAndJoin(self, x, y):
        '''If x and y are in the same component, returns False. If they are in
        distinct components, it join the components and returns False
        '''
        if self.ls[x] == self.ls[y]:
            return False
        old_set = self.ls[y]
        for s in self.ls:
            if self.ls[s] == old_set:
                self.ls[s] = self.ls[x]
        return True
        
def test_min_tree():
    g,cost=create_graph_and_cost()
    #print_graph(g)
    print(kruskal(g, cost))

test_min_tree()
