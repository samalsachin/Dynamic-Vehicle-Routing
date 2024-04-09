#include <iostream>
#include <cstdlib> // For rand()

#include "map.h"
#include "randomWalker.h" //For random walk
#include "fileHandler.h"  //For handelling files

using namespace std;

void randomPath(const Graph& graph, int StartNode, int EndNode, FileHandler& file, int serialNo)
{

    // Test Dijkstra's algorithm performance
    auto start = chrono::high_resolution_clock::now();
    struct return_value result = Dijkstra(graph, StartNode, EndNode);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> duration = end - start;

    //printing the results into a csv file
    stringstream data;
    data << serialNo << "," << file.decodeLocation(StartNode) << "," << file.decodeLocation(EndNode) << "," << result.distance << "," << duration.count();
    file.writeInCSV(data.str());

    //printing the results
    cout << "Distance between " << file.decodeLocation(StartNode) << " and " << file.decodeLocation(EndNode) << " is " << result.distance<<endl;
    cout << "Dijkstra's algorithm took " << duration.count() << " seconds.\n";
}

void dijkstraShortestPath(const Graph& graph, int StartNode, int EndNode, FileHandler& file)
{

    // Test Dijkstra's algorithm performance
    auto start = chrono::high_resolution_clock::now();
    struct return_value result = Dijkstra(graph, StartNode, EndNode);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> duration = end - start;

    //printing the results
    cout << "Distance between " << file.decodeLocation(StartNode) << " and " << file.decodeLocation(EndNode) << " is " << result.distance<<endl;
    cout << "Dijkstra's algorithm took " << duration.count() << " seconds.\n";
    cout << "The path from source to destination is ::\n";
    //printPath(result.parent, file, StartNode, EndNode);
    vector<int> path = retrievePath(result.parent, StartNode, EndNode);
    // Print the retrieved path
    cout << "Path from " << file.decodeLocation(StartNode) << " to " << file.decodeLocation(EndNode) << ": ";
    for (int node : path) {
        cout << file.decodeLocation(node) << "->";
    }
}


int main()
{
    //! handel the files names and the inputs needed to run the program
    string verticesFile = "Bhubaneswar.csv";
    int nodesCount = 41;
    string locationFile = "locations.csv";
    // Load graph from CSV files
    FileHandler file(locationFile);
    Graph graph = file.loadGraphFromCSV(verticesFile, nodesCount);

    while (true)
    {
        cout << "\n=== Dynamic Vehicle Routing ===\n";
        cout << "1. Run Random Walker\n";
        cout << "2. Find Shortest Path\n";
        cout << "3. Exit\n";

        cout << "Select an option (1/2/3): ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            string source, destination;
            cout << "Enter the source: ";
            cin.ignore();
            getline(cin, source);
            cout << "Enter the destination: ";
            //scanf("%[^\n]", &destination);
            getline(cin, destination);
            int iterate;
            cout << "Enter the number of random walks to be performed: ";
            cin >> iterate;

            file.writeInCSV("Sl No,Source,Destination,Distance,Execution Time");

            int sourceID = file.encodeLocation(source);
            int destinationID = file.encodeLocation(destination);
            for (int i = 0; i < iterate; i++)
            {
                cout << "================================================================================"<<endl;
                int newSource = runRandomWalker(graph, sourceID);
                if (newSource == -1) {
                    cout << "Random Walker is stuck at vertex " << file.decodeLocation(sourceID) << ".\n";
                    break;
                }
                else {
                    cout << "Random Walker moves from " << file.decodeLocation(sourceID) << " to " << file.decodeLocation(newSource) << endl;
                }
                randomPath(graph, newSource, destinationID, file, i);
                sourceID = newSource;
                cout << "================================================================================"<<endl;
            }
        }
        else if (choice == 2) {
            string source, destination;
            cout << "Enter the source: ";
            cin.ignore();
            getline(cin, source);
            cout << "Enter the destination: ";
            getline(cin, destination);
            int sourceID = file.encodeLocation(source);
            int destinationID = file.encodeLocation(destination);
            /*cout << "lets go from " << sourceID << " to " << destinationID<<endl;*/
            dijkstraShortestPath(graph, sourceID, destinationID, file);
        }
        else if (choice == 3) {
            cout << "Exiting the program. Goodbye!\n";
            return 0;
        }
        else {
            cout << "Invalid choice. Please enter 1, 2, or 3.\n";
        }
    }

    return 0;
}
