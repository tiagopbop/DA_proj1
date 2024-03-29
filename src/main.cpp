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

   /* const Reservoirs* c = hashReservoirs.findReservoir("R_2");
    if (c) {
        std::cout << "Station found: " << c->getCode() << std::endl;
    } else {
        std::cout << "Station not found" << std::endl;
    }*/
/*
    int choise;
    cout<<"3- Média de flow dos canos"<<endl;
    cout<<"4- Diferença entre capacidade e flow de cada cano"<<endl;
    cin>>choise;

    switch (choise) {

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
        default:{
            break;
        }
        break;
    }
         */


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

    Menu::Terminal();


    return 0;
}