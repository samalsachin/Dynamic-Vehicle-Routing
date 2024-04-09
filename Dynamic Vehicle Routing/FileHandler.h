#ifndef FILEHANDLER_H_INCLUDED
#define FILEHANDLER_H_INCLUDED

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "map.h"

using namespace std;

class FileHandler
{
private:
    void loadEncodingFromCSV(const string& csvFilePath);
public:
    unordered_map<string, int> placeToValueMap;
    unordered_map<int, string> valueToPlaceMap;

    FileHandler(const string& csvFilePath);

    int encodeLocation(const string& placeName) const;

    string decodeLocation(int encodedValue) const;

    void printMap();

    void writeInCSV(const string& data);

    // Function to initialise the graph from a csv file containing source, destination and weight data
    Graph loadGraphFromCSV(string filename, int nodesCount);
};

#endif // !FILEHANDLER_H_INCLUDED

