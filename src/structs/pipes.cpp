//
// Created by loading on 05-03-2024.
//
#include <fstream>
#include <sstream>
#include <vector>
#include "pipes.h"
using namespace std;
void Pipes::ReadLines(HashReservoirs hashReservoirs,HashCities hashCities, HashStations hashStations) {
    string input = "../src/structs/dataset/airlines.csv";
    ifstream MyReadFile(input);

    string line;

    getline(MyReadFile, line);
    while (std::getline(MyReadFile, line)) {
        stringstream ss(line);
        string sa;
        string sb;
        string cap;
        string dir;
        getline(ss, sa, ',');
        getline(ss, sb, ',');
        getline(ss, cap, ',');
        getline(ss, dir, ',');

        if(stoi(dir)==1)
        {
            pipes.addEdge(sa,sb,stod(cap));
        }
        else
        {
            pipes.addBidirectionalEdge(sa,sb,stod(cap));
        }
    }



    }
