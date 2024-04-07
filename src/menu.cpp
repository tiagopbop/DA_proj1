#include <iostream>
#include "menu.h"
#include "structs/pipes.h"
#include "structs/cities.h"
#include "structs/reservoirs.h"
#include "structs/stations.h"

using namespace std;
vector<Pipes::max_flow_info> pipi;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"

int Menu::Terminal() {

    Pipes pipes;
    int decision;
    int chs_fl;
    string input;

    cout << endl;
    cout << "\033[1;34mWelcome to the Water Supply Management Analysis Tool\033[0m" << endl;
    cout << endl;
    cout << "\033[1;33mPlease select the data origin to be analyzed\033[0m" << endl;
    cout << "\033[1;33m[ 1 ]\033[0m" << " Continental Portugal" << endl;
    cout << "\033[1;33m[ 2 ]\033[0m" << " 'Madeira' Island" << endl;
    cout << "\033[0;33mDISCLAIMER : This can be changed later without restarting the program\033[0m" << endl;
    cout << endl;

    cout << "\033[1;34mDecision: \033[0m";
    cin >> chs_fl;
    cout << endl;

    HashCities hashCities;
    hashCities.readLines(pipes, chs_fl);

    hashCities.readLines(pipes,chs_fl);

    HashReservoirs hashReservoirs;
    hashReservoirs.readLines(pipes,chs_fl);

    HashStations hashStations;
    hashStations.readLines(pipes,chs_fl);

    pipes.ReadLines(chs_fl);

    pipes.pipes.addVertex("super_source");
    pipes.pipes.addVertex("super_sink");

    Vertex<string>* super_source;
    Vertex<string>* super_sink;

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
                    pipes.pipes.removeVertex("super_sink");
                    pipes.pipes.removeVertex("super_source");
                    pipes.pipes.addVertex("super_source");
                    pipes.pipes.addVertex("super_sink");

                    super_source = pipes.pipes.findVertex("super_source");
                    super_sink = pipes.pipes.findVertex("super_sink");

                    cout << "\033[1;36m[ 1 ]\033[0m"
                         << " Maximum amount of water that can reach each or a specific city"
                         << endl;
                    cout << "\033[1;36m[ 2 ]\033[0m"
                         << " Balance the load of water across the entire network"
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
                            cout
                                    << "\033[0;33mDISCLAIMER : While specifying a city, it is always checked without overflow\033[0m"
                                    << endl;
                            cin >> input;
                            cout << endl << endl;

                            if (input == "y" || input == "Y") {

                                cout << "\033[1;34mWhich city? \033[0m";
                                cin >> input;
                                cout << endl << endl;

                                Pipes::Max_flow_specific_city(super_source, super_sink, pipes.pipes, hashCities, hashReservoirs, input);

                            } else if (input == "n" || input == "N") {

                                cout << "\033[1;34mDo you wish to consider overflow? \033[0m"
                                     << "\033[1;33m [ Y | N ]\033[0m" << endl;
                                cin >> input;
                                cout << endl << endl;

                                if (input == "y" || input == "Y") {

                                    Pipes::Max_flow_non_specific_city_with_overflow(super_source, super_sink, pipes.pipes, hashCities, hashReservoirs, input, not_full, pipi);

                                } else if (input == "n" || input == "N") {

                                    Pipes::Max_flow_non_specific_city_without_overflow(super_source, super_sink, pipes.pipes, hashCities, hashReservoirs, input, not_full, pipi);

                                } else {

                                    cout << "\033[1;31mInput error - Going back\033[0m" << endl << endl;

                                }

                            } else {

                                cout << "\033[1;31mInput error - Going back\033[0m" << endl << endl;

                            }

                            break;
                        case 2:

                            for (const auto& a: hashReservoirs.reservoirsTable) {
                                Vertex<string> *add = pipes.pipes.findVertex(a.getCode());
                                pipes.pipes.addEdge(super_source->getInfo(), add->getInfo(), a.getMaxDel());
                            }

                            for (const auto& a: hashCities.citiesTable) {
                                Vertex<string> *add = pipes.pipes.findVertex(a.getCode());
                                pipes.pipes.addEdge(add->getInfo(), super_sink->getInfo(), a.getDemand());
                            }
                            Pipes::edmondsKarp(super_source->getInfo(), super_sink->getInfo(), pipes.pipes);
                            for (const auto& a: hashCities.citiesTable) {
                                double res = 0;
                                Vertex<string> *check_flow = pipes.pipes.findVertex(a.getCode());
                                for (auto b: check_flow->getIncoming()) {
                                    res = res + b->getFlow();
                                }
                            }
                            Pipes::computeInitialMetrics(pipes, 0);
                            Pipes::balanceLoad(pipes,hashCities,hashReservoirs);

                            break;
                        case 0: case 9:

                            break;
                        default:

                            cout << "\033[1;31mInput error - Going back\033[0m" << endl << endl;

                            break;
                    }

                }

                break;
            case 2:

                while (decision != 0 && decision != 9) {

                    pipes.pipes.removeVertex("super_sink");
                    pipes.pipes.removeVertex("super_source");
                    pipes.pipes.addVertex("super_source");
                    pipes.pipes.addVertex("super_sink");

                    super_source = pipes.pipes.findVertex("super_source");
                    super_sink = pipes.pipes.findVertex("super_sink");

                    cout << "\033[1;36m[ 1 ]\033[0m"
                         << " Check the delivery capacity of the network putting one water reservoir out of commission"
                         << endl;
                    cout << "\033[1;36m[ 2 ]\033[0m"
                         << " Check the effects of a temporary removal of each or one specific pumping station" << endl;
                    cout << "\033[1;36m[ 3 ]\033[0m"
                         << " Check the affected cities for each pipe that is taken out of commission"
                         << endl;
                    cout << "\033[1;36m[ 4 ]\033[0m"
                         << " Check the pipes that affect a specific city if taken out of commission"
                         << endl;
                    cout << "\033[1;33m[ 9 ] Go back\033[0m" << endl;
                    cout << "\033[1;31m[ 0 ] Quit\033[0m" << endl;
                    cout << endl;

                    cout << "\033[1;34mDecision: \033[0m";
                    cin >> decision;
                    cout << endl << endl;

                    Pipes pipes_copy;
                    HashStations stations_copy;
                    HashCities cities_copy;
                    HashReservoirs reservoirs_copy;
                    vector<Stations> stations_vector;

                    HashReservoirs reservoirs;
                    HashCities cities;

                    switch (decision) {
                        case 1:

                            reservoirs.readLines(pipes, chs_fl);
                            cities.readLines(pipes, chs_fl);

                            Pipes::Removing_reservoir(super_source, super_sink, pipes.pipes, cities, reservoirs, input, not_full, chs_fl, cities_copy, reservoirs_copy, stations_copy, pipes_copy);

                            break;

                        case 2:

                            cout << "\033[1;36m[ 1 ]\033[0m" << " Print the effect of removing each pumping station"
                                 << endl;
                            cout << "\033[1;36m[ 2 ]\033[0m"
                                 << " Select a specific pumping station to be removed"
                                 << endl;
                            cout << "\033[1;33m[ 9 ] Go back to initial menu\033[0m" << endl;
                            cout << "\033[1;31m[ 0 ] Quit\033[0m" << endl;
                            cout << endl;

                            cout << "\033[1;34mDecision: \033[0m";
                            cin >> decision;
                            cout << endl;

                            switch (decision) {
                                case 1:

                                    stations_copy.readLines(pipes_copy, chs_fl);
                                    for(const auto& a: stations_copy.stationsTable){
                                        stations_vector.push_back(a);
                                    }
                                    stations_copy.stationsTable.clear();
                                    for (const auto& a: stations_vector) {
                                        stations_copy.readLines(pipes_copy, chs_fl);
                                        cities_copy.readLines(pipes_copy, chs_fl);
                                        reservoirs_copy.readLines(pipes_copy, chs_fl);
                                        pipes_copy.ReadLines_copy_station(a, chs_fl);
                                        pipes_copy.pipes_copy.addVertex("super_source");
                                        pipes_copy.pipes_copy.addVertex("super_sink");
                                        Vertex<string> *super_source_copy = pipes_copy.pipes_copy.findVertex("super_source");
                                        Vertex<string> *super_sink_copy = pipes_copy.pipes_copy.findVertex("super_sink");

                                        for (const auto& j: reservoirs_copy.reservoirsTable) {
                                            Vertex<string> *add = pipes_copy.pipes_copy.findVertex(j.getCode());
                                            pipes_copy.pipes_copy.addEdge(super_source_copy->getInfo(), add->getInfo(),j.getMaxDel());
                                        }
                                        for (const auto& k: cities_copy.citiesTable) {
                                            Vertex<string> *add = pipes_copy.pipes_copy.findVertex(k.getCode());
                                            pipes_copy.pipes_copy.addEdge(add->getInfo(), super_sink_copy->getInfo(),k.getDemand());
                                        }

                                        Pipes::edmondsKarp(super_source_copy->getInfo(), super_sink_copy->getInfo(),pipes_copy.pipes_copy);

                                        cout << "\033[0;32m ⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯ ⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯ \033[0m" << endl;
                                        cout << "\033[0;32m│⎯\033[0m" << "\033[1;33mPumping\033[0m" << "\033[0;32m⎯\033[0m" << "\033[1;33mstation\033[0m" << "\033[0;32m⎯\033[0m" << "\033[1;33mremoved\033[0m" << "\033[0;32m⎯⎯⎯⎯⎯│⎯\033[0m" << a.getCode();
                                        for (auto i = (10 - a.getCode().length()); i > 0; i--) {
                                            cout << "\033[0;32m⎯\033[0m";
                                        }
                                        cout << "\033[0;32m│\033[0m" << endl;

                                        cout << "\033[0;32m│⎯\033[0m" << "\033[1;33mCode\033[0m" << "\033[0;32m⎯⎯⎯│⎯\033[0m" << "\033[1;33mFlow\033[0m" << "\033[0;32m⎯⎯⎯⎯│⎯\033[0m" << "\033[1;33mDemand\033[0m" << "\033[0;32m⎯⎯⎯│⎯\033[0m" << "\033[1;33mDeficit\033[0m" << "\033[0;32m⎯⎯⎯│\033[0m" << endl;


                                        for (const auto& b: cities_copy.citiesTable) {
                                            Vertex<string> *check_incoming = pipes_copy.pipes_copy.findVertex(b.getCode());
                                            double flow = 0;
                                            for (auto c: check_incoming->getIncoming()) {
                                                flow = flow + c->getFlow();
                                            }

                                            cout << "\033[0;32m│⎯\033[0m" << b.getCode();
                                            for (auto i = (7 - b.getCode().length()); i > 0; i--) {
                                                cout << "\033[0;32m⎯\033[0m";
                                            }
                                            cout << "\033[0;32m│⎯\033[0m" << flow;
                                            for (auto i = (15 - to_string(flow).length()); i > 0; i--) {
                                                cout << "\033[0;32m⎯\033[0m";
                                            }
                                            cout << "\033[0;32m│⎯\033[0m" << b.getDemand();
                                            for (auto i = (9 - to_string((int)b.getDemand()).length()); i > 0; i--) {
                                                cout << "\033[0;32m⎯\033[0m";
                                            }

                                            if (flow < b.getDemand()) {
                                                double deficit = b.getDemand() - flow;

                                                cout << "\033[0;32m│⎯\033[0m" << deficit;
                                                for (auto i = (17 - to_string(deficit).length()); i > 0; i--) {
                                                    cout << "\033[0;32m⎯\033[0m";
                                                }
                                                cout << "\033[0;32m│\033[0m";

                                            } else {
                                                cout << "\033[0;32m│⎯\033[0m" << "None" << "\033[0;32m⎯⎯⎯⎯⎯⎯│\033[0m";
                                            }
                                            cout<<endl;
                                        }
                                        cout<<endl;

                                        for (auto v: pipes_copy.pipes_copy.getVertexSet()) {
                                            for (auto e: v->getAdj()) {
                                                pipes_copy.pipes_copy.removeEdge(v->getInfo(), e->getDest()->getInfo());
                                            }
                                            pipes_copy.pipes_copy.removeVertex(v->getInfo());
                                        }

                                    }
                                    cout << endl;
                                    break;

                                case 2 :

                                    cout << "\033[1;34mWhich pumping station? \033[0m";
                                    cin >> input;
                                    cout << endl << endl;

                                    stations_copy.readLines(pipes_copy, chs_fl);
                                    cities_copy.readLines(pipes_copy, chs_fl);
                                    reservoirs_copy.readLines(pipes_copy, chs_fl);
                                    for (const auto& a: stations_copy.stationsTable) {
                                        if (a.getCode() == input) {
                                            pipes_copy.ReadLines_copy_station(a, chs_fl);
                                            pipes_copy.pipes_copy.addVertex("super_source");
                                            pipes_copy.pipes_copy.addVertex("super_sink");
                                            Vertex<string> *super_source_copy = pipes_copy.pipes_copy.findVertex(
                                                    "super_source");
                                            Vertex<string> *super_sink_copy = pipes_copy.pipes_copy.findVertex("super_sink");

                                            for (const auto& j: reservoirs_copy.reservoirsTable) {
                                                Vertex<string> *add = pipes_copy.pipes_copy.findVertex(j.getCode());
                                                pipes_copy.pipes_copy.addEdge(super_source_copy->getInfo(), add->getInfo(),
                                                                              j.getMaxDel());
                                            }
                                            for (const auto& k: cities_copy.citiesTable) {
                                                Vertex<string> *add = pipes_copy.pipes_copy.findVertex(k.getCode());
                                                pipes_copy.pipes_copy.addEdge(add->getInfo(), super_sink_copy->getInfo(),
                                                                              k.getDemand());
                                            }

                                            Pipes::edmondsKarp(super_source_copy->getInfo(), super_sink_copy->getInfo(),
                                                                   pipes_copy.pipes_copy);

                                            cout << "\033[0;32m ⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯ ⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯ \033[0m" << endl;
                                            cout << "\033[0;32m│⎯\033[0m" << "\033[1;33mPumping\033[0m" << "\033[0;32m⎯\033[0m" << "\033[1;33mstation\033[0m" << "\033[0;32m⎯\033[0m" << "\033[1;33mremoved\033[0m" << "\033[0;32m⎯⎯⎯⎯⎯│⎯\033[0m" << input;
                                            for (auto i = (10 - input.length()); i > 0; i--) {
                                                cout << "\033[0;32m⎯\033[0m";
                                            }
                                            cout << "\033[0;32m│\033[0m" << endl;

                                            cout << "\033[0;32m│⎯\033[0m" << "\033[1;33mCode\033[0m" << "\033[0;32m⎯⎯⎯│⎯\033[0m" << "\033[1;33mFlow\033[0m" << "\033[0;32m⎯⎯⎯⎯│⎯\033[0m" << "\033[1;33mDemand\033[0m" << "\033[0;32m⎯⎯⎯│⎯\033[0m" << "\033[1;33mDeficit\033[0m" << "\033[0;32m⎯⎯⎯│\033[0m" << endl;

                                            for (const auto& b: cities_copy.citiesTable) {
                                                Vertex<string> *check_incoming = pipes_copy.pipes_copy.findVertex(b.getCode());
                                                double flow = 0;
                                                for (auto c: check_incoming->getIncoming()) {
                                                    flow = flow + c->getFlow();
                                                }

                                                cout << "\033[0;32m│⎯\033[0m" << b.getCode();
                                                for (auto i = (7 - b.getCode().length()); i > 0; i--) {
                                                    cout << "\033[0;32m⎯\033[0m";
                                                }
                                                cout << "\033[0;32m│⎯\033[0m" << flow;
                                                for (auto i = (15 - to_string(flow).length()); i > 0; i--) {
                                                    cout << "\033[0;32m⎯\033[0m";
                                                }
                                                cout << "\033[0;32m│⎯\033[0m" << b.getDemand();
                                                for (auto i = (9 - to_string((int)b.getDemand()).length()); i > 0; i--) {
                                                    cout << "\033[0;32m⎯\033[0m";
                                                }

                                                if (flow < b.getDemand()) {
                                                    double deficit = b.getDemand() - flow;

                                                    cout << "\033[0;32m│⎯\033[0m" << deficit;
                                                    for (auto i = (17 - to_string(deficit).length()); i > 0; i--) {
                                                        cout << "\033[0;32m⎯\033[0m";
                                                    }
                                                    cout << "\033[0;32m│\033[0m";

                                                } else {
                                                    cout << "\033[0;32m│⎯\033[0m" << "None" << "\033[0;32m⎯⎯⎯⎯⎯⎯│\033[0m";
                                                }
                                                cout << endl;
                                            }
                                            cout << endl << endl;

                                            for (auto v: pipes_copy.pipes_copy.getVertexSet()) {
                                                for (auto e: v->getAdj()) {
                                                    pipes_copy.pipes_copy.removeEdge(v->getInfo(), e->getDest()->getInfo());
                                                }
                                                pipes_copy.pipes_copy.removeVertex(v->getInfo());
                                            }
                                        }
                                    }
                                    break;

                                case 0: case 9:

                                    break;
                                default:

                                    cout << "\033[1;31mInput error - Going back\033[0m" << endl << endl;

                                    break;
                            }
                            break;
                        case 3:

                            Pipes::AllPipes(pipes.pipes,hashCities, hashReservoirs,chs_fl);

                            for(auto a: pipes.pipes.getVertexSet())
                            {
                                for(auto b: a->getAdj())
                                {
                                    b->setFlow(0);
                                }
                            }
                            break;
                        case 4:

                            cout << "\033[1;34mWhich city? \033[0m";
                            cin >> input;
                            cout << endl << endl;

                            Pipes::OneCity(pipes.pipes, hashCities,hashReservoirs,  chs_fl,input);

                            for(auto a: pipes.pipes.getVertexSet())
                            {
                                for(auto b: a->getAdj())
                                {
                                    b->setFlow(0);
                                }
                            }

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
                    cout << "\033[1;32mSwitched to 'Madeira' successfully\033[0m" << endl << endl;
                    chs_fl = 2;
                } else {
                    cout << "\033[1;32mSwitched to Continental Portugal successfully\033[0m" << endl << endl;
                    chs_fl = 1;
                }

                hashCities.readLines(pipes,chs_fl);
                hashReservoirs.readLines(pipes,chs_fl);
                hashStations.readLines(pipes,chs_fl);

                pipes.ReadLines(chs_fl);

                pipes.pipes.addVertex("super_source");
                pipes.pipes.addVertex("super_sink");

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
#pragma clang diagnostic pop