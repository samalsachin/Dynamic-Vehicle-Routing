#include "FileHandler.h"

using namespace std;

 
void FileHandler::loadEncodingFromCSV(const string& csvFilePath)
{
    ifstream file(csvFilePath);
    if (!file.is_open())
    {
        cerr << "Error opening CSV file: " << csvFilePath << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        string placeName;
        int placeValue;
        cout << line << endl;

        if (getline(iss, placeName, ',') && (iss >> placeValue))
        {
            placeToValueMap[placeName] = placeValue;
            valueToPlaceMap[placeValue] = placeName;
        }
    }

    file.close();
}

//Function to write in a CSV file with a given format
void FileHandler::writeInCSV(const string& data) {
    // file pointer
    ofstream csvFile;

    // opens an existing csv file or creates a new file.
    csvFile.open("Output5.csv", ios::in | ios::app);
    csvFile << data
        << "\n";
    csvFile.close();
}


FileHandler::FileHandler(const string& csvFilePath)
{
    loadEncodingFromCSV(csvFilePath);
}

int FileHandler::encodeLocation(const string& placeName) const
{
    auto it = placeToValueMap.find(placeName);
    if (it != placeToValueMap.end())
    {
        return it->second;
    }
    else
    {
        cout << "Place not found: " << placeName << endl;
        // You might want to return a default value or handle this case differently.
        return -1;
    }
}

string FileHandler::decodeLocation(int encodedValue) const
{
    auto it = valueToPlaceMap.find(encodedValue);
    if (it != valueToPlaceMap.end())
    {
        return it->second;
    }
    else
    {
        cout << "Value not found: " << encodedValue << endl;
        // You might want to return a default value or handle this case differently.
        return "";
    }
}

// Function to initialise the graph from a csv file containing source, destination and weight data
Graph FileHandler::loadGraphFromCSV(string filename, int nodesCount)
{
    Graph graph(nodesCount);
    ifstream csvFile;
    csvFile.open(filename);
    if (!csvFile.is_open())
    {
        cout << "Error: Could not open CSV file during initialization" << endl;
        return 0;
    }

    string line;
    getline(csvFile, line); // Skip the header line
    // cout << line << endl;
    while (getline(csvFile, line))
    {
        // cout << line << endl;
        string source;
        string destination;
        string weight;
        istringstream iss(line);
        getline(iss, source, ',');
        getline(iss, destination, ',');
        getline(iss, weight, ',');
        // Assuming the CSV format is correct, add data to the map
        // cout<<source<<" ";
        // cout<<destination<<" ";
        // cout<<weight<<endl;
        graph.addEdge(stoi(source), stoi(destination), stoi(weight));
    }
    // cout << "end of file" << endl;
    csvFile.close();

    return graph;
}

void FileHandler::printMap() {
    cout << "Encoded Location :: \n";
    for (auto x : FileHandler::placeToValueMap)
        cout << x.first << " " <<
        x.second << endl;
    cout << "Decoded Location :: \n";
    for (auto x : FileHandler::valueToPlaceMap)
        cout << x.first << " " <<
        x.second << endl;
}
