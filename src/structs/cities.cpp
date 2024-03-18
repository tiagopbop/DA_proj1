//
// Created by loading on 05-03-2024.
//
#include <fstream>
#include <sstream>
#include "cities.h"
using namespace std;
void HashCities::readLines() {
    string input = "../src/structs/dataset/airlines.csv";
    ifstream MyReadFile(input);

    string line;

    getline(MyReadFile, line);

    string city;
    string id;
    string code;
    string demand;
    string population;

    while (std::getline(MyReadFile, line)) {
        stringstream ss(line);


        getline(ss, city, ',');
        getline(ss, id, ',');
        getline(ss, code, ',');
        getline(ss, demand, ',');
        getline(ss, population, ',');


        Cities cities = Cities(city, stoi(id),code,stof(demand),population);
        this->citiesTable.insert(cities);
    }
}

    Cities::Cities(string city, string id, string code, string demand, string population)
    {
        this->city = city;
        this->id = id;
        this->code=code;
        this->demand=demand;
        this->population=population;
    }
    string Cities:: getId() const
    {
        return this->id;
    }
    string Cities:: getName() const
    {
        return this->city;
    }
    string Cities:: getCode() const
    {
        return this->code;
    }
    string Cities::getDemand() const
    {
        return this->demand;
    }
    string Cities:: getPopulation() const{
        return this->population;
}