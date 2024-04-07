#include <fstream>
#include <sstream>
#include <vector>
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
                    cout << "The city " << b.getCode() << " is affected by the following pipes: " << endl << a.first
                         << "-" << a.second << "  with a deficit of " << b.getDemand() - flow << "and diff of"
                         << flow_original - flow << endl;
                    print = false;
                } else {
                    cout << a.first << "-" << a.second << "  with a deficit of " << b.getDemand() - flow << "and diff of"
                         << flow_original - flow << endl;

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
    cout << "Unbalanced Metrics:" << endl;
    }
    else
    {
        cout << endl << endl << "Balanced Metrics"<< endl;
    }
    cout << "Average Difference: " << averageDifference << endl;
    cout << "Variance: " << variance << endl;
    cout << "Maximum Difference: " << maxDifference << endl;
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