//
// Created by loading on 05-03-2024.
//
#include <fstream>
#include <sstream>
#include <vector>
#include "pipes.h"
using namespace std;
void Pipes::ReadLines(HashReservoirs hashReservoirs,HashCities hashCities, HashStations hashStations, int decision) {

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
bool Pipes:: findAugmentingPath( Vertex<string> *s, Vertex<string> *t, Graph<string> pipe) {
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

void Pipes:: edmondsKarp(string source, string target, Graph<string> pipe) {
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

void Pipes::ReadLines_copy(HashReservoirs hashReservoirs,HashCities hashCities, HashStations hashStations, Stations station, int decision) {
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


void Pipes::ReadLines_copy_edgeless(HashReservoirs hashReservoirs,HashCities hashCities, HashStations hashStations, int decision, pair<string,string> pp) {
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


bool Pipes::check_existing_edge(string origin, string destiny, vector<pair<string,string>> rawr){
    for(auto a : rawr)
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
void Pipes::OneCity(string source, string target, Graph<string> pipe,HashCities citii, HashReservoirs reserr, int chs_fl) {
    Pipes pipes_copy;
    HashStations stations_copy;
    HashCities cities_copy;
    HashReservoirs reservoirs_copy;
    vector<pair<string,string>> pipes_vector;

    for (auto j: reserr.reservoirsTable) {
        Vertex<string> *add = pipe.findVertex(j.getCode());
        pipe.addEdge(pipe.findVertex("super_source")->getInfo(), add->getInfo(),j.getMaxDel());
    }


    for (auto k: citii.citiesTable) {
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



    for (auto a: pipes_vector) {
        bool print = true;
        stations_copy.readLines(pipes_copy, chs_fl);
        cities_copy.readLines(pipes_copy, chs_fl);
        reservoirs_copy.readLines(pipes_copy, chs_fl);
        pipes_copy.ReadLines_copy_edgeless(reservoirs_copy, cities_copy, stations_copy, chs_fl,a);
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

        for (auto b: cities_copy.citiesTable) {
            Vertex<string> *check_incoming = pipes_copy.pipes_copy.findVertex(b.getCode());
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
                if(print){
                    cout<<"The removal of the edge: "<<a.first<<" to "<<a.second<< " affects the following cities: "<< endl;
                    print = false;
                }

              cout << b.getName() << "  |  " << b.getCode() << "  |  " << "flow: "<<flow << "  |  with the following difference from the original flow: "
                                                           << flow_original - flow << " and deficit of: "<< b.getDemand()-flow << endl;
            }

        }

        if(!print) cout << endl << endl;

        for (auto v: pipes_copy.pipes_copy.getVertexSet()) {
            for (auto e: v->getAdj()) {
                pipes_copy.pipes_copy.removeEdge(v->getInfo(), e->getDest()->getInfo());
            }
            pipes_copy.pipes_copy.removeVertex(v->getInfo());
        }

    }


}

