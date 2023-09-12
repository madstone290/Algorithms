#include <bits/stdc++.h>
using namespace std;

/*
Edge of a graph
*/
class Edge
{
public:
    int src, dest, weight;
    Edge() {}
    Edge(int src, int dest, int weight)
    {
        this->src = src;
        this->dest = dest;
        this->weight = weight;
    }
    string toString()
    {
        return to_string(src) + " - " + to_string(dest) + " : " + to_string(weight);
    }
};

/*
Kruskal's Algorithm
- Greedy Algorithm
- Finds a minimum spanning tree for a connected weighted graph
- Time Complexity: O(ElogE)
- Space Complexity: O(E + V)
- E: Number of edges
- V: Number of vertices
*/
class Kruskal
{
private:
    /// @brief Check if two vertices are in the same set or not
    /// @param parent parent array
    /// @param src source vertex
    /// @param dest destination vertex
    /// @return true if src and dest are in the same set, false otherwise
    bool isConnected(vector<int> &parent, int src, int dest)
    {
        int rootX = find(parent, src);
        int rootY = find(parent, dest);
        return rootX == rootY;
    }

    /// @brief find the parent of a node
    /// @param parent parent array
    /// @param i node
    /// @return parent of i
    int find(vector<int> &parent, int i)
    {
        if (parent[i] == i)
            return i;
        return find(parent, parent[i]);
    }

    /// @brief merge two sets
    /// @param parent parent array
    /// @param x node
    /// @param y node
    void merge(vector<int> &parent, int x, int y)
    {
        int xRoot = find(parent, x);
        int yRoot = find(parent, y);
        parent[yRoot] = xRoot;
    }

public:
    /// @brief execute Kruskal's Algorithm
    /// @param edges edges of the graph
    /// @param V number of vertices
    vector<Edge> execute(vector<Edge> &edges, int V)
    {
        sort(edges.begin(), edges.end(), [](Edge &a, Edge &b)
             { return a.weight < b.weight; });
        /**
         * result[i] = ith edge of the MST
         * It is used to store the resultant MST
         */
        vector<Edge> result(V - 1);
        /**
         * parent[i] = parent of i. If parent[i] = i, then i is a root node
         * Initially, all vertices are in different sets and have themselves as parents
         * It is used to check if two vertices are in the same set or not
         */
        vector<int> parent(V);

        for (int i = 0; i < V; i++)
            parent[i] = i;

        // selected edges
        int edgeCount = 0;
        // index used to pick next edge
        int current = 0;
        while (edgeCount < V - 1)
        {
            Edge next_edge = edges[current++];

            /**
             * If the vertices of next_edge are not in the same set,
             * include next_edge in the result and merge the two sets
             */
            int src = next_edge.src;
            int dest = next_edge.dest;
            if (!isConnected(parent, src, dest))
            {
                result[edgeCount++] = next_edge;
                merge(parent, src, dest);
            }
        }
        return result;
    }
};

int main()
{
    int V = 9;
    vector<Edge> edges1;
    edges1.push_back(Edge(0, 1, 4));
    edges1.push_back(Edge(0, 7, 8));
    edges1.push_back(Edge(1, 2, 8));
    edges1.push_back(Edge(1, 7, 11));
    edges1.push_back(Edge(2, 3, 7));
    edges1.push_back(Edge(2, 8, 2));
    edges1.push_back(Edge(2, 5, 4));
    edges1.push_back(Edge(3, 4, 9));
    edges1.push_back(Edge(3, 5, 14));
    edges1.push_back(Edge(4, 5, 10));
    edges1.push_back(Edge(5, 6, 2));
    edges1.push_back(Edge(6, 7, 1));
    edges1.push_back(Edge(6, 8, 6));
    edges1.push_back(Edge(7, 8, 7));

    // vector<Edge> edges2;
    // edges2.push_back(Edge(7, 6, 1));
    // edges2.push_back(Edge(8, 2, 2));
    // edges2.push_back(Edge(6, 5, 2));
    // edges2.push_back(Edge(0, 1, 4));
    // edges2.push_back(Edge(2, 5, 4));
    // edges2.push_back(Edge(8, 6, 6));
    // edges2.push_back(Edge(2, 3, 7));
    // edges2.push_back(Edge(7, 8, 7));
    // edges2.push_back(Edge(0, 7, 8));
    // edges2.push_back(Edge(1, 2, 8));
    // edges2.push_back(Edge(3, 4, 9));
    // edges2.push_back(Edge(5, 4, 10));
    // edges2.push_back(Edge(1, 7, 11));
    // edges2.push_back(Edge(3, 5, 14));

    Kruskal kruskal;
    vector<Edge> result = kruskal.execute(edges1, V);
    for (Edge edge : result)
        cout << edge.toString() << endl;
    return 0;
}
