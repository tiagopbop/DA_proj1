#include "structs/pipes.h"
#include "structs/cities.h"
#include "structs/reservoirs.h"
#include "structs/stations.h"
#include "menu.h"
#include <fstream>
#include <sstream>
#include <limits.h>
#include <cmath>
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
    cout<<"3- Média de flow dos canos"<<endl;
    cout<<"4- Diferença entre capacidade e flow de cada cano"<<endl;
    cin>>choise;

    vector<string> not_full;

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

                        const Cities* d = hashCities.findCity(a.getCode());
                        if(res<d->getDemand())
                        {
                            not_full.push_back(a.getName());
                            not_full.push_back(a.getCode());
                            double missing = (d->getDemand()) - res;
                            not_full.push_back(to_string(missing));
                        }

                    }
                    cout<<"Max Flow = "<<max_flow<<endl;
                    cout << "Do you want to check if there are cities where the flow isn't enough? (Y/N)" << endl<< "Decision:";
                    string decision;
                    cin >> decision;
                    if(decision=="Y")
                    {
                        for (size_t i = 0; i < not_full.size() - 2; i += 3) {
                            cout << not_full[i] << ", " << not_full[i + 1] << ", " << stoi(not_full[i + 2]) << endl;
                        }                    }
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
        /*
        case 3:{
            int som = 0;
            int tot = 0;

            for (auto e : Vetor de pipes resultante do edmond karp ) {
                som += e->getFlow();
                tot++;
            }

            double res = som / tot;

            cout << endl << "A média é " << res << endl;
        }
        case 4:{
            int flo;
            int cap;
            int res;

            int max = 0;

            for (auto e : Vetor de pipes resultante do edmond karp ) {
                flo = e->getFlow();
                cap = e->getCapacidade();

                res = cap - flo;

                if (res > max) {
                    max = res;
                }

                cout << endl << "O cano " << e->getCode() << " tem uma diferença de " << res;
            }
            cout << endl;

            cout << endl << "Diferença máxima é de " << max << endl;
        }
        */
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