/** Filename: hashStats.cpp
 *  Name: Loc Chuong
 *  Userid: cs100sp19aj
 *  Description: Prints out the number of insertions and collisions for a given
 *               hash function to test.
 *  Date: 5/6/2019
 */

#include "BloomFilter.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const unsigned int DEFAULT_SIZE = 5;
const unsigned int RESIZE_FACTOR = 2;
const double MAX_LOAD_FACTOR = 0.67;

/** stores number of inserted items in each slot */
vector<unsigned int> table(DEFAULT_SIZE);

/** stores all the hash value of inserted items */
vector<unsigned int> inserted;

unsigned int tableLen = DEFAULT_SIZE;
unsigned int numElem = 0;

/** Function Name: hashFunc(const std::string & item)
 *  Description: The hash function that we are testing for collisions
 *  Parameters: item - The string object to hash into an unsigned int
 *  Return Value: The hash value created from hashing item
 */
unsigned int hashFunc(const std::string & item) {
    /** FNV-1a algorithmn (around 28 percent) one low entry at 33 percent */
    unsigned int hash = INITIAL_FNV;
    for( string::const_iterator i = item.begin(); i != item.end(); i++) {
        hash = hash ^ *i;
        hash = hash * FNV_PRIME;
    }
    return hash;
}

/** Function Name: countCollision()
 *  Description: Returns the number of collisions in the hash table
 *  Return Value: Number of collisions in the hash table.
 */
unsigned int countCollision() {
    /** Count the number of collisions in the pseudo hash table */
    unsigned int numCollisions = 0;
    for( unsigned int i = 0; i < tableLen; i++) {
        if( table[i] > 1) {
            numCollisions += table[i] - 1;
        }
    }
    return numCollisions;
}

/** Function Name: rehash()
 *  Descrition: When load factor is high, rehash all the inserted items
 *  Return Value: None
 */
void rehash() {
    /** print out the stats before each rehash */
    std::cout << "#insertions: " << numElem << "; hash table size: " 
        << tableLen << "; #collisions: " << countCollision() << std::endl;

    tableLen = tableLen * RESIZE_FACTOR;
    table.clear();
    table.resize(tableLen);
    /** rehash all the inserted items */
    for (unsigned int hashVal: inserted) {
        table[hashVal % tableLen]++;
    }
}

/** Function Name: insert(const std::string & item)
 *  Description: "Insert" a given item to hash table. This function does not 
 *               actually insert the item, it only increases the count of
 *               number of items inserted in the hashed slot.
 *  Parameters: item - Item to be "inserted" into the hash table
 *  Return Value: None
 */
void insert(const std::string & item) {

    /** rehash if load factor is high */
    if ((double) numElem / tableLen >= MAX_LOAD_FACTOR) {
        rehash();
    }
    unsigned int hashVal = hashFunc(item);
    table[hashVal % tableLen]++;
    numElem++;
    inserted.push_back(hashVal);
}

/** Function Name: main(int argc, const char * argv[])
 *  Description: Driver of the hashStats program which will print out the
 *               number of insertions and collisions for a given hash func.
 *  Parameters: argc - Number of arguments passed in by user
 *              argv - Array of char * which are the arguments passed in
 *  Return Value: Int denoting the success of the program
 */
int main(int argc, const char * argv[]) {

    /** reads the file line by line and insert each line to hash 
     *  table to output stats about the hash function */
    ifstream items (argv[1]);
    string line;

    while (true) {
        getline(items, line);
        if (items.eof()) break;
        insert(line);
    }

}

