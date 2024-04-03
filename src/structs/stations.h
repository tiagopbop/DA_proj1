//
// Created by loading on 05-03-2024.
//

#ifndef DA_PROJECT1_STATIONS_H
#define DA_PROJECT1_STATIONS_H
#include <string>
#include <unordered_set>
#include "Graph.h"
#include "pipes.h"

using namespace std;
class Pipes;
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
    void setCode(string code);
};

struct StationsHash {
    int operator() (const Stations& b) const {
        const string& code = b.getCode();
        unsigned  int hash = 5381;

        for(char c: b.getCode()){
            hash = 33*hash + static_cast<unsigned int>(c);
        }

        return hash % 3019;
    }


    bool operator()(const Stations &b1, const Stations &b2) const {
        return b1.getCode() == b2.getCode();
    }
};


typedef unordered_set<Stations, StationsHash, StationsHash>StationsTable;
class HashStations{
public:
    StationsTable stationsTable;
    void readLines(Pipes &pipes, int decision);


    const Stations* findStation(const string& code) const {
        Stations dummyStation; // Create a dummy Stations object with the given code
        dummyStation.setCode(code);

        auto it = stationsTable.find(dummyStation);
        if (it != stationsTable.end()) {
            return &(*it); // Return a pointer to the found object
        } else {
            return nullptr; // Object not found
        }
    }};


#endif //DA_PROJECT1_STATIONS_H
