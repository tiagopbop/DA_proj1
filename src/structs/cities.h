//
// Created by loading on 05-03-2024.
//

#ifndef DA_PROJECT1_CITIES_H
#define DA_PROJECT1_CITIES_H


#include <string>
#include <unordered_set>
#include "Graph.h"
#include "pipes.h"

using namespace std;
class Pipes;
class Cities{
private:
    string city;
    int id;
    string code;
    float demand;
    string population;
public:
    /**
 * @brief Default constructor. Initializes attributes to default values.
 *
 * Initializes the city with default attribute values:
 * - City: "Portugal"
 * - ID: 0
 * - Code: "C_0"
 * - Demand: 0.0
 * - Population: "0"
 */
    Cities();
    /**
 * @brief Constructor with ID parameter.
 *
 * Initializes the city with the specified ID and default attribute values:
 * - City: "Portugal"
 * - Code: "C_0"
 * - Demand: 0.0
 * - Population: "0"
 *
 * @param id The ID of the city.
 */
    Cities(int id);
    /**
  * @brief Constructor with all parameters.
  *
  * Initializes the city with the specified attributes.
  *
  * @param city The name of the city.
  * @param id The ID of the city.
  * @param code The code of the city.
  * @param demand The demand of the city.
  * @param population The population of the city.
  */
    Cities(string city, int id, string code, float demand, string population);
    /**
  * @brief Get the ID of the city.
  *
  * @return The ID of the city.
  */
    int getId() const;
    /**
     * @brief Get the name of the city.
     *
     * @return The name of the city.
     */
    string getName() const;
    /**
    * @brief Get the code of the city.
    *
    * @return The code of the city.
    */
    string getCode() const;
    /**
 * @brief Get the demand of the city.
 *
 * @return The demand of the city.
 */
    float getDemand() const;
    /**
 * @brief Get the population of the city.
 *
 * @return The population of the city.
 */
    string getPopulation() const;
    /**
 * @brief Set the code of the city.
 *
 * @param code The new code of the city.
 */
    void setCode(string code);
};

struct CitiesHash {
    /**
 * @brief Hashes a Cities object based on its city code.
 *
 * This function computes a hash value for a Cities object based on its city code.
 * It uses the djb2 algorithm to generate the hash value.
 *
 * @param b The Cities object to hash.
 * @return The computed hash value.
 *
 * @remarks This hash function aims to distribute hash values evenly across a range of buckets
 *          in a hash table.
 *
 * @complexity The time complexity of this function is O(n), where 'n' is the length of the
 *             city code.
 */
    int operator() (const Cities& b) const {
        const string& code = b.getCode();
        unsigned  int hash = 5381;

        for(char c: b.getCode()){
            hash = 33*hash + static_cast<unsigned int>(c);
        }

        return hash % 3019;
    }


    /**
        * @brief Checks equality between two Cities objects based on their city codes.
        *
        * This function checks whether two Cities objects are equal based on their city codes.
        *
        * @param b1 The first Cities object.
        * @param b2 The second Cities object.
        * @return True if the city codes of the two objects are equal, otherwise false.
        *
        * @remarks This function is used to determine equality between Cities objects when
        *          resolving collisions in a hash table.
        *
        * @complexity The time complexity of this function is O(1).
        */
    bool operator()(const Cities &b1, const Cities &b2) const {
        return b1.getCode() == b2.getCode();
    }
};


typedef unordered_set<Cities, CitiesHash,CitiesHash> CitiesTable;

class HashCities{
public:
    CitiesTable citiesTable;
    /**
 * @brief Reads lines from a CSV file containing city data and populates the hash table of cities.
 *
 * This function reads lines from a CSV file containing city data. Each line is parsed to extract
 * information about the city, and the data is used to create City objects which are then inserted
 * into a hash table.
 *
 * @param pipes The Pipes object containing the hash table to store city codes.
 * @param decision An integer representing the decision to choose between different CSV files.
 *                 If decision == 1, reads from "Cities.csv", otherwise reads from "Cities_Madeira.csv".
 *
 * @remarks This function assumes that the CSV file has the following format:
 *          city,id,code,demand,population
 *
 * @complexity The time complexity of this function depends on the number of lines in the CSV file,
 *             denoted as 'n':
 *             - Reading each line from the file: O(n)
 *             - Parsing each line and extracting data: O(1)
 *             - Inserting each city into the hash table: O(1)
 *             Overall, the time complexity is O(n) considering the worst-case scenario.
 */
    void readLines(Pipes &pipes, int decision);

/**
 * @brief Finds a city with the given code in the hash table.
 *
 * This function searches for a city with the specified code in the hash table of cities. It creates
 * a dummy Cities object with the provided code and uses it to search for the city in the hash table.
 * If the city is found, a pointer to the city object is returned; otherwise, nullptr is returned.
 *
 * @param code The code of the city to search for.
 * @return A pointer to the found city object if it exists, otherwise nullptr.
 *
 * @remarks This function assumes that each city in the hash table has a unique code.
 *
 * @complexity The time complexity of this function depends on the size of the hash table and its
 *             collision resolution strategy. Let 'n' be the number of cities in the hash table,
 *             and 'm' be the number of buckets in the hash table:
 *             - Creating a dummy Cities object: O(1)
 *             - Searching for the city in the hash table: O(1) on average (assuming constant-time
 *               access in the hash table), O(n) in the worst case (if all cities hash to the same
 *               bucket and linear search is performed)
 *             Overall, the time complexity is O(1) on average, O(n) in the worst case.
 */
    const Cities* findCity(const string& code) const {
        Cities dummyStation; // Create a dummy Stations object with the given code
        dummyStation.setCode(code);

        auto it = citiesTable.find(dummyStation);
        if (it != citiesTable.end()) {
            return &(*it); // Return a pointer to the found object
        } else {
            return nullptr; // Object not found
        }
    }};




#endif //DA_PROJECT1_CITIES_H
