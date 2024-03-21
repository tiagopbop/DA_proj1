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

string Cities::maxFlow(bool specific, string city) {

    int max = 0;
    if (specific) {

        vector<int> path;

        auto d = findVertex(city);

        for (auto v : pipes->getVertexSet()) {

            int max = 0;
            for (auto v : pipes->getVertexSet()) {
                v->setVisited(false);
            }

            if (v->getInfo()[0] == "R") {

                auto s = findVertex(v);
                queue <Vertex<T>*> q;
                q.push(s);
                s->setVisited(true);

                auto w = s;
                while (!q.empty() && w->getInfo() != city) {
                    auto a = q.front();
                    q.pop();
                    path.push_back(a->getInfo());
                    for (auto &e: a->getAdj()) {
                        if (e->getWeight() < max) {
                            max = e->getWeight();
                        }
                        w = e->getDest();
                        if (!w->isVisited()) {
                            q.push(w);
                            w->setVisited(true);
                        }
                    }
                }
                auto a = q.front();
                path.push_back(a->getInfo());


            }

        }
    }
    else {


    }

}
