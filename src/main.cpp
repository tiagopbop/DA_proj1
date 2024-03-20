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


    HashReservoirs hashReservoirs;
    hashReservoirs.readLines();

    HashStations hashStations;
    hashStations.readLines();

    Pipes pipes;
    pipes.ReadLines(hashReservoirs,hashCities,hashStations);

    const Reservoirs* c = hashReservoirs.findReservoir("R_2");
    if (c) {
        std::cout << "Station found: " << c->getCode() << std::endl;
    } else {
        std::cout << "Station not found" << std::endl;
    }    Menu::Terminal();

    return 0;
}