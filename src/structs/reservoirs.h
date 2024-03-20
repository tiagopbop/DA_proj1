//
// Created by loading on 05-03-2024.
//

#ifndef DA_PROJECT1_RESERVOIRS_H
#define DA_PROJECT1_RESERVOIRS_H
#include <string>
#include <unordered_set>
#include "Graph.h"
using namespace std;
class Reservoirs{
private:
    string name;
    string municipality;
    int id;
    string code;
    int max_del;
public:
    Reservoirs();
    Reservoirs(int id);
    Reservoirs(string name, string municipality, int id, string code, int max_del);
    string getName() const;
    string getMunicipality() const;
    int getId() const;
    string getCode() const;
    int getMaxDel() const;
    void setCode(string code);
};

struct ReservoirsHash {
    int operator() (const Reservoirs& b) const {
        const string& code = b.getCode();
        unsigned  int hash = 5381;

        for(char c: b.getCode()){
            hash = 33*hash + static_cast<unsigned int>(c);
        }

        return hash % 3019;
    }


    bool operator()(const Reservoirs &b1, const Reservoirs &b2) const {
        return b1.getCode() == b2.getCode();
    }
};


typedef unordered_set<Reservoirs, ReservoirsHash,ReservoirsHash> ReservoirsTable;

class HashReservoirs{
public:
    ReservoirsTable reservoirsTable;
    void readLines();

    const Reservoirs* findReservoir(const string& code) const {
        Reservoirs dummyStation; // Create a dummy Stations object with the given code
        dummyStation.setCode(code);

        auto it = reservoirsTable.find(dummyStation);
        if (it != reservoirsTable.end()) {
            return &(*it); // Return a pointer to the found object
        } else {
            return nullptr; // Object not found
        }
    }};


#endif //DA_PROJECT1_RESERVOIRS_H
