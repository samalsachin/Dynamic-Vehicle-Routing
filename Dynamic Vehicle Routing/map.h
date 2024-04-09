#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <climits>
#include <algorithm>
#include <chrono>

using namespace std;

class Graph
{
public:
    int nodesCount;
    vector<vector<pair<int, int>>> adjList;

    Graph(int nodes);

    void addEdge(int startNode, int endNode, int Weight);

    // Function to get neighbors of a given vertex
    vector<int> getNeighbors(int vertex) const;
};

struct return_value
{
    int distance;
    vector<vector<int>> parent;

    return_value(int distance, vector<vector<int>>& parent);
};

// Function to get the an array from the algorithm containing execution time, no of comparisons and no of relaxation
return_value Dijkstra(const Graph graph, int StartNode, int EndNode);

// Function to find all paths from source to destination
vector<int> retrievePath(const vector<vector<int>>& parentVector, int source, int destination);

#endif