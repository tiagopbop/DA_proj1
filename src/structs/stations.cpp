//
// Created by loading on 05-03-2024.
//
#include <fstream>
#include <sstream>
#include "stations.h"
#include "pipes.h"
#include <string>
#include <iostream>
using namespace std;
void HashStations::readLines(Pipes &pipes, int decision) {

    string input;

    if (decision == 1) {
        input = "../data/Stations.csv";
    } else {
        input = "../data/Stations_Madeira.csv";
    }

    ifstream MyReadFile(input);

    string line;
    Stations stations;

    getline(MyReadFile, line);

    while (std::getline(MyReadFile, line)) {
        stringstream ss(line);
        string id;
        string code;
        getline(ss, id, ',');

        if (decision == 1) {
            getline(ss, code, '\r');
        } else {
            getline(ss, code, ',');
        }

        int a = stoi(id);
        stations = Stations(a, code);
        pipes.pipes.addVertex(code);
        this->stationsTable.insert(stations);
    }
}


int Stations::getId() const {
    return this->id;
}

string Stations::getCode() const {
    return this->code;
}

void Stations::setCode(string code) {
    this->code = code;
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