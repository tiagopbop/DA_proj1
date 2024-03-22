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
    Pipes pipes;

    HashCities hashCities;
    hashCities.readLines(pipes);


    HashReservoirs hashReservoirs;
    hashReservoirs.readLines(pipes);

    HashStations hashStations;
    hashStations.readLines(pipes);

    pipes.ReadLines(hashReservoirs,hashCities,hashStations);

   /* const Reservoirs* c = hashReservoirs.findReservoir("R_2");
    if (c) {
        std::cout << "Station found: " << c->getCode() << std::endl;
    } else {
        std::cout << "Station not found" << std::endl;
    }*/


  //  for(auto a: hashCities.citiesTable)
    //    cout<<a.getName()<<endl;

    for(auto a: pipes.pipes.getVertexSet())
        cout<<a->getInfo() << endl;

    
    Menu::Terminal();


    return 0;
}