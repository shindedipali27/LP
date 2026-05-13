#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

class Graph
{
    int vertices;
    vector<vector<int> > adj;

public:

    Graph(int v)
    {
        vertices = v;
        adj.resize(v);
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void parallelBFS(int start)
    {
        vector<bool> visited(vertices, false);

        queue<int> q;

        visited[start] = true;

        q.push(start);

        cout << "Parallel BFS starting from node "
             << start << ": ";

        while (!q.empty())
        {
            int node;

            #pragma omp critical
            {
                node = q.front();
                q.pop();
            }

            cout << node << " ";

            #pragma omp parallel for
            for (int i = 0; i < adj[node].size(); i++)
            {
                int neighbor = adj[node][i];

                if (!visited[neighbor])
                {
                    #pragma omp critical
                    {
                        if (!visited[neighbor])
                        {
                            visited[neighbor] = true;
                            q.push(neighbor);
                        }
                    }
                }
            }
        }

        cout << endl;
    }

    void parallelDFSUtil(int node, vector<bool> &visited)
    {
        visited[node] = true;

        cout << node << " ";

        #pragma omp parallel for
        for (int i = 0; i < adj[node].size(); i++)
        {
            int neighbor = adj[node][i];

            if (!visited[neighbor])
            {
                #pragma omp critical
                {
                    if (!visited[neighbor])
                    {
                        parallelDFSUtil(neighbor, visited);
                    }
                }
            }
        }
    }

    void parallelDFS(int start)
    {
        vector<bool> visited(vertices, false);

        cout << "Parallel DFS starting from node "
             << start << ": ";

        parallelDFSUtil(start, visited);

        cout << endl;
    }
};

int main()
{
    Graph graph(6);

    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 5);

    int startNode = 0;

    graph.parallelBFS(startNode);

    graph.parallelDFS(startNode);

    return 0;
}
