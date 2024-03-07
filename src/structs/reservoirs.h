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
    string id;
    string code;
    string max_del;
public:
    Reservoirs();
    Reservoirs(string id);
    Reservoirs(string name, string municipality, string code, string demand, string population);
    string getName() const;
    string getMunicipality() const;
    string getId() const;
    string getCode() const;
    string getMaxDel() const;
};

struct reservoirsHash{

    int operator() (const Reservoirs& b) const {
        const string& code = b.getCode();
        unsigned  int hash = 5381;

        for(char c: b.getCode()){
            hash = 33*hash + static_cast<unsigned int>(c);
        }

        return hash % 449;
    }


    bool operator()(const Reservoirs &b1, const Reservoirs &b2) const {
        return b1.getCode() == b2.getCode();
    }
};


typedef unordered_set<Reservoirs, reservoirsHash, reservoirsHash> ReservoirsTable;
class HashReservoirs{
public:
    ReservoirsTable reservoirsTable;
    void readLines();
};

#endif //DA_PROJECT1_RESERVOIRS_H
