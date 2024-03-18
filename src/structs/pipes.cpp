//
// Created by loading on 05-03-2024.
//
#include <fstream>
#include <sstream>
#include <vector>
#include "pipes.h"
using namespace std;
void HashPipes::readLines() {
    string input = "../src/structs/dataset/airlines.csv";
    ifstream MyReadFile(input);

    string line;

    getline(MyReadFile, line);
    int count = -1;
    while (std::getline(MyReadFile, line)) {
        count++;
        stringstream ss(line);
        string sa;
        string sb;
        string cap;
        string dir;
        getline(ss, sa, ',');
        getline(ss, sb, ',');
        getline(ss, cap, ',');
        getline(ss, dir, ',');
        Pipes pipes = Pipes(count,sa,sb,stoi(cap),stoi(dir));
        this->pipestable.insert(pipes);
    }
}
Pipes::Pipes(){
    this->id = 0;
    this->ori = "R_1";
    this->dest = "PS_1";
    this->capacity = 100;
    this->direction = true;
}
Pipes::Pipes(int id){
    this->id = id;
    this->ori = "R_1";
    this->dest = "PS_1";
    this->capacity = 100;
    this->direction = true;
}
Pipes::Pipes(int id,string ori, string dest, int capacity, int direction){
    this->id = id;
    this->ori = ori;
    this->dest = dest;
    this->capacity = capacity;
    this->direction = direction;
}
