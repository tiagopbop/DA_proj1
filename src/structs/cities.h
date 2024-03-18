//
// Created by loading on 05-03-2024.
//

#ifndef DA_PROJECT1_CITIES_H
#define DA_PROJECT1_CITIES_H


#include <string>
#include <unordered_set>
#include "Graph.h"
using namespace std;
class Cities{
private:
    string city;
    int id;
    string code;
    float demand;
    string population;
public:
    Cities();
    Cities(int id);
    Cities(string city, int id, string code, float demand, string population);
    int getId() const;
    string getName() const;
    string getCode() const;
    float getDemand() const;
    string getPopulation() const;
};

struct CitiesHash {
    size_t operator()(const Cities& city) const {
        return hash<int>()(city.getId());
    }


    bool operator()(const Cities &b1, const Cities &b2) const {
        return b1.getCode() == b2.getCode();
    }
};


typedef unordered_set<Cities, CitiesHash,CitiesHash> CitiesTable;

class HashCities{
public:
    CitiesTable citiesTable;
    void readLines();
};


#endif //DA_PROJECT1_CITIES_H
