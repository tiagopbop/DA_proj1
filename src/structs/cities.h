//
// Created by loading on 05-03-2024.
//

#ifndef DA_PROJECT1_CITIES_H
#define DA_PROJECT1_CITIES_H


#include <string>
#include <unordered_set>
#include "Graph.h"
#include "pipes.h"

using namespace std;
class Pipes;
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
    void setCode(string code);
};

struct CitiesHash {
    int operator() (const Cities& b) const {
        const string& code = b.getCode();
        unsigned  int hash = 5381;

        for(char c: b.getCode()){
            hash = 33*hash + static_cast<unsigned int>(c);
        }

        return hash % 3019;
    }



    bool operator()(const Cities &b1, const Cities &b2) const {
        return b1.getCode() == b2.getCode();
    }
};


typedef unordered_set<Cities, CitiesHash,CitiesHash> CitiesTable;

class HashCities{
public:
    CitiesTable citiesTable;
    void readLines(Pipes &pipes, int decision);


    const Cities* findCity(const string& code) const {
        Cities dummyStation; // Create a dummy Stations object with the given code
        dummyStation.setCode(code);

        auto it = citiesTable.find(dummyStation);
        if (it != citiesTable.end()) {
            return &(*it); // Return a pointer to the found object
        } else {
            return nullptr; // Object not found
        }
    }};




#endif //DA_PROJECT1_CITIES_H
