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
    void ReadLines_copy_reservoirs(const Reservoirs& reservoirs, int decision);
    void ReadLines_copy_station(const Stations& stations, int decision);
    void ReadLines_copy_edgeless(int decision, const pair<string,string>& pp);

    static void OneCity(Graph<string> pipe,const HashCities& citii, const HashReservoirs& reserr, int chs_fl);
    static bool check_existing_edge(const string& origin, const string& destiny, const vector<pair<string,string>>& rawr);

    //void Max_flow_specific_city(string super_source, string super_sink, Graph<string> pipe, )

    static void balanceLoad(Pipes& pipes,const HashCities& citii, const HashReservoirs& reserr);
    static void computeInitialMetrics(const Pipes& pipes, int whi);


    static void edmondsKarp(const string& source, const string& target, const Graph<string>& pipe);
    static void augmentFlowAlongPath(Vertex<string> *s, Vertex<string> *t, double f);
    static double findMinResidualAlongPath(Vertex<string> *s, Vertex<string> *t);
    static bool findAugmentingPath( Vertex<string> *s, Vertex<string> *t, const Graph<string>& pipe);
    static void testAndVisit(std::queue< Vertex<string>*> &q, Edge<string> *e, Vertex<string> *w, double residual);

    };

struct max_flow_info{
    string city_name;
    string city_code;
};




#endif //DA_PROJECT1_PIPES_H
