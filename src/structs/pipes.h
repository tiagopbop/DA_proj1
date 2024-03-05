//
// Created by loading on 05-03-2024.
//

#ifndef DA_PROJECT1_PIPES_H
#define DA_PROJECT1_PIPES_H

#include <unordered_set>

using namespace std;
class Pipes{
private:
    string id;
    string ori;
    string dest;
    string capacity;
    string direction;
public:
    Pipes();
    Pipes(int id);
    Pipes(string id,string ori, string dest, string capacity, string direction);
    string getId();
    string getName();
    string getCode();
    string getDemand();
    string getPopulation();
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


    bool operator()(const Pipes &b1, const Pipes &b2) const {
        return b1.getCode() == b2.getCode();
    }
};


typedef unordered_set<Pipes, pipesHash, pipesHash> pipesTable;
class HashCities{
public:
    Pipestable pipestable;
    void readLines();
};



#endif //DA_PROJECT1_PIPES_H
