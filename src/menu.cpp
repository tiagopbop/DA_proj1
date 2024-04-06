#include <iostream>
#include <climits>
#include "menu.h"
#include "structs/pipes.h"
#include "structs/cities.h"
#include "structs/reservoirs.h"
#include "structs/stations.h"

using namespace std;
vector<max_flow_info> pipi;

/*int Menu::flush() {
    puts("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    return 0;
}*/

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
    cout << "\033[1;33mDISCLAIMER : This can be changed later without restarting the program\033[0m" << endl;
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
        pipes.pipes.removeVertex("super_sink");
        pipes.pipes.removeVertex("super_source");
        pipes.pipes.addVertex("super_source");
        pipes.pipes.addVertex("super_sink");

        super_source = pipes.pipes.findVertex("super_source");
        super_sink = pipes.pipes.findVertex("super_sink");
        switch (decision) {
            case 1:

                while (decision != 0 && decision != 9) {
                    pipes.pipes.removeVertex("super_sink");
                    pipes.pipes.removeVertex("super_source");
                    pipes.pipes.addVertex("super_source");
                    pipes.pipes.addVertex("super_sink");

                    super_source = pipes.pipes.findVertex("super_source");
                    super_sink = pipes.pipes.findVertex("super_sink");

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
                                        pipes.pipes.addEdge(add->getInfo(),super_sink->getInfo(), a.getDemand());
                                    }
                                }
                                pipes.edmondsKarp(super_source->getInfo(),super_sink->getInfo(), pipes.pipes);
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
                                    pipes.edmondsKarp(super_source->getInfo(),super_sink->getInfo(), pipes.pipes);
                                    double max_flow = 0;
                                    for(auto a : hashCities.citiesTable){
                                        double res = 0;
                                        Vertex<string>* check_flow = pipes.pipes.findVertex(a.getCode());
                                        for(auto b : check_flow->getIncoming()){
                                            res = res + b->getFlow();
                                        }
                                        max_flow = max_flow + res;
                                        cout << "City " << a.getName() << " of code " << a.getCode() << " has a maximum flow of " << res << endl;

                                    }
                                    cout << endl << "\033[1;32mMaximum total flow is \033[0m" << max_flow << endl << endl;

                                    cout << "\033[1;34mDo you wish to check for any cities where the flow isn't enough? \033[0m" << "\033[1;33m [ Y | N ]\033[0m" << endl;
                                    cin >> input;
                                    cout << endl << endl;

                                    if (input == "y" || input == "Y") {

                                        for (size_t i = 0; i < not_full.size() - 2; i += 3) {
                                            cout << "\033[1;32mCity \033[0m" << not_full[i] << "\033[1;32m of code \033[0m" << not_full[i + 1] << "\033[1;32m has a maximum flow of \033[0m" << stoi(not_full[i + 2]) << endl << endl << endl;
                                        }

                                    } else if (input == "n" || input == "N") {
                                        continue;
                                    } else {
                                        cout << "\033[1;31mInput error - Moving on\033[0m" << endl << endl;
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
                                    pipes.edmondsKarp(super_source->getInfo(),super_sink->getInfo(), pipes.pipes);
                                    double max_flow = 0;
                                    for(auto a : hashCities.citiesTable){
                                        double res = 0;
                                        Vertex<string>* check_flow = pipes.pipes.findVertex(a.getCode());
                                        for(auto b : check_flow->getIncoming()){
                                            res = res + b->getFlow();
                                        }
                                        max_flow = max_flow + res;
                                        cout << "City " << a.getName() << " of code " << a.getCode() << " has a maximum flow of " << res << endl;

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

                                    } else if (input == "n" || input == "N") {
                                        continue;
                                    } else {
                                        cout << "\033[1;31mInput error - Moving on\033[0m" << endl << endl;
                                    }

                                    decision = 9;

                                } else {

                                    cout << "\033[1;31mInput error - Going back\033[0m" << endl << endl;

                                }

                            } else {

                                cout << "\033[1;31mInput error - Going back\033[0m" << endl << endl;

                            }

                            break;
                        case 2: {

                            break;
                        }
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
                            cout << "para implementar" << endl;

                            break;
                        case 2: {
                            cout<<"1 - Check if any pumping station can be temporarily taken out of service without affecting the delivery capacity to all the cities"<<endl;
                            cout<<"2 - Select a pumping stations to be removed"<<endl;
                            int pumping_station;
                            cin>>pumping_station;

                            switch (pumping_station) {
                                case 1:{
                                    bool print = true;
                                    Pipes pipes_copy;
                                    HashStations stations_copy;
                                    HashCities cities_copy;
                                    HashReservoirs reservoirs_copy;
                                    vector<Stations> stations_vector;
                                    stations_copy.readLines(pipes_copy, chs_fl);
                                    for(auto a: stations_copy.stationsTable){
                                        stations_vector.push_back(a);
                                    }
                                    stations_copy.stationsTable.clear();
                                    for (auto a: stations_vector) {
                                        stations_copy.readLines(pipes_copy, chs_fl);
                                        cities_copy.readLines(pipes_copy, chs_fl);
                                        reservoirs_copy.readLines(pipes_copy, chs_fl);
                                        pipes_copy.ReadLines_copy(reservoirs_copy, cities_copy, stations_copy, a, chs_fl);
                                        pipes_copy.pipes_copy.addVertex("super_source");
                                        pipes_copy.pipes_copy.addVertex("super_sink");
                                        Vertex<string> *super_source_copy = pipes_copy.pipes_copy.findVertex("super_source");
                                        Vertex<string> *super_sink_copy = pipes_copy.pipes_copy.findVertex("super_sink");

                                        for (auto j: reservoirs_copy.reservoirsTable) {
                                            Vertex<string> *add = pipes_copy.pipes_copy.findVertex(j.getCode());
                                            pipes_copy.pipes_copy.addEdge(super_source_copy->getInfo(), add->getInfo(),j.getMaxDel());
                                        }
                                        for (auto k: cities_copy.citiesTable) {
                                            Vertex<string> *add = pipes_copy.pipes_copy.findVertex(k.getCode());
                                            pipes_copy.pipes_copy.addEdge(add->getInfo(), super_sink_copy->getInfo(),k.getDemand());
                                        }

                                        pipes_copy.edmondsKarp(super_source_copy->getInfo(), super_sink_copy->getInfo(),pipes_copy.pipes_copy);
                                        bool has_water = false;
                                        for (auto b: cities_copy.citiesTable) {
                                            Vertex<string> *check_incoming = pipes_copy.pipes_copy.findVertex(b.getCode());
                                            double flow = 0;
                                            for (auto c: check_incoming->getIncoming()) {
                                                flow = flow + c->getFlow();
                                            }
                                            //cout<<b.getCode()<<"  - "<<flow<<" / "<<b.getDemand()<<endl;

                                            if(flow == 0){
                                                has_water = true;
                                                break;
                                            }

                                        }

                                        if(has_water && print){
                                          print = false;
                                          cout<<"Pumping Stations: "<<endl;
                                          cout<<a.getCode()<<endl;
                                        }
                                        else if(has_water){
                                          cout<<a.getCode()<<endl;
                                        }

                                        for (auto v: pipes_copy.pipes_copy.getVertexSet()) {
                                            for (auto e: v->getAdj()) {
                                                pipes_copy.pipes_copy.removeEdge(v->getInfo(), e->getDest()->getInfo());
                                            }
                                            pipes_copy.pipes_copy.removeVertex(v->getInfo());
                                        }

                                    }
                                    break;
                                }
                                case 2:{
                                    string code;
                                    cout << "Select a pumping station to be removed:";
                                    cin >> code;
                                    Pipes pipes_copy;
                                    HashStations stations_copy;
                                    HashCities cities_copy;
                                    HashReservoirs reservoirs_copy;
                                    stations_copy.readLines(pipes_copy, chs_fl);
                                    cities_copy.readLines(pipes_copy, chs_fl);
                                    reservoirs_copy.readLines(pipes_copy, chs_fl);
                                    for (auto a: stations_copy.stationsTable) {
                                        if (a.getCode() == code) {
                                            pipes_copy.ReadLines_copy(reservoirs_copy, cities_copy, stations_copy, a, chs_fl);
                                            pipes_copy.pipes_copy.addVertex("super_source");
                                            pipes_copy.pipes_copy.addVertex("super_sink");
                                            Vertex<string> *super_source_copy = pipes_copy.pipes_copy.findVertex(
                                                    "super_source");
                                            Vertex<string> *super_sink_copy = pipes_copy.pipes_copy.findVertex("super_sink");

                                            for (auto j: reservoirs_copy.reservoirsTable) {
                                                Vertex<string> *add = pipes_copy.pipes_copy.findVertex(j.getCode());
                                                pipes_copy.pipes_copy.addEdge(super_source_copy->getInfo(), add->getInfo(),
                                                                              j.getMaxDel());
                                            }
                                            for (auto k: cities_copy.citiesTable) {
                                                Vertex<string> *add = pipes_copy.pipes_copy.findVertex(k.getCode());
                                                pipes_copy.pipes_copy.addEdge(add->getInfo(), super_sink_copy->getInfo(),
                                                                              k.getDemand());
                                            }

                                            pipes_copy.edmondsKarp(super_source_copy->getInfo(), super_sink_copy->getInfo(),
                                                                   pipes_copy.pipes_copy);

                                            cout << "City - flow / Demand" << endl;
                                            for (auto b: cities_copy.citiesTable) {
                                                Vertex<string> *check_incoming = pipes_copy.pipes_copy.findVertex(b.getCode());
                                                double flow = 0;
                                                for (auto c: check_incoming->getIncoming()) {
                                                    flow = flow + c->getFlow();
                                                }
                                                cout << b.getCode() << "  - " << flow << " / " << b.getDemand();
                                                if (flow < b.getDemand()) {
                                                    double deficit = b.getDemand() - flow;
                                                    cout << "   (deficit of " << deficit << ")";
                                                }
                                                cout << endl;
                                            }

                                            cout << endl;
                                            for (auto v: pipes_copy.pipes_copy.getVertexSet()) {
                                                for (auto e: v->getAdj()) {
                                                    pipes_copy.pipes_copy.removeEdge(v->getInfo(), e->getDest()->getInfo());
                                                }
                                                pipes_copy.pipes_copy.removeVertex(v->getInfo());
                                            }
                                        }
                                    }
                                    break;
                                }
                                default:

                                break;
                            }

                        }
                            break;
                        case 3:
                            pipes.OneCity(super_source->getInfo(),super_sink->getInfo(),pipes.pipes,hashCities, hashReservoirs,chs_fl);
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