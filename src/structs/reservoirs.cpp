//
// Created by loading on 05-03-2024.
//
#include <fstream>
#include <sstream>
#include "reservoirs.h"
#include "pipes.h"
#include <string>
#include <iostream>
using namespace std;
void HashReservoirs::readLines(Pipes &pipes) {
    string input = "../data/Reservoirs_Madeira.csv";
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

        int a = stoi(id);
        double b = stod(max_del);
        reservoirs = Reservoirs(reser, municipality, a, code, b);
        pipes.pipes.addVertex(code);
        this->reservoirsTable.insert(reservoirs);
    }
}

Reservoirs::Reservoirs() {
    this->name = "Portugal";
    this->municipality = "Portugal";
    this->id = 0;
    this->code = "R_0";
    this->max_del = 0;
}

Reservoirs::Reservoirs(int id) {
    this->name = "Portugal";
    this->municipality = "Portugal";
    this->id = id;
    this->code = "R_0";
    this->max_del = 0;
}

Reservoirs::Reservoirs(string name, string municipality, int id, string code, int max_del) {
    this->name = name;
    this->municipality = municipality;
    this->id = id;
    this->code = code;
    this->max_del = max_del;
}

string Reservoirs::getName() const {
    return this->name;
}

string Reservoirs::getMunicipality() const {
    return this->municipality;
}

int Reservoirs::getId() const {
    return this->id;
}

string Reservoirs::getCode() const {
    return this->code;
}
void Reservoirs::setCode(std::string code) {
    this->code=code;
}
int Reservoirs::getMaxDel() const {
    return this->max_del;
}