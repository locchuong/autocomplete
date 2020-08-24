/** Filename: BloomFilter.hpp
 *  Name: Loc Chuong
 *  Userid: cs100sp19aj
 *  Description: The class for bloom filter that provides memory efficient
 *               check of whether an item has been inserted before. Small
 *               amount of false positives is possible but there will be no
 *               false negatives.
 *  Date: 5/2/2019
 */

#ifndef BLOOM_FILTER_HPP
#define BLOOM_FILTER_HPP

#include <string>
#define BYTE_WIDTH 8 /** Num of bits for one byte */
#define INITIAL_FNV 216613621 /** Inital hash value for FNV-1A hash func */
#define FNV_PRIME 16777619 /** Multiplication value for FNV-1A hash func */
#define CRC_HASH_SHIFT 5 /** Shift value for CRC hash func */
#define SBDM_HASH_FIRST_SHIFT 6 /** First shift value for SBDM hash func */
#define SBDM_HASH_SECOND_SHIFT 16 /** Second shift value for SBDM hash func */
#define UNSIGNED_INT_BIT 1U /** Unsigned int with first bit set */
#define WORD_WIDTH sizeof(int)*BYTE_WIDTH /** Num of bits in a machine word */

using namespace std;

/** Class Name: BloomFilter
 *  Description: The class for bloom filter that provides memory efficient
 *               check of whether an item has been inserted before. Small
 *               amount of false positives is possible but there will be no
 *               false negatives.
 */
class BloomFilter {

    public:

        /* Constructor
         * Description: Create a new bloom filter with the size in bytes
         * Parameters: numBytes - The number of bytes the bloom filter will
         *                        have
         */
        BloomFilter(size_t numBytes);

        /* Function Name: insert(std::string item)
         * Description: Insert an item into the bloom filter using hashing
         *              funcs
         * Parameters: item - the string to hash and put into the bloom filter
         * Return Value: None
         */
        void insert(std::string item);

        /* Function Name: find(std::string item)
         * Description: Determine whether an item is in the bloom filter
         * Parameters: item - the string to find in the bloom filter
         * Return Value: True if item is found in bloom filter, false otherwise
         */
        bool find(std::string item);

        /* Destructor
         * Description: Destructor for the bloom filter
         */
        ~BloomFilter();

    private:

        unsigned char* table; /** Char array as the hash table */
        unsigned int numSlots; /** Size of hash table */

        /** Function Name: FNV1AHash(const std::string & item)
         *  Description: Uses the FNV1A-Hash algorithm to hash a string object
         *               into an unsigned int
         *  Parameters: item - String object to hash into an unsigned int
         *  Return Value: A hash key created using item in the form of an
         *                unsigned int
         *  Source(s) of Help: isthe.com/chongo/tech/comp/fnv/
         */
        unsigned int FNV1AHash(const std::string & item);

        /** Function Name: CRCHash(const std::string & item)
         *  Description: Uses the CRC hash algorithmn to hash a string object
         *               into an unsigned int
         *  Parameters: item - String object to hash into an unsigned int
         *  Return Value: A hash key created using item in the form of an
         *                unsigned int
         *  Source(s) of Help: Sample_hash_functions.docx from PA2 writeup
         *                     (First link in reference)
         *                     https://drive.google.com/file/d/1elgi1e1nU9gZxm
         *                     Jcl9RaxgryZBnxooVT/view
         */
        unsigned int SBDMHash(const std::string & item);

        /** Function Name: SBDMHash(const std::string & item)
         *  Description: Uses the SBDM hash algorithmn to hash a string object
         *               into an unsigned int
         *  Parameters: item - String object to hash into an unsigned int
         *  Return Value: A hash key created using item in the form of an
         *                unsigned int
         *  Source(s) of Help: www.cse.yorku.ca/~oz/hash.html
         */
        unsigned int CRCHash(const std::string & item);
};
#endif // BLOOM_FILTER
