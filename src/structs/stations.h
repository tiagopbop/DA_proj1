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

struct StationsHash {
    size_t operator()(const Stations& station) const {
        return hash<int>()(station.getId());
    }


    bool operator()(const Stations &b1, const Stations &b2) const {
        return b1.getCode() == b2.getCode();
    }
};


typedef unordered_set<Stations, StationsHash,
>StationsTable;
class HashStations{
public:
    StationsTable stationsTable;
    void readLines();
};


#endif //DA_PROJECT1_STATIONS_H
