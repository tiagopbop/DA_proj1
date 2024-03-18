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
    Reservoirs reservoirs;

    getline(MyReadFile, line);

    while (std::getline(MyReadFile, line)) {
        stringstream ss(line);
        string reser;
        string municipality;
        string id;
        string code;
        string max_del;
        getline(ss, reser, ',');
        getline(ss, municipality, ',');
        getline(ss, id, ',');
        getline(ss, code, ',');
        getline(ss, max_del, ',');


        reservoirs = Reservoirs(reser, municipality, stoi(id), code, stoi(max_del));
        this->reservoirsTable.insert(reservoirs);
    }
}