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
        stringstream ss(line);
        string id;
        string code;
        getline(ss, id, ',');
        getline(ss, code, ',');

        stations = Stations(stoi(id), code);
        this->stationsTable.insert(stations);
    }
}

int Stations::getId() const {
    return this->id;
}

string Stations::getCode() const {
    return this->code;
}

Stations::Stations() {
    this->id = 0;
    this->code = "PS_0";
}

Stations::Stations(int id) {
    this->id = id;
    this->code = "PS_0";
}

Stations::Stations(int id, string code) {
    this->id = id;
    this->code = code;
}