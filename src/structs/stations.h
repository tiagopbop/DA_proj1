//
// Created by loading on 05-03-2024.
//

#ifndef DA_PROJECT1_STATIONS_H
#define DA_PROJECT1_STATIONS_H
#include <string>
#include <unordered_set>
#include "Graph.h"
#include "pipes.h"

using namespace std;
class Pipes;
class Stations{
private:
    int id;
    string code;
public:
    /**
 * @brief Default constructor. Initializes attributes to default values.
 *
 * Initializes the station with default attribute values:
 * - ID: 0
 * - Code: "PS_0"
 */
    Stations();
    /**
 * @brief Constructor with ID parameter.
 *
 * Initializes the station with the specified ID and default code "PS_0".
 *
 * @param id The ID of the station.
 */
    Stations(int id);
    /**
 * @brief Constructor with ID and code parameters.
 *
 * Initializes the station with the specified ID and code.
 *
 * @param id The ID of the station.
 * @param code The code of the station.
 */
    Stations(int id, string code);
    /**
 * @brief Get the ID of the station.
 *
 * @return The ID of the station.
 */
    int getId() const;
    /**
 * @brief Get the code of the station.
 *
 * @return The code of the station.
 */
    string getCode() const;
    /**
   * @brief Set the code of the station.
   *
   * @param code The new code of the station.
   */
    void setCode(string code);
};

struct StationsHash {
    /**
   * @brief Hashes a Stations object based on its station code.
   *
   * This function computes a hash value for a Stations object based on its station code.
   * It uses the djb2 algorithm to generate the hash value.
   *
   * @param b The Stations object to hash.
   * @return The computed hash value.
   *
   * @remarks This hash function aims to distribute hash values evenly across a range of buckets
   *          in a hash table.
   *
   * @complexity The time complexity of this function is O(n), where 'n' is the length of the
   *             station code.
   */
    int operator() (const Stations& b) const {
        const string& code = b.getCode();
        unsigned  int hash = 5381;

        for(char c: b.getCode()){
            hash = 33*hash + static_cast<unsigned int>(c);
        }

        return hash % 3019;
    }

    /**
        * @brief Checks equality between two Stations objects based on their station codes.
        *
        * This function checks whether two Stations objects are equal based on their station codes.
        *
        * @param b1 The first Stations object.
        * @param b2 The second Stations object.
        * @return True if the station codes of the two objects are equal, otherwise false.
        *
        * @remarks This function is used to determine equality between Stations objects when
        *          resolving collisions in a hash table.
        *
        * @complexity The time complexity of this function is O(1).
        */
    bool operator()(const Stations &b1, const Stations &b2) const {
        return b1.getCode() == b2.getCode();
    }
};


typedef unordered_set<Stations, StationsHash, StationsHash>StationsTable;
class HashStations{
public:
    StationsTable stationsTable;
    /**
 * @brief Reads lines from a CSV file containing station data and populates the hash table of stations.
 *
 * This function reads lines from a CSV file containing station data. Each line is parsed to extract
 * information about the station, and the data is used to create Station objects which are then inserted
 * into a hash table.
 *
 * @param pipes The Pipes object containing the hash table to store station codes.
 * @param decision An integer representing the decision to choose between different CSV files.
 *                 If decision == 1, reads from "Stations.csv", otherwise reads from "Stations_Madeira.csv".
 *
 * @remarks This function assumes that the CSV file has the following format:
 *          id,code
 *          For decision == 1, the code field is expected to be terminated by '\r'.
 *          For decision != 1, the code field is expected to be terminated by ','.
 *
 * @complexity The time complexity of this function depends on the number of lines in the CSV file,
 *             denoted as 'n':
 *             - Reading each line from the file: O(n)
 *             - Parsing each line and extracting data: O(1)
 *             - Inserting each station into the hash table: O(1)
 *             Overall, the time complexity is O(n) considering the worst-case scenario.
 */
    void readLines(Pipes &pipes, int decision);

/**
 * @brief Finds a station with the given code in the hash table.
 *
 * This function searches for a station with the specified code in the hash table of stations. It creates
 * a dummy Stations object with the provided code and uses it to search for the station in the hash table.
 * If the station is found, a pointer to the station object is returned; otherwise, nullptr is returned.
 *
 * @param code The code of the station to search for.
 * @return A pointer to the found station object if it exists, otherwise nullptr.
 *
 * @remarks This function assumes that each station in the hash table has a unique code.
 *
 * @complexity The time complexity of this function depends on the size of the hash table and its
 *             collision resolution strategy. Let 'n' be the number of stations in the hash table,
 *             and 'm' be the number of buckets in the hash table:
 *             - Creating a dummy Stations object: O(1)
 *             - Searching for the station in the hash table: O(1) on average (assuming constant-time
 *               access in the hash table), O(n) in the worst case (if all stations hash to the same
 *               bucket and linear search is performed)
 *             Overall, the time complexity is O(1) on average, O(n) in the worst case.
 */
    const Stations* findStation(const string& code) const {
        Stations dummyStation; // Create a dummy Stations object with the given code
        dummyStation.setCode(code);

        auto it = stationsTable.find(dummyStation);
        if (it != stationsTable.end()) {
            return &(*it); // Return a pointer to the found object
        } else {
            return nullptr; // Object not found
        }
    }};


#endif //DA_PROJECT1_STATIONS_H
