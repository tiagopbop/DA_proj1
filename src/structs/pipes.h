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
class Pipes{
public:
    Graph<string> pipes;
    void ReadLines(HashReservoirs hashReservoirs, HashCities hashcities, HashStations hashStations);
};




#endif //DA_PROJECT1_PIPES_H
