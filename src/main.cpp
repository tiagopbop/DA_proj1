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

    pipes.pipes.addVertex("super_source");
    pipes.pipes.addVertex("super_sink");

    Vertex<string>* super_source = pipes.pipes.findVertex("super_source");
    Vertex<string>* super_sink = pipes.pipes.findVertex("super_sink");

    int choise;
    cout<<"1- Maximum amount of water that can reach each city"<<endl;
    cout<<"2- Maximum amount of water that can reach a city of your choice"<<endl;
    cin>>choise;
    switch (choise) {
        case 1:{
            int choise_1;
            cout<<"1- With overflow"<<endl;
            cout<<"2- Without overflow"<<endl;
            cin>>choise_1;
            switch (choise_1) {
                case 1:{
                    for(auto a : hashReservoirs.reservoirsTable){
                        Vertex<string>* add = pipes.pipes.findVertex(a.getCode());
                        pipes.pipes.addEdge(super_source->getInfo(), add->getInfo(), a.getMaxDel());
                    }

                    for(auto a : hashCities.citiesTable){
                        Vertex<string>* add = pipes.pipes.findVertex(a.getCode());
                        pipes.pipes.addEdge(add->getInfo(),super_sink->getInfo(), INT_MAX);
                    }
                    pipes.edmondsKarp(super_source->getInfo(),super_sink->getInfo());
                    double max_flow = 0;
                    for(auto a : hashCities.citiesTable){
                        double res = 0;
                        Vertex<string>* check_flow = pipes.pipes.findVertex(a.getCode());
                        for(auto b : check_flow->getIncoming()){
                            res = res + b->getFlow();
                        }
                        max_flow = max_flow + res;
                        cout<<a.getName()<<", "<<a.getCode()<<", "<<res<<endl;
                    }
                    cout<<"Max Flow = "<<max_flow<<endl;
                    break;
                }
                case 2:{
                    for(auto a : hashReservoirs.reservoirsTable){
                        Vertex<string>* add = pipes.pipes.findVertex(a.getCode());
                        pipes.pipes.addEdge(super_source->getInfo(), add->getInfo(), a.getMaxDel());
                    }

                    for(auto a : hashCities.citiesTable){
                        Vertex<string>* add = pipes.pipes.findVertex(a.getCode());
                        pipes.pipes.addEdge(add->getInfo(),super_sink->getInfo(), a.getDemand());
                    }
                    pipes.edmondsKarp(super_source->getInfo(),super_sink->getInfo());
                    double max_flow = 0;
                    for(auto a : hashCities.citiesTable){
                        double res = 0;
                        Vertex<string>* check_flow = pipes.pipes.findVertex(a.getCode());
                        for(auto b : check_flow->getIncoming()){
                            res = res + b->getFlow();
                        }
                        max_flow = max_flow + res;
                        cout<<a.getName()<<", "<<a.getCode()<<", "<<res<<endl;
                    }
                    cout<<"Max Flow = "<<max_flow<<endl;
                    break;
                }
                default:{
                    break;
                }
            }
            break;
        }
        case 2:{
            string code;
            cout<<"Write the code of the desired city"<<endl;
            cin>>code;
            string city_name;
            string city_code;
            double res = 0;
            for(auto a : hashReservoirs.reservoirsTable){
                Vertex<string>* add = pipes.pipes.findVertex(a.getCode());
                pipes.pipes.addEdge(super_source->getInfo(), add->getInfo(), a.getMaxDel());
            }
            for(auto a : hashCities.citiesTable){
                if(a.getCode() == code){
                    city_name = a.getName();
                    city_code = a.getCode();
                    Vertex<string>* add = pipes.pipes.findVertex(a.getCode());
                    pipes.pipes.addEdge(add->getInfo(),super_sink->getInfo(), INT_MAX);
                }
            }
            pipes.edmondsKarp(super_source->getInfo(),super_sink->getInfo());
            for(auto a : hashCities.citiesTable){
                if(a.getCode() == code){
                    Vertex<string>* check_flow = pipes.pipes.findVertex(a.getCode());
                    for(auto b: check_flow->getIncoming()){
                        res = res + b->getFlow();
                    }
                }
            }
            cout<<city_name<<", "<<city_code<<", "<<res<<endl;
        }
        default:{
            break;
        }
        break;
    }


    //pipes.edmondsKarp("R_1","C_10");

    /*std::stringstream ss;
    cout<<"Starting graphread"<<endl;
    for(auto v : pipes.pipes.getVertexSet()) {
        ss << v->getInfo() << "-> (";
        for (const auto e : v->getAdj())
            ss << (e->getDest())->getInfo() << "[Flow: " << e->getFlow() << "] ";
        ss << ") || ";
    }

    std::cout << ss.str() << std::endl << std::endl;*/

    //Menu::Terminal();


    return 0;
}