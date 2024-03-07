//
// Created by loading on 05-03-2024.
//
#include <fstream>
#include <sstream>
#include "stations.h"
using namespace std;
void HashStations::readLines() {
    string input = "../src/structs/dataset/airlines.csv";
    ifstream MyReadFile(input);

    string line;
    Stations stations;

    getline(MyReadFile, line);

    while (std::getline(MyReadFile, line)) {
        vector<std::string> values;
        stringstream ss(line);

        while (ss.good()) {
            std::string subtr;
            getline(ss, subtr, ',');
            values.push_back(subtr);
        }

        stations = Stations(values[0], values[1]);
        this->stationsTable.insert(stations);
    }
}