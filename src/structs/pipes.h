#ifndef DA_PROJECT1_PIPES_H
#define DA_PROJECT1_PIPES_H

#include <unordered_set>
#include <string>
#include "Graph.h"
#include "reservoirs.h"
#include "cities.h"
#include "stations.h"


using namespace std;
class HashStations;
class HashCities;
class HashReservoirs;
class Stations;
class Reservoirs;
class Pipes{
public:
    struct max_flow_info{
        string city_name;
        string city_code;
    };

    Graph<string> pipes;
    Graph<string> pipes_copy;
/**
 * @brief Reads lines from a CSV file containing pipe data and populates the pipes graph.
 *
 * This function reads lines from a CSV file containing pipe data. Each line is parsed to extract
 * information about the pipe, and the data is used to create edges in the pipes graph.
 *
 * @param decision An integer representing the decision to choose between different CSV files.
 *                 If decision == 1, reads from "Pipes.csv", otherwise reads from "Pipes_Madeira.csv".
 *
 * @remarks This function assumes that the CSV file has the following format:
 *          source_node,destination_node,capacity,direction
 *          For direction == 1, the line is terminated by '\r'.
 *
 * @complexity The time complexity of this function depends on the number of lines in the CSV file,
 *             denoted as 'n':
 *             - Reading each line from the file: O(n)
 *             - Parsing each line and extracting data: O(1)
 *             - Adding each edge to the graph: O(1)
 *             Overall, the time complexity is O(n) considering the worst-case scenario.
 */
    void ReadLines(int decision);
    /**
 * @brief Reads lines from a CSV file containing pipe data and populates a copy of the pipes graph, excluding connections involving a specific reservoir.
 *
 * This function reads lines from a CSV file containing pipe data. Each line is parsed to extract
 * information about the pipe, and the data is used to create edges in a copy of the pipes graph, excluding connections
 * involving a specific reservoir.
 *
 * @param reservoir The reservoir object for which connections should be excluded from the copy of the pipes graph.
 * @param decision An integer representing the decision to choose between different CSV files.
 *                 If decision == 1, reads from "Pipes.csv", otherwise reads from "Pipes_Madeira.csv".
 *
 * @remarks This function assumes that the CSV file has the following format:
 *          source_node,destination_node,capacity,direction
 *          For direction == 1, the line is terminated by '\r'.
 *          Connections involving the specified reservoir are excluded from the copy of the pipes graph.
 *
 * @complexity The time complexity of this function depends on the number of lines in the CSV file,
 *             denoted as 'n', and the number of connections involving the specified reservoir, denoted as 'm':
 *             - Reading each line from the file: O(n)
 *             - Parsing each line and extracting data: O(1)
 *             - Adding each edge to the copy of the graph: O(1)
 *             Overall, the time complexity is O(n + m) considering the worst-case scenario.
 */
    void ReadLines_copy_reservoirs(const Reservoirs& reservoirs, int decision);
    /**
 * @brief Reads lines from a CSV file containing pipe data and populates a copy of the pipes graph, excluding connections involving a specific station.
 *
 * This function reads lines from a CSV file containing pipe data. Each line is parsed to extract
 * information about the pipe, and the data is used to create edges in a copy of the pipes graph, excluding connections
 * involving a specific station.
 *
 * @param station The station object for which connections should be excluded from the copy of the pipes graph.
 * @param decision An integer representing the decision to choose between different CSV files.
 *                 If decision == 1, reads from "Pipes.csv", otherwise reads from "Pipes_Madeira.csv".
 *
 * @remarks This function assumes that the CSV file has the following format:
 *          source_node,destination_node,capacity,direction
 *          For direction == 1, the line is terminated by '\r'.
 *          Connections involving the specified station are excluded from the copy of the pipes graph.
 *
 * @complexity The time complexity of this function depends on the number of lines in the CSV file,
 *             denoted as 'n', and the number of connections involving the specified station, denoted as 'm':
 *             - Reading each line from the file: O(n)
 *             - Parsing each line and extracting data: O(1)
 *             - Adding each edge to the copy of the graph: O(1)
 *             Overall, the time complexity is O(n + m) considering the worst-case scenario.
 */
    void ReadLines_copy_station(const Stations& stations, int decision);
    /**
 * @brief Reads lines from a CSV file containing pipe data and populates a copy of the pipes graph, excluding connections involving a specific station.
 *
 * This function reads lines from a CSV file containing pipe data. Each line is parsed to extract
 * information about the pipe, and the data is used to create edges in a copy of the pipes graph, excluding connections
 * involving a specific station.
 *
 * @param station The station object for which connections should be excluded from the copy of the pipes graph.
 * @param decision An integer representing the decision to choose between different CSV files.
 *                 If decision == 1, reads from "Pipes.csv", otherwise reads from "Pipes_Madeira.csv".
 *
 * @remarks This function assumes that the CSV file has the following format:
 *          source_node,destination_node,capacity,direction
 *          For direction == 1, the line is terminated by '\r'.
 *          Connections involving the specified station are excluded from the copy of the pipes graph.
 *
 * @complexity The time complexity of this function depends on the number of lines in the CSV file,
 *             denoted as 'n', and the number of connections involving the specified station, denoted as 'm':
 *             - Reading each line from the file: O(n)
 *             - Parsing each line and extracting data: O(1)
 *             - Adding each edge to the copy of the graph: O(1)
 *             Overall, the time complexity is O(n + m) considering the worst-case scenario.
 */
    void ReadLines_copy_edgeless(int decision, const pair<string,string>& pp);
/**
 * @brief Computes all possible flows in the network, considering constraints and variations in flow.
 *
 * This function computes all possible flows in the network, considering constraints such as reservoir maximum delivery
 * and city demand. It iterates over all pipes in the network and calculates the maximum flow using the Edmonds-Karp algorithm.
 * It then compares the calculated flow with the original flow to detect any variations. If there are variations in flow that result in
 * a deficit in demand, the affected cities are identified and information about the deficit is displayed.
 *
 * @param pipe The original pipes graph.
 * @param citii The hash table containing city information.
 * @param reserr The hash table containing reservoir information.
 * @param chs_fl An integer representing the decision to choose between different CSV files.
 *               If chs_fl == 1, reads from "Pipes.csv", otherwise reads from "Pipes_Madeira.csv".
 *
 * @remarks This function assumes that there are super source and super sink vertices in the graph.
 *
 * @complexity The time complexity of this function depends on the number of edges and vertices in the pipes graph,
 *             denoted as 'E' and 'V' respectively, as well as the number of reservoirs and cities, denoted as 'R' and 'C':
 *             - Finding super source and super sink vertices: O(1)
 *             - Iterating over reservoirs and cities: O(R + C)
 *             - Running the Edmonds-Karp algorithm for each pair of super source and super sink: O(V * E^2)
 *             - Iterating over all pipes in the network: O(E)
 *             Overall, the time complexity is O((R + C) * (V * E^2 + E)) considering the worst-case scenario.
 */

    static void AllPipes(Graph<string> pipe,const HashCities& citii, const HashReservoirs& reserr, int chs_fl);
    /**
 * @brief Computes flows in the network affecting a specific city, considering constraints and variations in flow.
 *
 * This function computes flows in the network affecting a specific city, considering constraints such as reservoir maximum delivery
 * and city demand. It iterates over all pipes in the network and calculates the maximum flow using the Edmonds-Karp algorithm.
 * It then compares the calculated flow with the original flow to detect any variations. If there are variations in flow that result in
 * a deficit in demand for the specified city, the affected pipes are identified and information about the deficit is displayed.
 *
 * @param pipe The original pipes graph.
 * @param citii The hash table containing city information.
 * @param reserr The hash table containing reservoir information.
 * @param chs_fl An integer representing the decision to choose between different CSV files.
 *               If chs_fl == 1, reads from "Pipes.csv", otherwise reads from "Pipes_Madeira.csv".
 * @param cit The code of the specific city for which flows are computed and analyzed.
 *
 * @remarks This function assumes that there are super source and super sink vertices in the graph.
 *
 * @complexity The time complexity of this function depends on the number of edges and vertices in the pipes graph,
 *             denoted as 'E' and 'V' respectively, as well as the number of reservoirs and cities, denoted as 'R' and 'C':
 *             - Finding super source and super sink vertices: O(1)
 *             - Iterating over reservoirs and cities: O(R + C)
 *             - Running the Edmonds-Karp algorithm for each pair of super source and super sink: O(V * E^2)
 *             - Iterating over all pipes in the network: O(E)
 *             Overall, the time complexity is O((R + C) * (V * E^2 + E)) considering the worst-case scenario.
 */
    static void OneCity(Graph<string>pipe,const HashCities& citii, const HashReservoirs& reserr, int chs_fl, string cit);
    /**
 * @brief Checks if an edge already exists in the given vector of edges.
 *
 * This function checks if an edge, defined by its origin and destiny vertices, already exists in the given vector of edges.
 *
 * @param origin The code of the origin vertex of the edge.
 * @param destiny The code of the destiny vertex of the edge.
 * @param rawr The vector of pairs representing existing edges.
 *
 * @return True if the edge does not exist in the vector, false otherwise.
 *
 * @complexity The time complexity of this function is O(n), where 'n' is the size of the vector of existing edges.
 */
    static bool check_existing_edge(const string& origin, const string& destiny, const vector<pair<string,string>>& rawr);

    static void Max_flow_specific_city(Vertex<string> * super_source, Vertex<string> * super_sink, Graph<string> pipes, HashCities hashCities, HashReservoirs hashReservoirs, string input);
    static void Max_flow_non_specific_city_with_overflow(Vertex<string> * super_source, Vertex<string> * super_sink, Graph<string> pipes, HashCities hashCities, HashReservoirs hashReservoirs, string input, vector<string> not_full, vector<max_flow_info> pipi);
    static void Max_flow_non_specific_city_without_overflow(Vertex<string> * super_source, Vertex<string> * super_sink, Graph<string> pipes, HashCities hashCities, HashReservoirs hashReservoirs, string input, vector<string> not_full, vector<max_flow_info> pipi);

    static void Removing_reservoir(Vertex<string> * super_source, Vertex<string> * super_sink, Graph<string> pipes, HashCities cities, HashReservoirs reservoirs, string input, vector<string> not_full, int chs_fl, HashCities cities_copy, HashReservoirs reservoirs_copy, HashStations stations_copy, Pipes pipes_copy);



    //void Max_flow_specific_city(string super_source, string super_sink, Graph<string> pipe, )
/**
 * @brief Balances the load of flow in the network of pipes.
 *
 * This function redistributes the flow in the network of pipes to balance the load,
 * aiming to achieve a more uniform flow distribution across all pipes.
 *
 * @param pipes2 The pipes object representing the network of pipes.
 * @param citii The HashCities object containing city information.
 * @param reserr The HashReservoirs object containing reservoir information.
 *
 * @remarks This function assumes that the input pipes object, HashCities object, and HashReservoirs object contain valid data
 *          representing the network of pipes, cities, and reservoirs respectively.
 *
 * @complexity The time complexity of this function depends on the number of vertices and edges in the pipes network,
 *             denoted as 'V' and 'E' respectively:
 *             - Iterating over all vertices and their adjacent edges to compute total flow and pipe count: O(V * E)
 *             - Redistributing flow from pipes with higher flow rates to pipes with lower flow rates: O(V^2 * E)
 *             - Calling the computeInitialMetrics function: O(V * E)
 *             Overall, the time complexity is O(V^2 * E).
 */
    static void balanceLoad(Pipes& pipes,const HashCities& citii, const HashReservoirs& reserr);
    /**
 * @brief Computes and prints initial metrics related to flow in the network of pipes.
 *
 * This function computes and prints initial metrics related to the flow in the network of pipes.
 * It calculates metrics such as average difference, variance, and maximum difference between the weight
 * and flow of each pipe in the network.
 *
 * @param pipes2 The pipes object representing the network of pipes.
 * @param whi An integer flag indicating whether the metrics are for unbalanced (whi = 0) or balanced (whi != 0) pipes.
 *
 * @remarks This function assumes that the input pipes object contains valid data representing the network.
 *
 * @complexity The time complexity of this function depends on the number of vertices and edges in the pipes network,
 *             denoted as 'V' and 'E' respectively:
 *             - Iterating over all vertices and their adjacent edges: O(V * E)
 *             - Computing sum, max, and variance: O(V * E)
 *             Overall, the time complexity is O(V * E).
 */
    static void computeInitialMetrics(const Pipes& pipes, int whi);

/**
 * @brief Performs the Edmonds-Karp algorithm to compute maximum flow in the network of pipes.
 *
 * This function implements the Edmonds-Karp algorithm to compute the maximum flow from a given source to a target
 * in the network of pipes represented by the provided graph.
 *
 * @param source The source vertex representing the starting point of flow.
 * @param target The target vertex representing the endpoint of flow.
 * @param pipe The graph representing the network of pipes.
 *
 * @remarks This function assumes that the input graph contains valid data representing the network of pipes,
 *          and the source and target vertices are present in the graph.
 *
 * @complexity The time complexity of this function depends on the number of vertices and edges in the input graph,
 *             denoted as 'V' and 'E' respectively:
 *             - Initializing flow on all edges to 0: O(V * E)
 *             - Finding augmenting paths using breadth-first search (BFS): O(V * E^2)
 *             - Augmenting flow along each augmenting path: O(V * E)
 *             Overall, the time complexity is O(V * E^2).
 */
    static void edmondsKarp(const string& source, const string& target, const Graph<string>& pipe);
/**
 * @brief Augments the flow along the augmenting path.
 *
 * This function traverses the augmenting path from the target vertex to the source vertex and updates
 * the flow values of the edges accordingly based on the given flow value.
 *
 * @param s The source vertex representing the starting point of the augmenting path.
 * @param t The target vertex representing the endpoint of the augmenting path.
 * @param f The flow value to be augmented along the path.
 *
 * @remarks This function assumes that the augmenting path exists and is stored in the parent pointers
 *          of the vertices, leading from the target vertex to the source vertex.
 *          It also assumes that the vertices and edges have valid pointers set for accessing parent pointers
 *          and edge flow values.
 *
 * @complexity The time complexity of this function depends on the length of the augmenting path,
 *             denoted as 'L':
 *             - Traversing the augmenting path and updating flow values: O(L)
 *             Overall, the time complexity is O(L).
 */

    static void augmentFlowAlongPath(Vertex<string> *s, Vertex<string> *t, double f);
    /**
 * @brief Finds the minimum residual capacity along the augmenting path.
 *
 * This function traverses the augmenting path from the target vertex to the source vertex to determine
 * the minimum residual capacity along the path.
 *
 * @param s The source vertex representing the starting point of the augmenting path.
 * @param t The target vertex representing the endpoint of the augmenting path.
 *
 * @return The minimum residual capacity along the augmenting path.
 *
 * @remarks This function assumes that the augmenting path exists and is stored in the parent pointers
 *          of the vertices, leading from the target vertex to the source vertex.
 *          It also assumes that the vertices and edges have valid pointers set for accessing parent pointers
 *          and edge weights.
 *
 * @complexity The time complexity of this function depends on the length of the augmenting path,
 *             denoted as 'L':
 *             - Traversing the augmenting path: O(L)
 *             Overall, the time complexity is O(L).
 */
    static double findMinResidualAlongPath(Vertex<string> *s, Vertex<string> *t);
    /**
 * @brief Finds an augmenting path in the network of pipes using breadth-first search (BFS).
 *
 * This function performs a breadth-first search (BFS) starting from the source vertex to find an augmenting path
 * to the target vertex in the network of pipes represented by the provided graph.
 *
 * @param s The source vertex representing the starting point of the search.
 * @param t The target vertex representing the endpoint of the search.
 * @param pipe The graph representing the network of pipes.
 *
 * @return True if an augmenting path to the target vertex is found, false otherwise.
 *
 * @remarks This function assumes that the input graph contains valid data representing the network of pipes,
 *          and both the source and target vertices are present in the graph.
 *
 * @complexity The time complexity of this function depends on the number of vertices and edges in the input graph,
 *             denoted as 'V' and 'E' respectively:
 *             - Visiting all vertices in the graph: O(V)
 *             - Enqueuing and dequeuing vertices in the BFS queue: O(V)
 *             - Processing outgoing and incoming edges of each vertex: O(E)
 *             Overall, the time complexity is O(V + E).
 */
    static bool findAugmentingPath( Vertex<string> *s, Vertex<string> *t, const Graph<string>& pipe);
    /**
 * @brief Tests the given vertex and visits it if conditions are met.
 *
 * This function tests whether the given vertex 'w' meets certain conditions (not visited and residual capacity > 0).
 * If the conditions are met, it marks 'w' as visited, sets the path through which it was reached, and enqueues it.
 *
 * @param q A reference to the queue used for BFS traversal.
 * @param e The edge connecting the current vertex to vertex 'w'.
 * @param w The vertex to be tested and visited if conditions are met.
 * @param residual The residual capacity of the edge connecting the current vertex to vertex 'w'.
 *
 * @remarks This function is typically used in BFS traversal to visit vertices that satisfy certain conditions.
 *          It assumes that the vertex 'w' and the edge 'e' are valid and not null pointers.
 *
 * @complexity The time complexity of this function is O(1) as it performs simple conditional checks and
 *             enqueues the vertex 'w' into the queue.
 */
    static void testAndVisit(std::queue< Vertex<string>*> &q, Edge<string> *e, Vertex<string> *w, double residual);

    };




#endif //DA_PROJECT1_PIPES_H
