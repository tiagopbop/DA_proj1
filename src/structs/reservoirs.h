//
// Created by loading on 05-03-2024.
//

#ifndef DA_PROJECT1_RESERVOIRS_H
#define DA_PROJECT1_RESERVOIRS_H
#include <string>
#include <unordered_set>
#include "Graph.h"
#include "pipes.h"

using namespace std;
class Pipes;
class Reservoirs{
private:
    string name;
    string municipality;
    int id;
    string code;
    int max_del;
public:
    /**
 * @brief Default constructor. Initializes attributes to default values.
 *
 * Initializes the reservoir with default attribute values:
 * - Name: "Portugal"
 * - Municipality: "Portugal"
 * - ID: 0
 * - Code: "R_0"
 * - Maximum Delivery: 0
 */
    Reservoirs();
    /**
 * @brief Constructor with ID parameter.
 *
 * Initializes the reservoir with the specified ID and default attribute values:
 * - Name: "Portugal"
 * - Municipality: "Portugal"
 * - Code: "R_0"
 * - Maximum Delivery: 0
 *
 * @param id The ID of the reservoir.
 */
    Reservoirs(int id);
    /**
 * @brief Constructor with all parameters.
 *
 * Initializes the reservoir with the specified attributes.
 *
 * @param name The name of the reservoir.
 * @param municipality The municipality of the reservoir.
 * @param id The ID of the reservoir.
 * @param code The code of the reservoir.
 * @param max_del The maximum delivery of the reservoir.
 */
    Reservoirs(string name, string municipality, int id, string code, int max_del);

    /**
     * @brief Get the name of the reservoir.
     *
     * @return The name of the reservoir.
     */
    string getName() const;
    /**
 * @brief Get the municipality of the reservoir.
 *
 * @return The municipality of the reservoir.
 */
    string getMunicipality() const;
    /**
   * @brief Get the ID of the reservoir.
   *
   * @return The ID of the reservoir.
   */
    int getId() const;
    /**
 * @brief Get the code of the reservoir.
 *
 * @return The code of the reservoir.
 */
    string getCode() const;
    /**
   * @brief Set the code of the reservoir.
   *
   * @param code The new code of the reservoir.
   */
    int getMaxDel() const;
    /**
 * @brief Get the maximum delivery of the reservoir.
 *
 * @return The maximum delivery of the reservoir.
 */
    void setCode(string code);
};

struct ReservoirsHash {
    /**
  * @brief Hashes a Reservoirs object based on its reservoir code.
  *
  * This function computes a hash value for a Reservoirs object based on its reservoir code.
  * It uses the djb2 algorithm to generate the hash value.
  *
  * @param b The Reservoirs object to hash.
  * @return The computed hash value.
  *
  * @remarks This hash function aims to distribute hash values evenly across a range of buckets
  *          in a hash table.
  *
  * @complexity The time complexity of this function is O(n), where 'n' is the length of the
  *             reservoir code.
  */
    int operator() (const Reservoirs& b) const {
        const string& code = b.getCode();
        unsigned  int hash = 5381;

        for(char c: b.getCode()){
            hash = 33*hash + static_cast<unsigned int>(c);
        }

        return hash % 3019;
    }

    /**
       * @brief Checks equality between two Reservoirs objects based on their reservoir codes.
       *
       * This function checks whether two Reservoirs objects are equal based on their reservoir codes.
       *
       * @param b1 The first Reservoirs object.
       * @param b2 The second Reservoirs object.
       * @return True if the reservoir codes of the two objects are equal, otherwise false.
       *
       * @remarks This function is used to determine equality between Reservoirs objects when
       *          resolving collisions in a hash table.
       *
       * @complexity The time complexity of this function is O(1).
       */
    bool operator()(const Reservoirs &b1, const Reservoirs &b2) const {
        return b1.getCode() == b2.getCode();
    }
};


typedef unordered_set<Reservoirs, ReservoirsHash,ReservoirsHash> ReservoirsTable;

class HashReservoirs{
public:
    ReservoirsTable reservoirsTable;
    /**
 * @brief Reads lines from a CSV file containing reservoir data and populates the hash table of reservoirs.
 *
 * This function reads lines from a CSV file containing reservoir data. Each line is parsed to extract
 * information about the reservoir, and the data is used to create Reservoir objects which are then inserted
 * into a hash table.
 *
 * @param pipes The Pipes object containing the hash table to store reservoir codes.
 * @param decision An integer representing the decision to choose between different CSV files.
 *                 If decision == 1, reads from "Reservoir.csv", otherwise reads from "Reservoirs_Madeira.csv".
 *
 * @remarks This function assumes that the CSV file has the following format:
 *          reservoir,municipality,id,code,max_delimiter
 *          For decision == 1, the max_delimiter is expected to be terminated by '\r'.
 *          For decision != 1, the max_delimiter is expected to be terminated by ','.
 *
 * @complexity The time complexity of this function depends on the number of lines in the CSV file,
 *             denoted as 'n':
 *             - Reading each line from the file: O(n)
 *             - Parsing each line and extracting data: O(1)
 *             - Inserting each reservoir into the hash table: O(1)
 *             Overall, the time complexity is O(n) considering the worst-case scenario.
 */
    void readLines(Pipes &pipes, int decision);
/**
 * @brief Finds a reservoir with the given code in the hash table.
 *
 * This function searches for a reservoir with the specified code in the hash table of reservoirs. It creates
 * a dummy Reservoirs object with the provided code and uses it to search for the reservoir in the hash table.
 * If the reservoir is found, a pointer to the reservoir object is returned; otherwise, nullptr is returned.
 *
 * @param code The code of the reservoir to search for.
 * @return A pointer to the found reservoir object if it exists, otherwise nullptr.
 *
 * @remarks This function assumes that each reservoir in the hash table has a unique code.
 *
 * @complexity The time complexity of this function depends on the size of the hash table and its
 *             collision resolution strategy. Let 'n' be the number of reservoirs in the hash table,
 *             and 'm' be the number of buckets in the hash table:
 *             - Creating a dummy Reservoirs object: O(1)
 *             - Searching for the reservoir in the hash table: O(1) on average (assuming constant-time
 *               access in the hash table), O(n) in the worst case (if all reservoirs hash to the same
 *               bucket and linear search is performed)
 *             Overall, the time complexity is O(1) on average, O(n) in the worst case.
 */
    const Reservoirs* findReservoir(const string& code) const {
        Reservoirs dummyStation; // Create a dummy Stations object with the given code
        dummyStation.setCode(code);

        auto it = reservoirsTable.find(dummyStation);
        if (it != reservoirsTable.end()) {
            return &(*it); // Return a pointer to the found object
        } else {
            return nullptr; // Object not found
        }
    }};


#endif //DA_PROJECT1_RESERVOIRS_H
