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
    struct max_flow_info{
        string city_name;
        string city_code;
    };

    Graph<string> pipes;
    Graph<string> pipes_copy;

    void ReadLines(int decision);
    void ReadLines_copy_reservoirs(const Reservoirs& reservoirs, int decision);
    void ReadLines_copy_station(const Stations& stations, int decision);
    void ReadLines_copy_edgeless(int decision, const pair<string,string>& pp);

    static void AllPipes(Graph<string> pipe,const HashCities& citii, const HashReservoirs& reserr, int chs_fl);
    static void OneCity(Graph<string>pipe,const HashCities& citii, const HashReservoirs& reserr, int chs_fl, string cit);
    static bool check_existing_edge(const string& origin, const string& destiny, const vector<pair<string,string>>& rawr);

    static void Max_flow_specific_city(Vertex<string> * super_source, Vertex<string> * super_sink, Graph<string> pipes, HashCities hashCities, HashReservoirs hashReservoirs, string input);
    static void Max_flow_non_specific_city_with_overflow(Vertex<string> * super_source, Vertex<string> * super_sink, Graph<string> pipes, HashCities hashCities, HashReservoirs hashReservoirs, string input, vector<string> not_full, vector<max_flow_info> pipi);
    static void Max_flow_non_specific_city_without_overflow(Vertex<string> * super_source, Vertex<string> * super_sink, Graph<string> pipes, HashCities hashCities, HashReservoirs hashReservoirs, string input, vector<string> not_full, vector<max_flow_info> pipi);

    static void Removing_reservoir(Vertex<string> * super_source, Vertex<string> * super_sink, Graph<string> pipes, HashCities cities, HashReservoirs reservoirs, string input, vector<string> not_full, int chs_fl, HashCities cities_copy, HashReservoirs reservoirs_copy, HashStations stations_copy, Pipes pipes_copy);
    static void Removing_each_station(HashStations stations_copy, int chs_fl, Pipes pipes_copy, HashCities cities_copy, HashReservoirs reservoirs_copy);



    static void balanceLoad(Pipes& pipes,const HashCities& citii, const HashReservoirs& reserr);
    static void computeInitialMetrics(const Pipes& pipes, int whi);


    static void edmondsKarp(const string& source, const string& target, const Graph<string>& pipe);
    static void augmentFlowAlongPath(Vertex<string> *s, Vertex<string> *t, double f);
    static double findMinResidualAlongPath(Vertex<string> *s, Vertex<string> *t);
    static bool findAugmentingPath( Vertex<string> *s, Vertex<string> *t, const Graph<string>& pipe);
    static void testAndVisit(std::queue< Vertex<string>*> &q, Edge<string> *e, Vertex<string> *w, double residual);

    };




#endif //DA_PROJECT1_PIPES_H
