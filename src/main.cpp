#include "structs/pipes.h"
#include "structs/cities.h"
#include "structs/reservoirs.h"
#include "structs/stations.h"
#include "menu.h"
using namespace std;
//
// Created by loading on 05-03-2024.
//

int main() {
    HashCities hashCities;
    hashCities.readLines();

    HashPipes hashPipes;
    hashPipes.readLines();

    HashReservoirs hashReservoirs;
    hashReservoirs.readLines();

    HashStations hashStations;
    hashStations.readLines();

    Menu::Terminal();

    return 0;
}