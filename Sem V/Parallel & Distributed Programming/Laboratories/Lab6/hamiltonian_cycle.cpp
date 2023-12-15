#include <iostream>
#include <vector>
#include <future>
#include <mutex>

const int V = 5; // Number of vertices in the graph

std::mutex mtx; // Mutex for synchronization

bool isSafe(int v, bool graph[V][V], const std::vector<int> &path, int pos)
{
    if (!graph[path[pos - 1]][v])
        return false;
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;
    return true;
}

std::vector<int> hamCycleUtil(bool graph[V][V], std::vector<int> path, int pos)
{
    if (pos == V)
    {
        if (graph[path[pos - 1]][path[0]])
            return path;
        else
            return std::vector<int>();
    }

    std::vector<std::future<std::vector<int>>> futures;

    for (int v = 0; v < V; v++)
    {
        if (isSafe(v, graph, path, pos))
        {
            std::vector<int> newPath = path;
            newPath[pos] = v;
            futures.push_back(std::async(std::launch::async, hamCycleUtil, graph, newPath, pos + 1));
        }
    }

    for (auto &future : futures)
    {
        std::vector<int> result = future.get();
        if (!result.empty())
            return result;
    }

    return std::vector<int>();
}

void findHamiltonianCycle(bool graph[V][V], int start_vertex)
{
    std::vector<int> path(V, -1);
    path[0] = start_vertex;

    std::vector<int> resultPath = hamCycleUtil(graph, path, 1);
    std::lock_guard<std::mutex> lock(mtx);
    if (resultPath.empty())
    {
        std::cout << "No Hamiltonian Cycle found." << std::endl;
    }
    else
    {
        std::cout << "Hamiltonian Cycle found starting from vertex " << start_vertex << ": ";
        for (int vertex : resultPath)
            std::cout << vertex << " ";
        std::cout << resultPath[0] << std::endl;
    }
}

// Function to generate a random directed graph
// V - number of vertices
// edgeProbability - probability of an edge existing between two vertices
std::vector<std::vector<bool>> generateRandomGraph(int V, double edgeProbability)
{
    std::vector<std::vector<bool>> graph(V, std::vector<bool>(V, false));

    // Initialize random number generator
    std::srand(std::time(nullptr));

    for (int i = 0; i < V; ++i)
    {
        for (int j = 0; j < V; ++j)
        {
            if (i != j && static_cast<double>(std::rand()) / RAND_MAX < edgeProbability)
            {
                graph[i][j] = true;
            }
        }
    }

    return graph;
}

// Function to print the graph
void printGraph(const std::vector<std::vector<bool>> &graph)
{
    for (const auto &row : graph)
    {
        for (bool edge : row)
        {
            std::cout << edge << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    // Simple example
    bool graph1[V][V] = {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 1, 1},
        {0, 1, 0, 0, 1},
        {1, 1, 0, 0, 1},
        {0, 1, 1, 1, 0},
    };

    int V = 5;                    // Number of vertices
    double edgeProbability = 0.3; // Probability of an edge

    // Generate and print the random graph
    auto graph = generateRandomGraph(V, edgeProbability);
    printGraph(graph);

    findHamiltonianCycle(graph1, 4);

    return 0;
}
