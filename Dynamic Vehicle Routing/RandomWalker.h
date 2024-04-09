#ifndef RANDOMWALKER_H_INCLUDED
#define RANDOMWALKER_H_INCLUDED

#include <vector>
#include <iostream>
#include "map.h"
#include "FileHandler.h"
using namespace std;

// Function to run the random walker and test Dijkstra's performance
int runRandomWalker(Graph& graph, int startingVertex);

#endif // !RANDOMWALKER_H_INCLUDED