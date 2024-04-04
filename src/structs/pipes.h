//
// Created by loading on 05-03-2024.
//

#ifndef DA_PROJECT1_PIPES_H
#define DA_PROJECT1_PIPES_H

#include <unordered_set>
#include <string>
#include "Graph.h"
#include "reservoirs.h"
#include "cities.h"
#include "stations.h"


using namespace std;
class HashStations;
class HashCities;
class HashReservoirs;
class Stations;
class Pipes{
public:
    Graph<string> pipes;
    Graph<string> pipes_copy;

    void ReadLines(HashReservoirs hashReservoirs, HashCities hashcities, HashStations hashStations, int decision);
    void ReadLines_copy(HashReservoirs hashReservoirs, HashCities hashcities, HashStations hashStations, Stations stations, int decision);

    void OneCity(string source, string target, Graph<string> pipe);
    string maxFlow(bool specific, string city);
    void edmondsKarp(string source, string target, Graph<string> pipe);
    void augmentFlowAlongPath(Vertex<string> *s, Vertex<string> *t, double f);
    double findMinResidualAlongPath(Vertex<string> *s, Vertex<string> *t);
    bool findAugmentingPath( Vertex<string> *s, Vertex<string> *t, Graph<string> pipe);
    void testAndVisit(std::queue< Vertex<string>*> &q, Edge<string> *e, Vertex<string> *w, double residual);

    };

struct max_flow_info{
    string city_name;
    string city_code;
    int flow;
};




#endif //DA_PROJECT1_PIPES_H
