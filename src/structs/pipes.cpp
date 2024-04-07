#include <fstream>
#include <sstream>
#include <vector>
#include <climits>
#include "pipes.h"

using namespace std;

void Pipes::ReadLines(int decision) {

    string input;

    if (decision == 1) {
        input = "../data/Pipes.csv";
    } else {
        input = "../data/Pipes_Madeira.csv";
    }

    ifstream MyReadFile(input);

    string line;
    string sa;
    string sb;
    string cap;
    string dir;
    getline(MyReadFile, line);
    while (std::getline(MyReadFile, line)) {
        stringstream ss(line);
        getline(ss, sa, ',');
        getline(ss, sb, ',');
        getline(ss, cap, ',');
        getline(ss, dir, '\r');

        if(dir == "1")
        {
            pipes.addEdge(sa,sb,stod(cap));
        }
        else
        {
            pipes.addBidirectionalEdge(sa,sb,stod(cap));
        }
    }
    }




// Function to test the given vertex 'w' and visit it if conditions are met
void Pipes:: testAndVisit(std::queue< Vertex<string>*> &q, Edge<string> *e, Vertex<string> *w, double residual) {
// Check if the vertex 'w' is not visited and there is residual capacity
    if (! w->isVisited() && residual > 0) {
// Mark 'w' as visited, set the path through which it was reached, and enqueue it
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}





// Function to find an augmenting path using Breadth-First Search
bool Pipes:: findAugmentingPath( Vertex<string> *s, Vertex<string> *t, const Graph<string>& pipe) {
// Mark all vertices as not visited
    for(auto v : pipe.getVertexSet()) {
        v->setVisited(false);
    }
// Mark the source vertex as visited and enqueue it
    s->setVisited(true);
    std::queue<Vertex<string> *> q;
    q.push(s);
// BFS to find an augmenting path
    while( ! q.empty() && ! t->isVisited()) {
        auto v = q.front();
        q.pop();
// Process outgoing edges
        for(auto e: v->getAdj()) {
            testAndVisit(q, e, e->getDest(), e->getWeight() - e->getFlow());
        }
// Process incoming edges
        for(auto e: v->getIncoming()) {
            testAndVisit(q, e, e->getOrig(), e->getFlow());
        }
    }
// Return true if a path to the target is found, false otherwise
    return t->isVisited();
}


// Function to find the minimum residual capacity along the augmenting path
double Pipes:: findMinResidualAlongPath(Vertex<string> *s, Vertex<string> *t) {
    double f = INF;

// Traverse the augmenting path to find the minimum residual capacity
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            f = std::min(f, e->getWeight() - e->getFlow());
            v = e->getOrig();
        }
        else {
            f = std::min(f, e->getFlow());
            v = e->getDest();
        }
    }
// Return the minimum residual capacity
    return f;
}


// Function to augment flow along the augmenting path with the given flow value
void Pipes::augmentFlowAlongPath(Vertex<string> *s, Vertex<string> *t, double f) {
// Traverse the augmenting path and update the flow values accordingly
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        double flow = e->getFlow();
        if (e->getDest() == v) {
            e->setFlow(flow + f);
            v = e->getOrig();
        }
        else {
            e->setFlow(flow - f);
            v = e->getDest();
        }
    }
}

// Main function implementing the Edmonds-Karp algorithm

void Pipes:: edmondsKarp(const string& source, const string& target, const Graph<string>& pipe) {
    Vertex<string>* s = pipe.findVertex(source);
    Vertex<string>* t = pipe.findVertex(target);
// Initialize flow on all edges to 0
    for (auto v : pipe.getVertexSet()) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }
// While there is an augmenting path, augment the flow along the path
    while( findAugmentingPath(s, t, pipe) ) {
        double f = findMinResidualAlongPath(s, t);
        augmentFlowAlongPath(s, t, f);
    }
}

void Pipes::ReadLines_copy_reservoirs(const Reservoirs& reservoir, int decision) {
    string input;

    if (decision == 1) {
        input = "../data/Pipes.csv";
    } else {
        input = "../data/Pipes_Madeira.csv";
    }

    ifstream MyReadFile(input);

    string line;
    string sa;
    string sb;
    string cap;
    string dir;
    getline(MyReadFile, line);
    while (std::getline(MyReadFile, line)) {
        stringstream ss(line);
        getline(ss, sa, ',');
        getline(ss, sb, ',');
        getline(ss, cap, ',');
        getline(ss, dir, '\r');
        if (!(sa == reservoir.getCode() || sb == reservoir.getCode())) {
            if (dir == "1") {
                pipes_copy.addEdge(sa, sb, stod(cap));
            } else {
                pipes_copy.addBidirectionalEdge(sa, sb, stod(cap));
            }

        }
    }
}

void Pipes::ReadLines_copy_station(const Stations& station, int decision) {
    string input;

    if (decision == 1) {
        input = "../data/Pipes.csv";
    } else {
        input = "../data/Pipes_Madeira.csv";
    }

    ifstream MyReadFile(input);

    string line;
    string sa;
    string sb;
    string cap;
    string dir;
    getline(MyReadFile, line);
    while (std::getline(MyReadFile, line)) {
        stringstream ss(line);
        getline(ss, sa, ',');
        getline(ss, sb, ',');
        getline(ss, cap, ',');
        getline(ss, dir, '\r');
        if (!(sa == station.getCode() || sb == station.getCode())) {
            if (dir == "1") {
                pipes_copy.addEdge(sa, sb, stod(cap));
            } else {
                pipes_copy.addBidirectionalEdge(sa, sb, stod(cap));
            }

        }
    }
}



void Pipes::ReadLines_copy_edgeless(int decision, const pair<string,string>& pp) {
    string input;

    if (decision == 1) {
        input = "../data/Pipes.csv";
    } else {
        input = "../data/Pipes_Madeira.csv";
    }

    ifstream MyReadFile(input);

    string line;
    string sa;
    string sb;
    string cap;
    string dir;
    getline(MyReadFile, line);
    while (std::getline(MyReadFile, line)) {
        stringstream ss(line);
        getline(ss, sa, ',');
        getline(ss, sb, ',');
        getline(ss, cap, ',');
        getline(ss, dir, '\r');

        if (!((pp.first == sa && pp.second == sb)||(pp.second==sa && pp.first==sb))) {
            if (dir == "1") {
                pipes_copy.addEdge(sa, sb, stod(cap));
            } else {
                pipes_copy.addBidirectionalEdge(sa, sb, stod(cap));
            }

        }
    }
}


bool Pipes::check_existing_edge(const string& origin, const string& destiny, const vector<pair<string,string>>& rawr){
    for(const auto& a : rawr)
    {
        if(a.first == origin && a.second==destiny)
        {
            return  false;
        }
        if(a.second == origin && a.first == destiny)
        {
            return  false;
        }
    }


    return true;
}


//pepe is a maxflow struct
void Pipes::AllPipes(Graph<string> pipe,const HashCities& citii, const HashReservoirs& reserr, int chs_fl) {
    Pipes pipes_copy2;
    HashStations stations_copy;
    HashCities cities_copy;
    HashReservoirs reservoirs_copy;
    vector<pair<string,string>> pipes_vector;

    for (const auto& j: reserr.reservoirsTable) {
        Vertex<string> *add = pipe.findVertex(j.getCode());
        pipe.addEdge(pipe.findVertex("super_source")->getInfo(), add->getInfo(),j.getMaxDel());
    }


    for (const auto& k: citii.citiesTable) {
        Vertex<string> *add = pipe.findVertex(k.getCode());
        pipe.addEdge(add->getInfo(), pipe.findVertex("super_sink")->getInfo(),k.getDemand());
    }



    edmondsKarp(pipe.findVertex("super_source")->getInfo(), pipe.findVertex("super_sink")->getInfo(),pipe);

    //this cycle checks if an edge is already in the vector -> only adds if it is not
    for(auto a: pipe.getVertexSet()){
        for(auto b: a->getAdj())
        {
            if(check_existing_edge(b->getOrig()->getInfo(), b->getDest()->getInfo(),pipes_vector)) {
                pair<string, string> op = make_pair(b->getOrig()->getInfo(), b->getDest()->getInfo());
                pipes_vector.push_back(op);
            }
        }
    }



    for (const auto& a: pipes_vector) {
        bool print = true;
        stations_copy.readLines(pipes_copy2, chs_fl);
        cities_copy.readLines(pipes_copy2, chs_fl);
        reservoirs_copy.readLines(pipes_copy2, chs_fl);
        pipes_copy2.ReadLines_copy_edgeless(chs_fl,a);
        pipes_copy2.pipes_copy.addVertex("super_source");
        pipes_copy2.pipes_copy.addVertex("super_sink");
        Vertex<string> *super_source_copy = pipes_copy2.pipes_copy.findVertex("super_source");
        Vertex<string> *super_sink_copy = pipes_copy2.pipes_copy.findVertex("super_sink");


        for (const auto& j: reservoirs_copy.reservoirsTable) {
            Vertex<string> *add = pipes_copy2.pipes_copy.findVertex(j.getCode());
            pipes_copy2.pipes_copy.addEdge(super_source_copy->getInfo(), add->getInfo(),j.getMaxDel());
        }


        for (const auto& k: cities_copy.citiesTable) {
            Vertex<string> *add = pipes_copy2.pipes_copy.findVertex(k.getCode());
            pipes_copy2.pipes_copy.addEdge(add->getInfo(), super_sink_copy->getInfo(),k.getDemand());
        }



        Pipes::edmondsKarp(super_source_copy->getInfo(), super_sink_copy->getInfo(),pipes_copy2.pipes_copy);

        for (const auto& b: cities_copy.citiesTable) {
            Vertex<string> *check_incoming = pipes_copy2.pipes_copy.findVertex(b.getCode());
            double flow = 0;
            for (auto c: check_incoming->getIncoming()) {
                flow = flow + c->getFlow();
            }


            Vertex<string> *check_incoming_original =pipe.findVertex(b.getCode());
            double flow_original = 0;
            for (auto c: check_incoming_original->getIncoming()) {
                flow_original = flow_original + c->getFlow();
            }

            if(flow != flow_original && flow < b.getDemand()){
                if (print) {

                    cout << "\033[0;32m ⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯ \033[0m" << endl;
                    cout << "\033[0;32m│⎯\033[0m" << "\033[1;33mRemoving\033[0m" << "\033[0;32m⎯\033[0m" << "\033[1;33medge\033[0m" << "\033[0;32m⎯\033[0m" << "\033[1;33mfrom\033[0m" << "\033[0;32m⎯⎯\033[0m" << a.first << "\033[0;32m⎯⎯\033[0m" << "\033[1;33mto\033[0m" << "\033[0;32m⎯⎯\033[0m" << a.second;
                    for (auto i = (11 - (a.first.length() + a.second.length())); i > 0; i--) {
                        cout << "\033[0;32m⎯\033[0m";
                    }
                    cout << "\033[0;32m│⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯\033[0m" << endl;

                    cout << "\033[0;32m│⎯\033[0m" << "\033[1;33mAffected\033[0m" << "\033[0;32m⎯\033[0m" << "\033[1;33mCities\033[0m" << "\033[0;32m⎯⎯⎯⎯⎯│⎯\033[0m" << "\033[1;33mCode\033[0m" << "\033[0;32m⎯⎯│⎯\033[0m" << "\033[1;33mFlow\033[0m" << "\033[0;32m⎯⎯⎯│⎯\033[0m" << "\033[1;33mVariation\033[0m" << "\033[0;32m⎯\033[0m" << "\033[1;33mof\033[0m" << "\033[0;32m⎯\033[0m" << "\033[1;33mflow\033[0m" << "\033[0;32m⎯⎯│⎯\033[0m" << "\033[1;33mDeficit\033[0m" << "\033[0;32m⎯⎯│ \033[0m" << endl;

                    print = false;
                }

                int checker = 0;
                for (int i = 0; i < b.getName().length(); i++) {
                    if ((b.getName()[i] > 122 || b.getName()[i] < 65) && b.getName()[i] != 32) {
                        checker++;
                    }
                }
                checker /= 2;

                cout << "\033[0;32m│⎯\033[0m" << b.getName();
                for (auto i = ((20 - b.getName().length()) + checker); i > 0; i--) {
                    cout << "\033[0;32m⎯\033[0m";
                }
                cout << "\033[0;32m│⎯\033[0m" << b.getCode();
                for (auto i = (6 - b.getCode().length()); i > 0; i--) {
                    cout << "\033[0;32m⎯\033[0m";
                }
                cout << "\033[0;32m│⎯\033[0m" << flow;
                for (auto i = (14 - to_string(flow).length()); i > 0; i--) {
                    cout << "\033[0;32m⎯\033[0m";
                }
                cout << "\033[0;32m│⎯\033[0m" << (flow_original - flow);
                for (auto i = (26 - to_string(flow_original - flow).length()); i > 0; i--) {
                    cout << "\033[0;32m⎯\033[0m";
                }
                cout << "\033[0;32m│⎯\033[0m" << (b.getDemand() - flow);
                for (auto i = (16 - to_string(b.getDemand() - flow).length()); i > 0; i--) {
                    cout << "\033[0;32m⎯\033[0m";
                }
                cout << "\033[0;32m│\033[0m" << endl;
            }

        }

        if(!print) cout << endl << endl;

        for (auto v: pipes_copy2.pipes_copy.getVertexSet()) {
            for (auto e: v->getAdj()) {
                pipes_copy2.pipes_copy.removeEdge(v->getInfo(), e->getDest()->getInfo());
            }
            pipes_copy2.pipes_copy.removeVertex(v->getInfo());
        }

    }


}

void Pipes::Max_flow_specific_city(Vertex<string> * super_source, Vertex<string> * super_sink, Graph<string> pipes, HashCities hashCities, HashReservoirs hashReservoirs, string input) {

    string city_name;
    string city_code;
    double city_demand;
    double res = 0;
    for (const auto& a: hashReservoirs.reservoirsTable) {
        Vertex<string> *add = pipes.findVertex(a.getCode());
        pipes.addEdge(super_source->getInfo(), add->getInfo(), a.getMaxDel());
    }
    for (const auto& a: hashCities.citiesTable) {
        Vertex<string> *add = pipes.findVertex(a.getCode());
        pipes.addEdge(add->getInfo(), super_sink->getInfo(), a.getDemand());
    }
    edmondsKarp(super_source->getInfo(), super_sink->getInfo(), pipes);
    Cities save;
    for (const auto& a: hashCities.citiesTable) {
        if (a.getCode() == input) {
            city_name = a.getName();
            city_code = a.getCode();
            city_demand = a.getDemand();
            save = a;
            Vertex<string> *check_flow = pipes.findVertex(a.getCode());
            for (auto b: check_flow->getIncoming()) {
                res = res + b->getFlow();
            }
        }
    }

    cout << "\033[0;32m ⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯ ⎯⎯⎯⎯⎯⎯⎯ ⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯ ⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯ \033[0m"
         << endl;
    cout << "\033[0;32m│⎯\033[0m" << "\033[1;33mCity\033[0m"
         << "\033[0;32m⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯│⎯\033[0m" << "\033[1;33mCode\033[0m"
         << "\033[0;32m⎯⎯│⎯\033[0m" << "\033[1;33mMaximum\033[0m" << "\033[0;32m⎯\033[0m"
         << "\033[1;33mFlow\033[0m" << "\033[0;32m⎯│⎯\033[0m";

    if ((res - city_demand) > 0) {
        cout << "\033[1;33mOverflow\033[0m" << "\033[0;32m⎯│\033[0m" << endl;
    } else {
        cout << "\033[1;33mDeficit\033[0m" << "\033[0;32m⎯⎯│\033[0m" << endl;
    }


    int checker = 0;
    for (int i = 0; i < city_name.length(); i++) {
        if ((city_name[i] > 122 || city_name[i] < 65) && city_name[i] != 32) {
            checker++;
        }
    }
    checker /= 2;

    cout << "\033[0;32m│⎯\033[0m" << city_name;
    for (auto i = ((20 - city_name.length()) + checker); i > 0; i--) {
        cout << "\033[0;32m⎯\033[0m";
    }
    cout << "\033[0;32m│⎯\033[0m" << city_code;
    for (auto i = (6 - city_code.length()); i > 0; i--) {
        cout << "\033[0;32m⎯\033[0m";
    }
    cout << "\033[0;32m│⎯\033[0m" << res;
    for (auto i = (20 - to_string(res).length()); i > 0; i--) {
        cout << "\033[0;32m⎯\033[0m";
    }
    cout << "\033[0;32m│⎯\033[0m" << city_demand - res;
    if ((res - city_demand) == 0) {
        city_demand++;
    }
    for (auto i = (17 - to_string(res - city_demand).length()); i > 0; i--) {
        cout << "\033[0;32m⎯\033[0m";
    }
    cout << "\033[0;32m│\033[0m" << endl;

    if (res < save.getDemand()) {
        cout << "\033[0;32m│⎯\033[0m" << "\033[1;33mMinimum\033[0m" << "\033[0;32m⎯\033[0m"
             << "\033[1;33mflow\033[0m" << "\033[0;32m⎯\033[0m"
             << "\033[1;33mrequirement\033[0m" << "\033[0;32m⎯\033[0m"
             << "\033[1;33mmet\033[0m" << "\033[0;32m⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯│⎯⎯⎯⎯⎯⎯⎯\033[0m" << "No"
             << "\033[0;32m⎯│\033[0m" << endl << endl << endl;
    } else {
        cout << "\033[0;32m│⎯\033[0m" << "\033[1;33mMinimum\033[0m" << "\033[0;32m⎯\033[0m"
             << "\033[1;33mflow\033[0m" << "\033[0;32m⎯\033[0m"
             << "\033[1;33mrequirement\033[0m" << "\033[0;32m⎯\033[0m"
             << "\033[1;33mmet\033[0m" << "\033[0;32m⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯│⎯⎯⎯⎯⎯⎯\033[0m" << "Yes"
             << "\033[0;32m⎯│\033[0m" << endl << endl << endl;
    }

}

void Pipes::Removing_reservoir(Vertex<string> * super_source, Vertex<string> * super_sink, Graph<string> pipes, HashCities cities, HashReservoirs reservoirs, string input, vector<string> not_full, int chs_fl, HashCities cities_copy, HashReservoirs reservoirs_copy, HashStations stations_copy, Pipes pipes_copy) {
    for (const auto &a: reservoirs.reservoirsTable) {
        Vertex<string> *add = pipes.findVertex(a.getCode());
        pipes.addEdge(super_source->getInfo(), add->getInfo(), a.getMaxDel());
    }

    for (const auto &a: cities.citiesTable) {
        Vertex<string> *add = pipes.findVertex(a.getCode());
        pipes.addEdge(add->getInfo(), super_sink->getInfo(), a.getDemand());
    }
    Pipes::edmondsKarp(super_source->getInfo(), super_sink->getInfo(), pipes);

    cout << "\033[1;34mWhich water reservoir? \033[0m";
    cin >> input;
    cout << endl;

    stations_copy.readLines(pipes_copy, chs_fl);
    cities_copy.readLines(pipes_copy, chs_fl);
    reservoirs_copy.readLines(pipes_copy, chs_fl);
    for (const auto& a: reservoirs_copy.reservoirsTable) {
        if (a.getCode() == input) {
            pipes_copy.ReadLines_copy_reservoirs(a, chs_fl);
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

            pipes_copy.edmondsKarp(super_source_copy->getInfo(), super_sink_copy->getInfo(),
                                   pipes_copy.pipes_copy);

            cout << "\033[0;32m ⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯ ⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯ \033[0m" << endl;
            cout << "\033[0;32m│⎯\033[0m" << "\033[1;33mWater\033[0m" << "\033[0;32m⎯\033[0m" << "\033[1;33mreservoir\033[0m" << "\033[0;32m⎯\033[0m" << "\033[1;33mremoved\033[0m" << "\033[0;32m⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯│⎯\033[0m" << a.getCode();
            for (auto i = (25 - a.getCode().length()); i > 0; i--) {
                cout << "\033[0;32m⎯\033[0m";
            }
            cout << "\033[0;32m│\033[0m" << endl;

            cout << "\033[0;32m│⎯\033[0m" << "\033[1;33mCode\033[0m" << "\033[0;32m⎯⎯⎯│⎯\033[0m" << "\033[1;33mOld\033[0m" << "\033[0;32m⎯\033[0m" << "\033[1;33mflow\033[0m" << "\033[0;32m⎯⎯⎯⎯│⎯\033[0m" << "\033[1;33mNew\033[0m" << "\033[0;32m⎯\033[0m" << "\033[1;33mflow\033[0m" << "\033[0;32m⎯⎯⎯⎯│⎯\033[0m"  << "\033[1;33mDemand\033[0m" << "\033[0;32m⎯⎯⎯│⎯\033[0m" << "\033[1;33mNew\033[0m" << "\033[0;32m⎯\033[0m" << "\033[1;33mdeficit\033[0m" << "\033[0;32m⎯⎯⎯│\033[0m" << endl;

            for (const auto &b: cities_copy.citiesTable) {
                Vertex<string> *check_incoming_new = pipes_copy.pipes_copy.findVertex(
                        b.getCode());
                Vertex<string> *check_incoming_old = pipes.findVertex(b.getCode());

                double flow_new = 0;
                double flow_old = 0;
                for (auto c: check_incoming_new->getIncoming()) {
                    flow_new = flow_new + c->getFlow();
                }
                for (auto c: check_incoming_old->getIncoming()) {
                    flow_old = flow_old + c->getFlow();
                }


                if (flow_old != flow_new) {
                    cout << "\033[0;32m│⎯\033[0m" << b.getCode();
                    for (auto i = (7 - b.getCode().length()); i > 0; i--) {
                        cout << "\033[0;32m⎯\033[0m";
                    }
                    cout << "\033[0;32m│⎯\033[0m" << flow_old;
                    for (auto i = (19 - to_string(flow_old).length()); i > 0; i--) {
                        cout << "\033[0;32m⎯\033[0m";
                    }
                    cout << "\033[0;32m│⎯\033[0m" << flow_new;
                    for (auto i = (19 - to_string(flow_new).length()); i > 0; i--) {
                        cout << "\033[0;32m⎯\033[0m";
                    }
                    cout << "\033[0;32m│⎯\033[0m" << b.getDemand();
                    for (auto i = (9 - to_string((int)b.getDemand()).length()); i > 0; i--) {
                        cout << "\033[0;32m⎯\033[0m";
                    }

                    if (flow_new < b.getDemand()) {
                        double deficit = b.getDemand() - flow_new;

                        cout << "\033[0;32m│⎯\033[0m" << deficit;
                        for (auto i = (21 - to_string(deficit).length()); i > 0; i--) {
                            cout << "\033[0;32m⎯\033[0m";
                        }
                        cout << "\033[0;32m│\033[0m";

                    } else {
                        cout << "\033[0;32m│⎯\033[0m" << "None" << "\033[0;32m⎯⎯⎯⎯⎯⎯│\033[0m";
                    }
                    cout<<endl;
                }

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
}


void Pipes:: OneCity(Graph<string>pipe,const HashCities& citii, const HashReservoirs& reserr, int chs_fl, string cit) {
    Pipes pipes_copy2;
    HashStations stations_copy;
    HashCities cities_copy;
    HashReservoirs reservoirs_copy;
    vector<pair<string, string>> pipes_vector;
    bool print = true;

    for (const auto &j: reserr.reservoirsTable) {
        Vertex<string> *add = pipe.findVertex(j.getCode());
        pipe.addEdge(pipe.findVertex("super_source")->getInfo(), add->getInfo(), j.getMaxDel());
    }


    for (const auto &k: citii.citiesTable) {
        Vertex<string> *add = pipe.findVertex(k.getCode());
        pipe.addEdge(add->getInfo(), pipe.findVertex("super_sink")->getInfo(), k.getDemand());
    }


    edmondsKarp(pipe.findVertex("super_source")->getInfo(), pipe.findVertex("super_sink")->getInfo(), pipe);

    //this cycle checks if an edge is already in the vector -> only adds if it is not
    for (auto a: pipe.getVertexSet()) {
        for (auto b: a->getAdj()) {
            if (check_existing_edge(b->getOrig()->getInfo(), b->getDest()->getInfo(), pipes_vector)) {
                pair<string, string> op = make_pair(b->getOrig()->getInfo(), b->getDest()->getInfo());
                pipes_vector.push_back(op);
            }
        }
    }

    cout << "\033[0;32m ⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯ ⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯ \033[0m" << endl;
    cout << "\033[0;32m│⎯\033[0m" << "\033[1;33mCity\033[0m" << "\033[0;32m⎯⎯⎯⎯⎯│⎯\033[0m" << cit;
    for (auto i = (46 - cit.length()); i > 0; i--) {
        cout << "\033[0;32m⎯\033[0m";
    }
    cout << "\033[0;32m│\033[0m" << endl;

    cout << "\033[0;32m│⎯\033[0m" << "\033[1;33mOrigin\033[0m" << "\033[0;32m⎯⎯⎯│⎯\033[0m" << "\033[1;33mDestination\033[0m" << "\033[0;32m⎯⎯⎯│⎯\033[0m" << "\033[1;33mDeficit\033[0m" << "\033[0;32m⎯⎯⎯⎯│⎯\033[0m" << "\033[1;33mFlow\033[0m" << "\033[0;32m⎯\033[0m" << "\033[1;33mvariation\033[0m" << "\033[0;32m⎯⎯⎯│\033[0m" << endl;

    for (const auto &a: pipes_vector) {
        stations_copy.readLines(pipes_copy2, chs_fl);
        cities_copy.readLines(pipes_copy2, chs_fl);
        reservoirs_copy.readLines(pipes_copy2, chs_fl);
        pipes_copy2.ReadLines_copy_edgeless(chs_fl, a);
        pipes_copy2.pipes_copy.addVertex("super_source");
        pipes_copy2.pipes_copy.addVertex("super_sink");
        Vertex<string> *super_source_copy = pipes_copy2.pipes_copy.findVertex("super_source");
        Vertex<string> *super_sink_copy = pipes_copy2.pipes_copy.findVertex("super_sink");


        for (const auto &j: reservoirs_copy.reservoirsTable) {
            Vertex<string> *add = pipes_copy2.pipes_copy.findVertex(j.getCode());
            pipes_copy2.pipes_copy.addEdge(super_source_copy->getInfo(), add->getInfo(), j.getMaxDel());
        }


        for (const auto &k: cities_copy.citiesTable) {
            Vertex<string> *add = pipes_copy2.pipes_copy.findVertex(k.getCode());
            pipes_copy2.pipes_copy.addEdge(add->getInfo(), super_sink_copy->getInfo(), k.getDemand());
        }


        Pipes::edmondsKarp(super_source_copy->getInfo(), super_sink_copy->getInfo(), pipes_copy2.pipes_copy);

        for (const auto &b: cities_copy.citiesTable) {
            if(!(b.getCode()==citii.findCity(cit)->getCode())) continue;
            Vertex<string> *check_incoming = pipes_copy2.pipes_copy.findVertex(b.getCode());
            double flow = 0;
            for (auto c: check_incoming->getIncoming()) {
                flow = flow + c->getFlow();
            }


            Vertex<string> *check_incoming_original = pipe.findVertex(b.getCode());
            double flow_original = 0;
            for (auto c: check_incoming_original->getIncoming()) {
                flow_original = flow_original + c->getFlow();
            }



            if ( flow != flow_original && flow < b.getDemand()) {
                if (print) {

                    cout << "\033[0;32m│⎯\033[0m" << a.first;
                    for (auto i = (9 - a.first.length()); i > 0; i--) {
                        cout << "\033[0;32m⎯\033[0m";
                    }
                    cout << "\033[0;32m│⎯\033[0m" << a.second;
                    for (auto i = (14 - a.second.length()); i > 0; i--) {
                        cout << "\033[0;32m⎯\033[0m";
                    }
                    cout << "\033[0;32m│⎯\033[0m" << b.getDemand() - flow;
                    for (auto i = (18 - to_string(b.getDemand() - flow).length()); i > 0; i--) {
                        cout << "\033[0;32m⎯\033[0m";
                    }
                    cout << "\033[0;32m│⎯\033[0m" << flow_original - flow;
                    for (auto i = (24 - to_string(flow_original - flow).length()); i > 0; i--) {
                        cout << "\033[0;32m⎯\033[0m";
                    }
                    cout << "\033[0;32m│\033[0m" << endl;

                    print = false;
                } else {

                    cout << "\033[0;32m│⎯\033[0m" << a.first;
                    for (auto i = (9 - a.first.length()); i > 0; i--) {
                        cout << "\033[0;32m⎯\033[0m";
                    }
                    cout << "\033[0;32m│⎯\033[0m" << a.second;
                    for (auto i = (14 - a.second.length()); i > 0; i--) {
                        cout << "\033[0;32m⎯\033[0m";
                    }
                    cout << "\033[0;32m│⎯\033[0m" << b.getDemand() - flow;
                    for (auto i = (18 - to_string(b.getDemand() - flow).length()); i > 0; i--) {
                        cout << "\033[0;32m⎯\033[0m";
                    }
                    cout << "\033[0;32m│⎯\033[0m" << flow_original - flow;
                    for (auto i = (24 - to_string(flow_original - flow).length()); i > 0; i--) {
                        cout << "\033[0;32m⎯\033[0m";
                    }
                    cout << "\033[0;32m│\033[0m" << endl;

                }
            }
        }


        for (auto v: pipes_copy2.pipes_copy.getVertexSet()) {
            for (auto e: v->getAdj()) {
                pipes_copy2.pipes_copy.removeEdge(v->getInfo(), e->getDest()->getInfo());
            }
            pipes_copy2.pipes_copy.removeVertex(v->getInfo());
        }
    }
    cout << endl << endl;
}




void Pipes::Max_flow_non_specific_city_without_overflow(Vertex<string> * super_source, Vertex<string> * super_sink, Graph<string> pipes, HashCities hashCities, HashReservoirs hashReservoirs, string input, vector<string> not_full, vector<max_flow_info> pipi) {
    for (const auto& a: hashReservoirs.reservoirsTable) {
        Vertex<string> *add = pipes.findVertex(a.getCode());
        pipes.addEdge(super_source->getInfo(), add->getInfo(), a.getMaxDel());
    }

    for (const auto& a: hashCities.citiesTable) {
        Vertex<string> *add = pipes.findVertex(a.getCode());
        pipes.addEdge(add->getInfo(), super_sink->getInfo(), a.getDemand());
    }
    edmondsKarp(super_source->getInfo(), super_sink->getInfo(), pipes);
    double max_flow = 0;

    cout << "\033[0;32m ⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯ ⎯⎯⎯⎯⎯⎯⎯ ⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯ \033[0m" << endl;
    cout << "\033[0;32m│⎯\033[0m" << "\033[1;33mCity\033[0m"
         << "\033[0;32m⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯│⎯\033[0m" << "\033[1;33mCode\033[0m"
         << "\033[0;32m⎯⎯│⎯\033[0m" << "\033[1;33mMaximum\033[0m"
         << "\033[0;32m⎯\033[0m" << "\033[1;33mFlow\033[0m" << "\033[0;32m⎯│\033[0m"
         << endl;

    for (const auto& a: hashCities.citiesTable) {
        double res = 0;
        Vertex<string> *check_flow = pipes.findVertex(a.getCode());
        for (auto b: check_flow->getIncoming()) {
            res = res + b->getFlow();
        }
        max_flow = max_flow + res;

        int checker = 0;
        for (int i = 0; i < a.getName().length(); i++) {
            if ((a.getName()[i] > 122 || a.getName()[i] < 65) && a.getName()[i] != 32) {
                checker++;
            }
        }
        checker /= 2;

        cout << "\033[0;32m│⎯\033[0m" << a.getName();
        for (auto i = ((20 - a.getName().length()) + checker); i > 0; i--) {
            cout << "\033[0;32m⎯\033[0m";
        }
        cout << "\033[0;32m│⎯\033[0m" << a.getCode();
        for (auto i = (6 - a.getCode().length()); i > 0; i--) {
            cout << "\033[0;32m⎯\033[0m";
        }
        cout << "\033[0;32m│⎯\033[0m" << res;
        for (auto i = (20 - to_string(res).length()); i > 0; i--) {
            cout << "\033[0;32m⎯\033[0m";
        }
        cout << "\033[0;32m│\033[0m" << endl;

        Pipes::max_flow_info m;
        m.city_name = a.getName();
        m.city_code = a.getCode();
        pipi.push_back(m);

        const Cities *d = hashCities.findCity(a.getCode());
        if (res < d->getDemand()) {
            not_full.push_back(a.getName());
            not_full.push_back(a.getCode());
            double missing = (d->getDemand()) - res;
            not_full.push_back(to_string(missing));
        }

    }


    cout << "\033[0;32m│⎯\033[0m" << "\033[1;33mMaximum\033[0m" << "\033[0;32m⎯\033[0m"
         << "\033[1;33mtotal\033[0m" << "\033[0;32m⎯\033[0m" << "\033[1;33mflow\033[0m"
         << "\033[0;32m⎯⎯│⎯\033[0m" << max_flow;
    for (auto i = (28 - to_string(max_flow).length()); i > 0; i--) {
        cout << "\033[0;32m⎯\033[0m";
    }
    cout << "\033[0;32m│\033[0m" << endl << endl;

    cout
            << "\033[1;34mDo you wish to check for any cities where the flow isn't enough? \033[0m"
            << "\033[1;33m [ Y | N ]\033[0m" << endl;
    cin >> input;
    cout << endl;

    if (input == "y" || input == "Y") {

        cout << "\033[0;32m ⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯ ⎯⎯⎯⎯⎯⎯⎯ ⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯ \033[0m"
             << endl;
        cout << "\033[0;32m│⎯\033[0m" << "\033[1;33mCity\033[0m"
             << "\033[0;32m⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯│⎯\033[0m" << "\033[1;33mCode\033[0m"
             << "\033[0;32m⎯⎯│⎯\033[0m" << "\033[1;33mFlow\033[0m"
             << "\033[0;32m⎯\033[0m" << "\033[1;33mdeficit\033[0m"
             << "\033[0;32m⎯│\033[0m" << endl;

        for (size_t i = 0; i < not_full.size() - 2; i += 3) {

            int checker = 0;
            for (int j = 0; j < not_full[i].length(); j++) {
                if ((not_full[i][j] > 122 || not_full[i][j] < 65) &&
                    not_full[i][j] != 32) {
                    checker++;
                }
            }
            checker /= 2;

            cout << "\033[0;32m|⎯\033[0m" << not_full[i];
            for (auto j = ((20 - not_full[i].length()) + checker); j > 0; j--) {
                cout << "\033[0;32m⎯\033[0m";
            }
            cout << "\033[0;32m|⎯\033[0m" << not_full[i + 1];
            for (auto j = (6 - not_full[i + 1].length()); j > 0; j--) {
                cout << "\033[0;32m⎯\033[0m";
            }
            cout << "\033[0;32m│⎯\033[0m" << stoi(not_full[i + 2]);
            for (auto j = (20 - not_full[i + 2].length()); j > 0; j--) {
                cout << "\033[0;32m⎯\033[0m";
            }
            cout << "\033[0;32m│\033[0m" << endl;

        }
        cout << endl << endl;

    } else if (input == "n" || input == "N") {
        cout << endl;
    } else {
        cout << "\033[1;31mInput error - Moving on\033[0m" << endl << endl;
    }

    not_full.clear();
}

void Pipes::Max_flow_non_specific_city_with_overflow(Vertex<string> * super_source, Vertex<string> * super_sink, Graph<string> pipes, HashCities hashCities, HashReservoirs hashReservoirs, string input, vector<string> not_full, vector<max_flow_info> pipi) {
    for (const auto& a: hashReservoirs.reservoirsTable) {
        Vertex<string> *add = pipes.findVertex(a.getCode());
        pipes.addEdge(super_source->getInfo(), add->getInfo(), a.getMaxDel());
    }

    for (const auto& a: hashCities.citiesTable) {
        Vertex<string> *add = pipes.findVertex(a.getCode());
        pipes.addEdge(add->getInfo(), super_sink->getInfo(), INT_MAX);
    }
    edmondsKarp(super_source->getInfo(), super_sink->getInfo(), pipes);
    double max_flow = 0;

    cout << "\033[0;32m ⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯ ⎯⎯⎯⎯⎯⎯⎯ ⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯ \033[0m" << endl;
    cout << "\033[0;32m│⎯\033[0m" << "\033[1;33mCity\033[0m"
         << "\033[0;32m⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯│⎯\033[0m" << "\033[1;33mCode\033[0m"
         << "\033[0;32m⎯⎯│⎯\033[0m" << "\033[1;33mMaximum\033[0m"
         << "\033[0;32m⎯\033[0m" << "\033[1;33mFlow\033[0m" << "\033[0;32m⎯│\033[0m"
         << endl;

    for (const auto& a: hashCities.citiesTable) {
        double res = 0;
        Vertex<string> *check_flow = pipes.findVertex(a.getCode());
        for (auto b: check_flow->getIncoming()) {
            res = res + b->getFlow();
        }
        max_flow = max_flow + res;

        int checker = 0;
        for (int i = 0; i < a.getName().length(); i++) {
            if ((a.getName()[i] > 122 || a.getName()[i] < 65) && a.getName()[i] != 32) {
                checker++;
            }
        }
        checker /= 2;

        cout << "\033[0;32m│⎯\033[0m" << a.getName();
        for (auto i = ((20 - a.getName().length()) + checker); i > 0; i--) {
            cout << "\033[0;32m⎯\033[0m";
        }
        cout << "\033[0;32m│⎯\033[0m" << a.getCode();
        for (auto i = (6 - a.getCode().length()); i > 0; i--) {
            cout << "\033[0;32m⎯\033[0m";
        }
        cout << "\033[0;32m│⎯\033[0m" << res;
        for (auto i = (20 - to_string(res).length()); i > 0; i--) {
            cout << "\033[0;32m⎯\033[0m";
        }
        cout << "\033[0;32m│\033[0m" << endl;

        max_flow_info m;
        m.city_name = a.getName();
        m.city_code = a.getCode();
        pipi.push_back(m);

        const Cities *d = hashCities.findCity(a.getCode());
        if (res < d->getDemand()) {
            not_full.push_back(a.getName());
            not_full.push_back(a.getCode());
            double missing = (d->getDemand()) - res;
            not_full.push_back(to_string(missing));
        }

    }

    cout << "\033[0;32m│⎯\033[0m" << "\033[1;33mMaximum\033[0m" << "\033[0;32m⎯\033[0m"
         << "\033[1;33mtotal\033[0m" << "\033[0;32m⎯\033[0m" << "\033[1;33mflow\033[0m"
         << "\033[0;32m⎯⎯│⎯\033[0m" << max_flow;
    for (auto i = (28 - to_string(max_flow).length()); i > 0; i--) {
        cout << "\033[0;32m⎯\033[0m";
    }
    cout << "\033[0;32m│\033[0m" << endl << endl;

    cout
            << "\033[1;34mDo you wish to check for any cities where the flow isn't enough? \033[0m"
            << "\033[1;33m [ Y | N ]\033[0m" << endl;
    cin >> input;
    cout << endl;

    if (input == "y" || input == "Y") {

        cout << "\033[0;32m ⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯ ⎯⎯⎯⎯⎯⎯⎯ ⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯ \033[0m"
             << endl;
        cout << "\033[0;32m│⎯\033[0m" << "\033[1;33mCity\033[0m"
             << "\033[0;32m⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯│⎯\033[0m" << "\033[1;33mCode\033[0m"
             << "\033[0;32m⎯⎯│⎯\033[0m" << "\033[1;33mFlow\033[0m"
             << "\033[0;32m⎯\033[0m" << "\033[1;33mdeficit\033[0m"
             << "\033[0;32m⎯│\033[0m" << endl;

        for (size_t i = 0; i < not_full.size() - 2; i += 3) {

            int checker = 0;
            for (int j = 0; j < not_full[i].length(); j++) {
                if ((not_full[i][j] > 122 || not_full[i][j] < 65) &&
                    not_full[i][j] != 32) {
                    checker++;
                }
            }
            checker /= 2;

            cout << "\033[0;32m│⎯\033[0m" << not_full[i];
            for (auto j = ((20 - not_full[i].length()) + checker); j > 0; j--) {
                cout << "\033[0;32m⎯\033[0m";
            }
            cout << "\033[0;32m│⎯\033[0m" << not_full[i + 1];
            for (auto j = (6 - not_full[i + 1].length()); j > 0; j--) {
                cout << "\033[0;32m⎯\033[0m";
            }
            cout << "\033[0;32m│⎯\033[0m" << stoi(not_full[i + 2]);
            for (auto j = (20 - not_full[i + 2].length()); j > 0; j--) {
                cout << "\033[0;32m⎯\033[0m";
            }
            cout << "\033[0;32m│\033[0m" << endl;

        }
        cout << endl << endl;
    } else if (input == "n" || input == "N") {
        cout << endl;
    } else {
        cout << "\033[1;31mInput error - Moving on\033[0m" << endl << endl;
    }

    not_full.clear();

}


void Pipes:: computeInitialMetrics(const Pipes& pipes2, int whi) {

    double sumDifference = 0;
    double maxDifference = 0;
    double dif = 0;
    int pipe_count =  0;

    for(auto vv : pipes2.pipes.getVertexSet()) {
        for(auto pip: vv->getAdj() )
        dif = pip->getWeight() - pip->getFlow();
        sumDifference +=dif;
        maxDifference = max(maxDifference, dif);
        pipe_count++;
    }
    double averageDifference = sumDifference / pipe_count;

    double sumSquaredDifference = 0;
    dif = 0;

    for(auto vv : pipes2.pipes.getVertexSet()) {
        for(auto pip: vv->getAdj() )
         dif = pip->getWeight() - pip->getFlow();
         sumSquaredDifference += (dif - averageDifference) * (dif - averageDifference);
    }

    double variance = sumSquaredDifference / pipes2.pipes.getVertexSet().size();

    if(whi==0){
        cout << endl << "\033[0;32m ⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯ \033[0m"
             << endl;
        cout << "\033[0;32m│⎯\033[0m" << "\033[1;33mUnbalanced\033[0m"
             << "\033[0;32m⎯\033[0m" << "\033[1;33mmetrics\033[0m" << "\033[0;32m⎯│\033[0m" << endl;

    }
    else
    {
        cout << "\033[0;32m ⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯ \033[0m"
             << endl;
        cout << "\033[0;32m│⎯\033[0m" << "\033[1;33mBalanced\033[0m"
             << "\033[0;32m⎯\033[0m" << "\033[1;33mmetrics\033[0m" << "\033[0;32m⎯⎯⎯│\033[0m" << endl;
    }

    cout << "\033[0;32m│⎯\033[0m" << "\033[1;33mAverage\033[0m" << "\033[0;32m⎯\033[0m" << "\033[1;33mdifference\033[0m" << "\033[0;32m⎯⎯⎯ \033[0m" << averageDifference << endl << "\033[0;32m│⎯\033[0m""\033[1;33mVariance\033[0m" << "\033[0;32m⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯ \033[0m" << variance << endl << "\033[0;32m│⎯\033[0m" << "\033[1;33mMaximum\033[0m" << "\033[0;32m⎯\033[0m" << "\033[1;33mdifference\033[0m" << "\033[0;32m⎯⎯⎯ \033[0m"
    << maxDifference << endl << endl;

}





void Pipes:: balanceLoad(Pipes& pipes2,const HashCities& citii, const HashReservoirs& reserr) {



        double totalFlow = 0;
        double pipe_count = 0;
        for (auto vv: pipes2.pipes.getVertexSet()) {
            for (auto pip: vv->getAdj()) {
                totalFlow += pip->getFlow();
                pipe_count++;
            }
        }

        double averageFlow = totalFlow / pipe_count;

        // Redistribute flow from pipes with higher flow rates to pipes with lower flow rates
        for (auto vv: pipes2.pipes.getVertexSet()) {
            for (auto pip: vv->getAdj()) {

                if (pip->getFlow() > averageFlow) {
                    double excessFlow = pip->getFlow() - averageFlow;


                    for (auto vv2: pipes2.pipes.getVertexSet()) {
                        for (auto pip2: vv2->getAdj()) {
                            if (pip2 != pip && pip2->getFlow() < averageFlow) {
                                double transferFlow = min(excessFlow, averageFlow - pip2->getFlow());
                                pip2->setFlow(pip2->getFlow() + transferFlow);
                                pip->setFlow(pip->getFlow() - transferFlow);
                                excessFlow -= transferFlow;
                                if (excessFlow == 0) {
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }


        computeInitialMetrics(pipes2,1);

    }