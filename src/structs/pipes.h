//
// Created by loading on 05-03-2024.
//

#ifndef DA_PROJECT1_PIPES_H
#define DA_PROJECT1_PIPES_H

#include <unordered_set>
#include <string>
using namespace std;
class Pipes{
private:
    int id;
    string ori;
    string dest;
    int capacity;
    bool direction;
public:
    Pipes();
    Pipes(int id);
    Pipes(int id,string ori, string dest, int capacity, bool direction);
    int getId() const {return id;}
    string getOri() const {return ori;}
    string getDest() const {return dest;}
    int getCapacity() const {return capacity;}
    bool getDirection() const {return direction;}
};

struct pipesHash{

    int operator() (const Pipes& b) const {
        const string& code = b.getId();
        unsigned  int hash = 5381;

        for(char c: b.getId()){
            hash = 33*hash + static_cast<unsigned int>(c);
        }

        return hash % 449;
    }


    bool operator()(const Pipes &b1, const Pipes &b2) const {
        return b1.getId() == b2.getId();
    }
};


typedef unordered_set<Pipes, pipesHash, pipesHash> PipesTable;
class HashPipes{
public:
    PipesTable pipestable;
    void readLines();
};



#endif //DA_PROJECT1_PIPES_H
