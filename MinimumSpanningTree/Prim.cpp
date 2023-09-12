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

    /// @brief create new edge with src and dest swapped
    /// @return the reversed edge
    Edge reverse()
    {
        return Edge(dest, src, weight);
    }
};

struct EdgeCompare
{
    bool operator()(Edge &a, Edge &b)
    {
        if (a.weight == b.weight)
            return a.src > b.src;
        return a.weight > b.weight;
    }
};

/*
Prim's algorithm
- Greedy algorithm
- Finds a minimum spanning tree for a connected weighted graph
- Time Complexity: O(ElogV)
- Space Complexity: O(E + V)
- E: Number of edges
- V: Number of vertices
*/
class Prim
{
private:
public:
    vector<Edge> execute(vector<Edge> &edges, int V)
    {
        // result tree
        vector<Edge> result;

        // create adjacency list
        vector<vector<Edge>> nodeEdges(V);
        for (int i = 0; i < edges.size(); i++)
        {
            nodeEdges[edges[i].src].push_back(edges[i]);
            nodeEdges[edges[i].dest].push_back(edges[i].reverse());
        }
        // check if a node is visited or not
        vector<bool> visited(V, false);
        // priority queue to store edges. The top element is the edge with the smallest weight
        priority_queue<Edge, vector<Edge>, EdgeCompare> pq;

        // set node 0 as starting node. add all edges from node 0 to the priority queue
        visited[0] = true;
        for (int i = 0; i < nodeEdges[0].size(); i++)
            pq.push(nodeEdges[0][i]);
        
        // count of edges added to the result tree. It should be V - 1
        int count = 0;
        while (count < V - 1)
        {
            Edge e = pq.top();
            pq.pop();
            if (visited[e.dest])
                continue;

            visited[e.dest] = true;
            result.push_back(e);
            count++;

            // add all edges from node e.dest to the priority queue
            for (int i = 0; i < nodeEdges[e.dest].size(); i++)
                pq.push(nodeEdges[e.dest][i]);
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

    Prim prim;
    vector<Edge> result = prim.execute(edges1, V);
    for (int i = 0; i < result.size(); i++)
        cout << result[i].toString() << endl;
    return 0;
}