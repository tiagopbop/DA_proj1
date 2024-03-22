#include "structs/pipes.h"
#include "structs/cities.h"
#include "structs/reservoirs.h"
#include "structs/stations.h"
#include "menu.h"
#include <fstream>
#include <sstream>
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


    pipes.edmondsKarp("R_1","C_10");

    std::stringstream ss;
    cout<<"Starting graphread"<<endl;
    for(auto v : pipes.pipes.getVertexSet()) {
        ss << v->getInfo() << "-> (";
        for (const auto e : v->getAdj())
            ss << (e->getDest())->getInfo() << "[Flow: " << e->getFlow() << "] ";
        ss << ") || ";
    }

    std::cout << ss.str() << std::endl << std::endl;

    Vertex<string>* v = pipes.pipes.findVertex("C_10");
    double res = 0;
    for(auto a : v->getIncoming()){
        res = res + a->getFlow();
    }

    cout<<"Agua da cidade: "<<v->getInfo()<<" = "<<res;

    Menu::Terminal();


    return 0;
}