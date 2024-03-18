//
// Created by loading on 05-03-2024.
//

#ifndef DA_PROJECT1_STATIONS_H
#define DA_PROJECT1_STATIONS_H
#include <string>
#include <unordered_set>
#include "Graph.h"
using namespace std;
class Stations{
private:
    int id;
    string code;
public:
    Stations();
    Stations(int id);
    Stations(int id, string code);
    int getId() const;
    string getCode() const;
};

struct stationsHash{

    int operator() (const Stations& b) const {
        const string& code = b.getCode();
        unsigned  int hash = 5381;

        for(char c: b.getCode()){
            hash = 33*hash + static_cast<unsigned int>(c);
        }

        return hash % 449;
    }


    bool operator()(const Stations &b1, const Stations &b2) const {
        return b1.getCode() == b2.getCode();
    }
};


typedef unordered_set<Stations, stationsHash, stationsHash> StationsTable;
class HashStations{
public:
    stationsTable StationsTable;
    void readLines();
};

#endif //DA_PROJECT1_STATIONS_H
