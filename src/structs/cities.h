//
// Created by loading on 05-03-2024.
//
/*
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
    int population;
public:
    Cities();
    Cities(int id);
    Cities(string city, int id, string code, float demand, int population);
    int getId();
    string getName();
    string getCode();
    float getDemand();
    int getPopulation();
};

struct citiesHash{

    int operator() (const Cities& b) const {
        const string& code = b.getCode();
        unsigned  int hash = 5381;

        for(char c: b.getCode()){
            hash = 33*hash + static_cast<unsigned int>(c);
        }

        return hash % 449;
    }


    bool operator()(const Airlines &b1, const Airlines &b2) const {
        return b1.getCode() == b2.getCode();
    }
};


typedef unordered_set<Cities, citiesHash, citiesHash> citiesTable;
class HashCities{
public:
    CitiesTable citiesTable;
    void readLines();
};


#endif //DA_PROJECT1_CITIES_H
*/