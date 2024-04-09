#include "map.h"

using namespace std;


Graph::Graph(int nodes)
{
    this->nodesCount = nodes;
    this->adjList = vector<vector<pair<int, int>>>(nodes);
}

void Graph::addEdge(int startNode, int endNode, int Weight)
{
    if (startNode >= 0 && startNode < nodesCount && endNode >= 0 && endNode < nodesCount)
    {
        adjList[startNode].push_back(make_pair(endNode, Weight));
        adjList[endNode].push_back(make_pair(startNode, Weight));
    }
    else
    {
        // Handle the case where the provided node indices are out of bounds.
        // You can print an error message or take appropriate action.
        cout << "Invalid node indices: " << startNode << " or " << endNode << endl;
    }
    }

// Function to get neighbors of a given vertex
vector<int> Graph::getNeighbors(int vertex) const
{
    vector<int> neighbors;
    if (vertex >= 0 && vertex < nodesCount)
    {
        for (const auto& neighbor : adjList[vertex])
        {
            neighbors.push_back(neighbor.first);
        }
    }
    else
    {
        cout << "Invalid vertex index: " << vertex << endl;
    }
    return neighbors;
}



return_value::return_value(int distance, vector<vector<int>>& parent)
{
    this->distance = distance;
    this->parent = parent;
}


// Function to get the an array from the algorithm containing execution time, no of comparisons and no of relaxation
return_value Dijkstra(const Graph graph, int StartNode, int EndNode)
{

    // declaring the needed storage structures
    vector<int> Dst(graph.nodesCount, INT_MAX);
    vector<bool> vis(graph.nodesCount, false);
    vector<vector<int>> parent(graph.nodesCount, vector<int>());

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // initializing the storage structures
    Dst[StartNode] = 0;
    vis[StartNode] = true;
    pq.push(make_pair(0, StartNode));

    // main loop
    while (!pq.empty())
    {
        // For finding the SDSP we can break the loop if the current node is the destination
        //if (pq.top().second == EndNode) break;
        // later we can send the distance and the path as output

        // taking out the first element
        int curr = pq.top().second;
        pq.pop();

        vis[curr] = true;

        for (auto neigh : graph.adjList[curr])
        {
            int neighbor = neigh.first;
            int weight = neigh.second;

            if (vis[neighbor] != true)
            {
                int relax = Dst[curr] + weight;
                if (relax < Dst[neighbor])
                {
                    Dst[neighbor] = relax;
                    parent[neighbor].clear();
                    parent[neighbor].push_back(curr);
                    pq.push(make_pair(Dst[neighbor], neighbor));
                }
                else if (relax == Dst[neighbor])
                {
                    parent[neighbor].push_back(curr);
                }
            }
        }
    }

    return return_value(Dst[EndNode], parent);
}

// Function to find all paths from source to destination
vector<int> retrievePath(const vector<vector<int>>& parentVector, int source, int destination) {
    vector<int> path;
    int current = destination;

    // If the destination is unreachable (no parent)
    if (parentVector[destination].empty()) {
        cout << "No path exists from " << source << " to " << destination << endl;
        return path;
    }

    // Traverse the parent vector from destination to source
    while (current != source) {
        path.push_back(current);
        if (parentVector[current].empty()) {
            // Handle the case where there is a gap in the parent information
            cout << "Error: Parent information is incomplete." << endl;
            return vector<int>();
        }
        current = parentVector[current][0];
    }

    // Add the source node to the path
    path.push_back(source);

    // Reverse the path to get it from source to destination
    reverse(path.begin(), path.end());

    return path;
}

