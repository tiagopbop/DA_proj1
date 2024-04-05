//
// Created by loading on 05-03-2024.
//
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "cities.h"
#include "pipes.h"

using namespace std;
void HashCities::readLines(Pipes &pipes, int decision) {

    string input;

    if (decision == 1) {
        input = "../data/Cities.csv";
    } else {
        input = "../data/Cities_Madeira.csv";
    }

    ifstream MyReadFile(input);

    string line;

    getline(MyReadFile, line);



    while (std::getline(MyReadFile, line)) {
        stringstream ss(line);

        string city;
        string id;
        string code;
        string demand;
        string population;
        getline(ss, city, ',');
        getline(ss, id, ',');
        getline(ss, code, ',');
        getline(ss, demand, ',');
        getline(ss, population, ',');

        int a = stoi(id);
        float b = stof(demand);
        Cities cities = Cities(city, a,code,b,population);
        pipes.pipes.addVertex(code);
        pipes.pipes_copy.addVertex(code);
        this->citiesTable.insert(cities);
    }
}

    Cities::Cities() {
        this->city = "Portugal";
        this->id = 0;
        this->code = "C_0";
        this->demand = 0.0;
        this->population = "0";
    }
    Cities::Cities(int id) {
        this->city = "Portugal";
        this->id = id;
        this->code = "C_0";
        this->demand = 0.0;
        this->population = "0";
    }
    Cities::Cities(string city, int id, string code, float demand, string population)
    {
        this->city = city;
        this->id = id;
        this->code = code;
        this->demand = demand;
        this->population = population;
    }
    int Cities::getId() const
    {
        return this->id;
    }
    string Cities::getName() const
    {
        return this->city;
    }
    string Cities::getCode() const
    {
        return this->code;
    }
    void Cities::setCode(std::string code) {
        this->code = code;
}
    float Cities::getDemand() const
    {
        return this->demand;
    }
    string Cities::getPopulation() const{
        return this->population;
}

