#include <iostream>
#include <climits>
#include "menu.h"
#include "structs/pipes.h"
#include "structs/cities.h"
#include "structs/reservoirs.h"
#include "structs/stations.h"

using namespace std;
vector<max_flow_info> pipi;

int Menu::Terminal() {

    Pipes pipes;

    int decision;
    int chs_fl;
    string input;

    cout << endl;
    cout << "\033[1;34mWelcome to the Water Supply Management Analysis Tool\033[0m" << endl;
    cout << endl;
    cout << "\033[1;33mPlease select the data origin to be analyzed?\033[0m" << endl;
    cout << "\033[1;33m[ 1 ]\033[0m" << " Continental Portugal" << endl;
    cout << "\033[1;33m[ 2 ]\033[0m" << " 'Madeira' Island" << endl;
    cout << endl;
    cout << "\033[1;33m[ This can be changed later without restarting the program ]\033[0m" << endl;
    cout << endl;

    cout << "\033[1;34mDecision: \033[0m";
    cin >> chs_fl;
    cout << endl;

    HashCities hashCities;
    hashCities.readLines(pipes,chs_fl);

    HashReservoirs hashReservoirs;
    hashReservoirs.readLines(pipes,chs_fl);

    HashStations hashStations;
    hashStations.readLines(pipes,chs_fl);

    pipes.ReadLines(hashReservoirs,hashCities,hashStations,chs_fl);

    pipes.pipes.addVertex("super_source");
    pipes.pipes.addVertex("super_sink");

    Vertex<string>* super_source;
    Vertex<string>* super_sink;

    super_source = pipes.pipes.findVertex("super_source");
    super_sink = pipes.pipes.findVertex("super_sink");

    vector<string> not_full;

    if (chs_fl == 1) {
        cout << "\033[1;32mContinental Portugal chosen successfully\033[0m" << endl;
    } else if (chs_fl == 2) {
        cout << "\033[1;32mIsland 'Madeira' chosen successfully\033[0m" << endl;
    } else {
        cout << "\033[1;33mUnrecognized answer - Proceeding with 'Madeira'\033[0m" << endl;
    }

    cout << endl << endl;
    cout << "\033[1;34mWhat do you wish to do?\033[0m" << endl;

    cout << "\033[1;36m[ 1 ]\033[0m" << " Basic Service Metrics" << endl;
    cout << "\033[1;36m[ 2 ]\033[0m" << " Reliability and Sensitivity to Failures" << endl;
    cout << "\033[1;33m[ 9 ] Change the input data being analyzed\033[0m" << endl;
    cout << "\033[1;31m[ 0 ] Quit\033[0m" << endl;
    cout << endl;

    cout << "\033[1;34mDecision: \033[0m";
    cin >> decision;
    cout << endl << endl;

    while (decision != 0) {

        switch (decision) {
            case 1:

                while (decision != 0 && decision != 9) {

                    cout << "\033[1;36m[ 1 ]\033[0m" << " Maximum amount of water that can reach each or a specific city"
                         << endl;
                    cout << "\033[1;36m[ 2 ]\033[0m"
                         << " Check the water supply given to every delivery site and list those who have a deficit"
                         << endl;
                    cout << "\033[1;36m[ 3 ]\033[0m"
                         << " Balance the load of water across the entire network (Não percebi bem esta, vejam melhor depois)"
                         << endl;
                    cout << "\033[1;33m[ 9 ] Go back\033[0m" << endl;
                    cout << "\033[1;31m[ 0 ] Quit\033[0m" << endl;
                    cout << endl;

                    cout << "\033[1;34mDecision: \033[0m";
                    cin >> decision;
                    cout << endl << endl;

                    switch (decision) {
                        case 1:

                            cout << "\033[1;34mDo you want to check a specific city? \033[0m"
                                 << "\033[1;33m [ Y | N ]\033[0m" << endl;
                            cout << "\033[1;33mDISCLAIMER : While specifying a city, it is always checked assuming overflow\033[0m" << endl;
                            cin >> input;
                            cout << endl << endl;

                            if (input == "y" || input == "Y") {

                                cout << "\033[1;34mWhich city? \033[0m";
                                cin >> input;
                                cout << endl << endl;

                                string city_name;
                                string city_code;
                                double res = 0;
                                for(auto a : hashReservoirs.reservoirsTable){
                                    Vertex<string>* add = pipes.pipes.findVertex(a.getCode());
                                    pipes.pipes.addEdge(super_source->getInfo(), add->getInfo(), a.getMaxDel());
                                }
                                for(auto a : hashCities.citiesTable){
                                    if(a.getCode() == input){
                                        city_name = a.getName();
                                        city_code = a.getCode();
                                        Vertex<string>* add = pipes.pipes.findVertex(a.getCode());
                                        pipes.pipes.addEdge(add->getInfo(),super_sink->getInfo(), INT_MAX);
                                    }
                                }
                                pipes.edmondsKarp(super_source->getInfo(),super_sink->getInfo());
                                for(auto a : hashCities.citiesTable){
                                    if(a.getCode() == input){
                                        Vertex<string>* check_flow = pipes.pipes.findVertex(a.getCode());
                                        for(auto b: check_flow->getIncoming()){
                                            res = res + b->getFlow();
                                        }
                                    }
                                }
                                cout << "\033[1;32mCity \033[0m" << city_name << "\033[1;32m of code \033[0m" << city_code << "\033[1;32m has a maximum flow of \033[0m" << res << endl << endl << endl;

                                decision = 9;

                            } else if (input == "n" || input == "N") {

                                cout << "\033[1;34mDo you wish to consider overflow? \033[0m" << "\033[1;33m [ Y | N ]\033[0m" << endl;
                                cin >> input;
                                cout << endl << endl;

                                if (input == "y" || input == "Y") {

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
                                        cout << "\033[1;32mCity \033[0m" << a.getName() << "\033[1;32m of code \033[0m" << a.getCode() << "\033[1;32m has a maximum flow of \033[0m" << res << endl;

                                    }
                                    cout << endl << "\033[1;32mMaximum total flow is \033[0m" << max_flow << endl << endl;

                                    cout << "\033[1;34mDo you wish to check for any cities where the flow isn't enough? \033[0m" << "\033[1;33m [ Y | N ]\033[0m" << endl;
                                    cin >> input;
                                    cout << endl << endl;

                                    if (input == "y" || input == "Y") {

                                        for (size_t i = 0; i < not_full.size() - 2; i += 3) {
                                            cout << "\033[1;32mCity \033[0m" << not_full[i] << "\033[1;32m of code \033[0m" << not_full[i + 1] << "\033[1;32m has a maximum flow of \033[0m" << stoi(not_full[i + 2]) << endl << endl << endl;
                                        }

                                    }

                                    decision = 9;

                                } else if (input == "n" || input == "N") {

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
                                        cout << "\033[1;32mCity \033[0m" << a.getName() << "\033[1;32m of code \033[0m" << a.getCode() << "\033[1;32m has a maximum flow of \033[0m" << res << endl;

  //adicionei aqui guardar maxflow numa struct
                                        max_flow_info m;
                                        m.city_name = a.getName();
                                        m.city_code = a.getCode();
                                        m.flow = res;
                                        pipi.push_back(m);

                                        const Cities* d = hashCities.findCity(a.getCode());
                                        if(res<d->getDemand())
                                        {
                                            not_full.push_back(a.getName());
                                            not_full.push_back(a.getCode());
                                            double missing = (d->getDemand()) - res;
                                            not_full.push_back(to_string(missing));
                                        }

                                    }


                                    cout << endl << "\033[1;32mMaximum total flow is \033[0m" << max_flow << endl << endl;

                                    cout << "\033[1;34mDo you wish to check for any cities where the flow isn't enough? \033[0m" << "\033[1;33m [ Y | N ]\033[0m" << endl;
                                    cin >> input;
                                    cout << endl << endl;

                                    if (input == "y" || input == "Y") {

                                        for (size_t i = 0; i < not_full.size() - 2; i += 3) {
                                            cout << "\033[1;32mCity \033[0m" << not_full[i] << "\033[1;32m of code \033[0m" << not_full[i + 1] << "\033[1;32m has a maximum flow of \033[0m" << stoi(not_full[i + 2]) << endl;
                                        }
                                        cout << endl << endl;

                                    }

                                    decision = 9;

                                } else {

                                    cout << "\033[1;31mInput error - Going back\033[0m" << endl << endl;

                                }

                            } else {

                                cout << "\033[1;31mInput error - Going back\033[0m" << endl << endl;

                            }

                            break;
                        case 2:


                            break;
                        case 3:


                            break;
                        case 9: case 0:

                            break;
                        default:

                            cout << "\033[1;31mInput error - Going back\033[0m" << endl << endl;

                            break;
                    }

                }

                break;
            case 2:

                while (decision != 0 && decision != 9) {

                    cout << "\033[1;36m[ 1 ]\033[0m"
                         << " Check the delivery capacity of the network putting one water reservoir out of commission"
                         << endl;
                    cout << "\033[1;36m[ 2 ]\033[0m"
                         << " Check the effects of a temporary removal of each pumping station" << endl;
                    cout << "\033[1;36m[ 3 ]\033[0m"
                         << " Check which pipelines would make it impossible to deliver the desired amount of water, for each city"
                         << endl;
                    cout << "\033[1;33m[ 9 ] Go back\033[0m" << endl;
                    cout << "\033[1;31m[ 0 ] Quit\033[0m" << endl;
                    cout << endl;

                    cout << "\033[1;34mDecision: \033[0m";
                    cin >> decision;
                    cout << endl << endl;

                    switch (decision) {
                        case 1:

                            cout << "\033[1;34mWhich water reservoir?\033[0m";
                            cin >> input;
                            cout << endl << endl;


                            break;
                        case 2:


                            break;
                        case 3:


                            break;
                        case 0: case 9:

                            break;
                        default:

                            cout << "\033[1;31mInput error - Going back\033[0m" << endl << endl;

                            break;
                    }

                }

                break;
            case 9:

                for (auto v : pipes.pipes.getVertexSet()) {
                    for (auto e : v->getAdj()) {
                        pipes.pipes.removeEdge(v->getInfo(), e->getDest()->getInfo());
                    }
                    pipes.pipes.removeVertex(v->getInfo());
                }

                hashCities.citiesTable.clear();
                hashReservoirs.reservoirsTable.clear();
                hashStations.stationsTable.clear();

                if (chs_fl == 1) {
                    cout << "\033[1;32mSwitched to 'Madeira' successfully\033[0m" << endl;
                    chs_fl = 2;
                } else {
                    cout << "\033[1;32mSwitched to Continental Portugal successfully\033[0m" << endl;
                    chs_fl = 1;
                }

                hashCities.readLines(pipes,chs_fl);
                hashReservoirs.readLines(pipes,chs_fl);
                hashStations.readLines(pipes,chs_fl);

                pipes.ReadLines(hashReservoirs,hashCities,hashStations,chs_fl);

                pipes.pipes.addVertex("super_source");
                pipes.pipes.addVertex("super_sink");

                super_source = pipes.pipes.findVertex("super_source");
                super_sink = pipes.pipes.findVertex("super_sink");

                break;
            case 0:

                break;
            default:

                cout << "\033[1;31mInput error - Going back\033[0m" << endl << endl;
                decision = 1;

                break;
        }

        if (decision != 0) {

            cout << "\033[1;34mWish to do anything else?\033[0m" << endl;

            cout << "\033[1;36m[ 1 ]\033[0m" << " Basic Service Metrics" << endl;
            cout << "\033[1;36m[ 2 ]\033[0m" << " Reliability and Sensitivity to Failures" << endl;
            cout << "\033[1;33m[ 9 ] Change the input data being analyzed\033[0m" << endl;
            cout << "\033[1;31m[ 0 ] Quit\033[0m" << endl;
            cout << endl;

            cout << "\033[1;34mDecision: \033[0m";
            cin >> decision;
            cout << endl << endl;

        }

    }

    return 0;
}