import copy
import random
import time
import queue
from heapq import heappush, heappop

class Graph:
    
    # self.out_neighbors = dict from vertex to list of neighbors
    def __init__(self, vertices = [], edges = []):
        self.out_neighbors = {}
        self.in_neighbors = {}
        for vertex in vertices:
            self.add_vertex(vertex)
        for edge in edges:
            self.add_edge(edge[0], edge[1])
    
    def add_vertex(self, vertex):
        if vertex not in self.out_neighbors.keys():
            self.out_neighbors[vertex] = []
            self.in_neighbors[vertex] = []
        else:
            raise ValueError("Vertex already in the graph!")
    def add_edge(self, x, y):
        if x not in self.out_neighbors.keys():
            raise ValueError(f"{x} vertex is not in the graph")
        if y not in self.out_neighbors.keys():
            raise ValueError(f"{y} vertex is not in the graph")
        if y in self.out_neighbors[x]:
            raise ValueError(f"{x}, {y} edge is already in the graph")
        self.out_neighbors[x].append(y)
        self.in_neighbors[y].append(x)
        
    def parse_vertices(self):
        return [x for x in self.out_neighbors.keys()]
    
    def outbound(self, x):
        return copy.deepcopy(self.out_neighbors[x])

    def inbound(self, x):
        return copy.deepcopy(self.in_neighbors[x])
        l = []
        for y in self.out_neighbors.keys():
            if x in self.out_neighbors[y]:
                l.append(y)
        return l

    def is_edge(self, x, y):
        return y in self.out_neighbors[x]
        
class WolfGoatCabbageGraph:
    def parse_vertices(self):
        pass
    
    def outbound(self, x):
        return x.neighbor_states()

    def inbound(self, x):
        return x.neighbor_states()

    def is_edge(self, x, y):
        pass

    def initial_state(self):
        return WolfGoatCabbageState({x:False for x in ['W', 'G', 'C', 'B']})

    def final_state(self):
        return WolfGoatCabbageState({x:True for x in ['W', 'G', 'C', 'B']})

class WolfGoatCabbageState:
    def __init__(self, dic):
        self.__objects = copy.copy(dic)
        
    def __str__(self):
        init_string="-"
        for key in self.__objects:
            if self.__objects[key]:
                init_string+=key
            else:
                init_string = key + init_string
        return init_string
        
    def __repr__(self):
        return self.__str__()
        
    def __eq__(self, other):
        return isinstance(other,WolfGoatCabbageState) and self.__objects == other.__objects
        
    def __hash__(self):
        n = 0
        powers = {
            'W' : 0,
            'G' : 1,
            'C' : 2,
            'B' : 3,
        }
        for key in self.__objects:
            if self.__objects[key]:
                n += 2**powers[key]
                
        return n
        
    def is_valid(self):
        '''Returns True if the state is valid in the sense that nobody eats anybody else
        '''
        if (self.__objects['G'] == self.__objects['B']):
            return True
            
        if (self.__objects['W'] != self.__objects['B']):
            return False
            
        if (self.__objects['C'] != self.__objects['B']):
            return False
            
        return True
        
    def neighbor_states(self):
        '''Returns an iterable that contains all the states reachable in one move
        '''
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
    print("Took %sms" % (1000*(time.time()-start),))
    print("Inbound")
    start = time.time()
    for x in g.parse_vertices():
        for y in g.inbound(x):
            pass
    print("Took %sms" % (1000*(time.time()-start),))

def build_graph1():
    g = Graph()
    g.add_vertex(1)
    g.add_vertex(2)
    g.add_vertex(3)
    g.add_vertex(4)
    g.add_vertex(5)
    g.add_edge(1, 2)
    g.add_edge(2, 3)
    g.add_edge(3, 4)
    g.add_edge(4, 2)
    #g.add_edge(2, 4)
    g.add_edge(5, 4)
    return g

def build_graph2():
    g = Graph(["A", "B"])
    g.add_edge("A", "B")
    return g

def build_graph3():
    g = Graph(["A", "B", "C"], [("A", "B"), ("A", "C"), ("C", "A")])
    return g

def build_random_graph(n, m):
    g = Graph(range(n))
    while m > 0:
        x = random.randrange(n)
        y = random.randrange(n)
        if not g.is_edge(x, y):
            g.add_edge(x, y)
            m = m - 1
    return g

def shortest_path(g, s, t):
    '''Finds the shortest path (minimum number of edges)
    in the graph g from vertex s to vertex t.
    Returns the path as a list of vertices
    starting with s and ending with t.
    If s==t, we return [s]. If there are multiple path of the same
    minimum length, the function will return one of them.
    Returns None if no path exists.
    '''
    path = []
    distance  = bfs(g, s)
    vertex = t
    path.append(t)
    if not t in distance.keys():
        return None
    while vertex != s:
        for neighbor in g.inbound(vertex):
            if neighbor in distance.keys() and distance[neighbor] == distance[vertex] - 1:
                path.append(neighbor)
                vertex = neighbor
                break
    path.reverse()
    return path
    
    
def bfs(g, s):
    '''Executes a BFS parse of graph g from vertex s
    Returns a dictionary where the keys are the vertices and the values
    are the corresponding distances from the starting vertex
    '''
    distance = {}
    distance[s] = 0
    q = queue.Queue()
    q.put(s)
    while not q.empty():
        first = q.get()
        for neighbor in g.outbound(first):
            if not neighbor in distance.keys():
                distance[neighbor] = distance[first] + 1
                q.put(neighbor)
    return distance 
    

def shortest_path2(g,s,t):
    # 1    2 3 4 5 
    # None 1 2 3 
    
    prev = {}
    prev[s] = None
    q = queue.Queue()
    q.put(s)
    arrived = False
    while not q.empty() and not arrived:
        first = q.get()
        for neighbor in g.outbound(first):
            if not neighbor in prev.keys():
                prev[neighbor] = first
                q.put(neighbor)
                
                if neighbor == t:
                    arrived = True
                    break;
    path = []
    vertex = t
    path.append(t)
    if not t in prev.keys():
        return None
    while vertex != s:
        path.append(prev[vertex])
        vertex = prev[vertex]
        
    path.reverse()
    
    return path

def main():
    n = 10000
    #g = build_random_graph(n, 10*n)
    g = build_graph1()
    parse_graph(g)
    
    print(shortest_path(g, 1, 4))
    print(shortest_path2(g, 1, 4))
    
    #lst = g.outbound(1)
    #lst.append(2)
    
    
class VertexWithDist:
    def __init__(self, vertex, dist):
        self.vertex = vertex
        self.dist = dist
        
    def __lt__(self, other):
        return self.dist < other.dist
    def __le__(self, other):
        return self.dist <= other.dist
    def __gt__(self, other):
        return self.dist > other.dist
    def __ge__(self, other):
        return self.dist >= other.dist
        
    def __str__(self):
        return "vertex=%s, dist=%s" % (self.vertex, self.dist)
    def __repr__(self):
        return "vertex=%s, dist=%s" % (self.vertex, self.dist)
    
def create_graph_and_cost():
    g = Graph(range(6))
    cost = {
        (0,1): 3,
        (0,2): 6,
        (1,2): 3,
        (0,3): 3,
        (3,2): 2,
        (2,4): 10,
        #(2,0):1
    }
    for edge in cost.keys():
        g.add_edge(edge[0], edge[1])
    return g, cost

def create_graph_with_cycle():
    g = Graph(range(6))
    edges = [
        (0,1),
        (0,2),
        (1,2),
        (0,3),
        (3,2),
        (2,4),
        (4,3),
        (2,5),
    ]
    for edge in edges:
        g.add_edge(edge[0], edge[1])
    return g

def min_cost_path_dijkstra(g, cost, s, t):
    '''Finds the minimum cost path from s to t
    in the graph g. Returns a tuple containing the path as a list of vertices starting
    with s and ending with t, and the corresponding cost. Returns (None,None) if no path exists.
    '''
    dist,prev = dijkstra(g, cost, s, t)
    
    if t not in dist.keys():
        return None
        
    path = []
    y = t
    while y != s:
        path.append(y)
        y = prev[y]
    path.append(s)
    path.reverse()
    return path,dist[t]

def dijkstra(g, cost, s, t=None):
    dist = dict()
    prev = dict()
    dist[s] = 0
    q = list()
    #heappush(q, (dist[s], s))
    heappush(q, VertexWithDist(s, dist[s]))
    
    while q:
        print(f"q={q}")
        #distance, vertex = heappop(q)
        vd = heappop(q)
        vertex = vd.vertex
        distance = vd.dist
        print(f"distance={distance}, vertex={vertex}")
        if vertex == t:
            print("Destination reached")
            break
        if distance == dist[vertex]:
            for neighbor in g.outbound(vertex):
                if neighbor not in dist or dist[neighbor] > dist[vertex] + cost[(vertex, neighbor)]: 
                    dist[neighbor] = dist[vertex] + cost[(vertex, neighbor)]
                    prev[neighbor] = vertex
                    #heappush(q, (dist[neighbor], neighbor))
                    heappush(q, VertexWithDist(neighbor, dist[neighbor]))
        else:
            print(f"Skip vertex {vertex}")
        print(f"dist={dist}")
        print(f"prev={prev}")
    return dist, prev

def min_cost_path_dag(g, cost, s, t):
    '''Finds the minimum cost path from s to t
    in the graph g. Returns a tuple containing the path as a list of vertices starting
    with s and ending with t, and the corresponding cost. Returns (None,None) if no path exists.
    '''
    sorted_list = toposort(g)
    dist,prev = dist_dag(sorted_list, g, cost, s)
    
    if t not in dist.keys():
        return None
        
    path = []
    y = t
    while y != s:
        path.append(y)
        y = prev[y]
    path.append(s)
    path.reverse()
    return path,dist[t]

def dfs(g, x, phase, top_sort_list):
    phase[x] = 1
    
    for neighbor in g.outbound(x):
        if phase[neighbor] == 0:
            val = dfs(g, neighbor, phase, top_sort_list)
            if val is not None:
                if val[0] != val[-1]:
                    val.append(x)
                return val
        elif phase[neighbor] == 1:
            return [neighbor,x]
            #raise Exception("Not a DAG")
    phase[x] = 2
    top_sort_list.append(x)
    return None

def toposort(g):
    '''Returns the list of vertices of graph g in topological sorting order, or None if g is not a DAG
    '''
    
    phase = {x : 0 for x in g.parse_vertices()}
    top_sort_list = []

    for v in g.parse_vertices():
        if phase[v] == 0:
            val = dfs(g, v, phase, top_sort_list)
            if val is not None:
                val.reverse()
                print(f"Cycle found: {val}")
                return None
    
    top_sort_list.reverse()
    print(top_sort_list)
    return top_sort_list

def dist_dag(sorted_list, g, cost, s):
    dist = dict()
    prev = dict()
    dist[s] = 0
    
    for vertex in sorted_list:
        if vertex not in dist:
            print(f"Vertex {vertex} is inaccessible from start")
            continue
        print(f"distance={dist[vertex]}, vertex={vertex}")
        for neighbor in g.outbound(vertex):
            if neighbor not in dist or dist[neighbor] > dist[vertex] + cost[(vertex, neighbor)]: 
                dist[neighbor] = dist[vertex] + cost[(vertex, neighbor)]
                prev[neighbor] = vertex
        print(f"dist={dist}")
        print(f"prev={prev}")
    return dist, prev

def test_wolf_goat_cabbage():
    g = WolfGoatCabbageGraph()
    s = g.initial_state()
    t = g.final_state()
    print(s == t)
    print(s == WolfGoatCabbageState({x:False for x in ['W', 'C', 'G', 'B']}))
    print(s == 1)
    print(s.__hash__())
    print(t.__hash__())
    print(s)
    print(t)
    print(shortest_path(g, s, t))

def test_dijkstra():
    g,cost=create_graph_and_cost()
    print(min_cost_path_dijkstra(g, cost, 0, 4))

def test_min_cost_dag():
    g,cost=create_graph_and_cost()
    print(min_cost_path_dag(g, cost, 0, 4))

def test_cycle():
    g=create_graph_with_cycle()
    print(toposort(g))

test_cycle()
