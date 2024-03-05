//
// Created by loading on 05-03-2024.
//
#include <fstream>
#include <sstream>
#include "reservoirs.h"
using namespace std;
void HashReservoirs::readLines() {
    string input = "../src/structs/dataset/airlines.csv";
    ifstream MyReadFile(input);

    string line;
    Cities cities;

    getline(MyReadFile, line);

    while (std::getline(MyReadFile, line)) {
        vector<std::string> values;
        stringstream ss(line);

        while (ss.good()) {
            std::string subtr;
            getline(ss, subtr, ',');
            values.push_back(subtr);
        }

        cities = Cities(values[0], values[1], values[2], values[3], values[4]);
        this->citiesTable.insert(cities);
    }
}