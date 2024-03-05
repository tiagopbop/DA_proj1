//
// Created by loading on 05-03-2024.
//
#include <fstream>
#include <sstream>
#include <vector>
#include "pipes.h"
using namespace std;
void HashCities::readLines() {
    string input = "../src/structs/dataset/airlines.csv";
    ifstream MyReadFile(input);

    string line;
    Pipes pipes;

    getline(MyReadFile, line);
    int count = -1;
    while (std::getline(MyReadFile, line)) {
        count++;
        vector<std::string> values;
        stringstream ss(line);

        while (ss.good()) {
            std::string subtr;
            getline(ss, subtr, ',');
            values.push_back(subtr);
        }

        pipes = Pipes(to_string(count),values[0], values[1], values[2], values[3], values[4]);
        this->pipesTable.insert(pipes);
    }
}