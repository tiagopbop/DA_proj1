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
    //pepe is a maxflow struct
void Pipes::OneCity(string source, string target, Graph<string> pipe) {
    edmondsKarp(source,target, pipe);
    for(auto a: pipes.getVertexSet()) {
    }}


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