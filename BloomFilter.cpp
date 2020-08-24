/** Filename: BloomFilter.cpp
 *  Name: Loc Chuong
 *  Userid: cs100sp19aj
 *  Description: The class for bloom filter that provides memory efficient
 *               check of whether an item has been inserted before. Small
 *               amount of false positives is possible but there bill be no
 *               false negatives.
 *  Date: 5/2/2019
 */

#include "BloomFilter.hpp"
#include <iostream>
#include <string.h>

/* Constructor
 * Description: Create a new bloom filter with the size in bytes
 * Parameters: numBytes - The number of bytes the bloom filter will have
 */
BloomFilter::BloomFilter(size_t numBytes) {
    /** Transfer numBytes to number of bits and assign to numSlots in table */
    numSlots = (numBytes * BYTE_WIDTH);
    /** Initialize new unsigned char array to table with size numBytes */
    table = new unsigned char[numBytes];
    /** Set all elements in table to be 0 */
    memset(table, 0, numBytes);
}

/* Function Name: insert(std::string item)
 * Description: Insert an item into the bloom filter using hashing funcs
 * Parameters: item - the string to hash and put into the bloom filter
 * Return Value: None
 */
void BloomFilter::insert(std::string item) {
    /** Find the hash value for the hash function FNV-1A */
    unsigned int hashVal_FNV = FNV1AHash(item) % numSlots;
    /** Set the bit using FNV-1A hash value*/
    table[hashVal_FNV/BYTE_WIDTH] |= (UNSIGNED_INT_BIT 
            << (hashVal_FNV%BYTE_WIDTH));
    /** Find the hash value for the hash function CRC */
    unsigned int hashVal_CRC = CRCHash(item) % numSlots;
    /** Set the bit using CRC hash value*/
    table[hashVal_CRC/BYTE_WIDTH] |= (UNSIGNED_INT_BIT 
            << (hashVal_CRC%BYTE_WIDTH));
    /** Find the hash value for the hash function SBDM */
    unsigned int hashVal_SBDM = SBDMHash(item) % numSlots;
    /** Set the bit using SBDM hash value*/
    table[hashVal_SBDM/BYTE_WIDTH] |= (UNSIGNED_INT_BIT 
            << (hashVal_SBDM%BYTE_WIDTH));
}

/* Function Name: find(std::string item)
 * Description: Determine whether an item is in the bloom filter
 * Parameters: item - the string to find in the bloom filter
 * Return Value: True if item is found in bloom filter, false otherwise
 */
bool BloomFilter::find(std::string item) {
    /** Find the hash value for the hash function FNV-1A */
    unsigned int hashVal_FNV = FNV1AHash(item) % numSlots;
    if( ((table[hashVal_FNV/BYTE_WIDTH] >> hashVal_FNV%BYTE_WIDTH) & 
                UNSIGNED_INT_BIT) != UNSIGNED_INT_BIT) {
        return false;
    }
    /** Find the hash value for the hash function CRC */
    unsigned int hashVal_CRC = CRCHash(item) % numSlots;
    if( ((table[hashVal_CRC/BYTE_WIDTH] >> hashVal_CRC%BYTE_WIDTH) & 
                UNSIGNED_INT_BIT) != UNSIGNED_INT_BIT) {
        return false;
    }
    /** Find the hash value for the hash function SBDM */
    unsigned int hashVal_SBDM = SBDMHash(item) % numSlots;
    if( ((table[hashVal_SBDM/BYTE_WIDTH] >> hashVal_SBDM%BYTE_WIDTH) & 
                UNSIGNED_INT_BIT) != UNSIGNED_INT_BIT) {
        return false;
    }
    return true;
}

/** Function Name: FNV1AHash(const std::string & item)
 *  Description: Uses the FNV1A-Hash algorithm to hash a string object into an
 *               unsigned int
 *  Parameters: item - String object to hash into an unsigned int
 *  Return Value: A hash key created using item in the form of an unsigned int
 *  Source(s) of Help: isthe.com/chongo/tech/comp/fnv/
 */
unsigned int BloomFilter::FNV1AHash(const std::string & item) {
    /** Initialize initial FNV hash value */
    unsigned int hashValue = INITIAL_FNV;
    /** Perform hashing operation on each character of the string */
    for( string::const_iterator i = item.begin(); i != item.end(); i++) {
        hashValue = hashValue ^ *i;
        hashValue = hashValue * FNV_PRIME;
    }
    return hashValue;
}

/** Function Name: CRCHash(const std::string & item)
 *  Description: Uses the CRC hash algorithmn to hash a string object into an
 *               unsigned int
 *  Parameters: item - String object to hash into an unsigned int
 *  Return Value: A hash key created using item in the form of an unsigned int
 *  Source(s) of Help: Sample_hash_functions.docx from PA2 writeup (First link)
 *                     https://drive.google.com/file/d/1elgi1e1nU9gZxmJcl9Rax
 *                     gryZBnxooVT/view
 */
unsigned int BloomFilter::CRCHash(const std::string & item) {
    /** Initialize initial CRC hash value */
    unsigned int hashValue = 0;
    /** Perform hashing operation on each character of the string */
    for( string::const_iterator i = item.begin(); i != item.end(); i++) {
        unsigned int leftShift = hashValue << CRC_HASH_SHIFT;
        unsigned int rightShift = hashValue >> (WORD_WIDTH - CRC_HASH_SHIFT);
        hashValue = (leftShift | rightShift) ^ (unsigned)*i;
    }
    return hashValue;
}

/** Function Name: SBDMHash(const std::string & item)
 *  Description: Uses the SBDM hash algorithmn to hash a string object into an
 *               unsigned int
 *  Parameters: item - String object to hash into an unsigned int
 *  Return Value: A hash key created using item in the form of an unsigned int
 *  Source(s) of Help: www.cse.yorku.ca/~oz/hash.html
 */
unsigned int BloomFilter::SBDMHash(const std::string & item) {
    /** Initialize initial SBDM hash value */
    unsigned int hashValue = 0;
    /** Perform hasing operation on each character of the string */
    for( string::const_iterator i = item.begin(); i != item.end(); i++) {
        hashValue = (*i) + (hashValue << SBDM_HASH_FIRST_SHIFT) 
            + (hashValue << SBDM_HASH_SECOND_SHIFT) - hashValue;
    }
    return hashValue;
}

/* Destructor
 * Description: Destructor for the bloom filter
 */
BloomFilter::~BloomFilter() {
    /** Delete char pointer to char array */
    delete[] table;
}
