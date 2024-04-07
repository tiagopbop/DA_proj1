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
class Reservoirs;
class Pipes{
public:
    Graph<string> pipes;
    Graph<string> pipes_copy;

    void ReadLines(int decision);
    void ReadLines_copy_reservoirs(Reservoirs reservoirs, int decision);
    void ReadLines_copy_station(Stations stations, int decision);
    void ReadLines_copy_edgeless(int decision, pair<string,string> pp);

    void OneCity(Graph<string> pipe,HashCities citii, HashReservoirs reserr, int chs_fl);
    bool check_existing_edge(string origin, string destiny, vector<pair<string,string>> rawr);

    //void Max_flow_specific_city(string super_source, string super_sink, Graph<string> pipe, )

    void balanceLoad(Pipes pipes,HashCities citii, HashReservoirs reserr);
    void computeInitialMetrics(Pipes pipes);


    void edmondsKarp(string source, string target, Graph<string> pipe);
    void augmentFlowAlongPath(Vertex<string> *s, Vertex<string> *t, double f);
    double findMinResidualAlongPath(Vertex<string> *s, Vertex<string> *t);
    bool findAugmentingPath( Vertex<string> *s, Vertex<string> *t, Graph<string> pipe);
    void testAndVisit(std::queue< Vertex<string>*> &q, Edge<string> *e, Vertex<string> *w, double residual);

    };

struct max_flow_info{
    string city_name;
    string city_code;
};




#endif //DA_PROJECT1_PIPES_H
