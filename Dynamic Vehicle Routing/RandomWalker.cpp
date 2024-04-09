#include "RandomWalker.h"

// Function to run the random walker and test Dijkstra's performance
int runRandomWalker(Graph& graph, int startingVertex)
{
    // Get neighboring vertices
    vector<int> neighbors = graph.getNeighbors(startingVertex);

    // If there are no neighbors, the walker is stuck
    if (neighbors.empty())
    {
        return  -1;
    }

    // Randomly choose one neighbor to move to
    int nextVertex;
    do {
        nextVertex = neighbors[rand() % neighbors.size()];
    }while (nextVertex == startingVertex);

    return nextVertex;
}