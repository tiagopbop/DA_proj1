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
};

struct ReservoirsHash {
    size_t operator()(const Reservoirs& reservoir) const {
        return hash<int>()(reservoir.getId());
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
};

#endif //DA_PROJECT1_RESERVOIRS_H
