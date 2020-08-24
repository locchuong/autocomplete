/** Filename: firewall.cpp
 *  Name: Loc Chuong
 *  Userid: cs100sp19aj
 *  Description: The main driver of the firewall program. The program will 
 *               populate a bloom filter with the bad urls and pick out the
 *               good urls from the mixed urls ultimately placing the good urls
 *               into the output file.
 *  Date: 5/2/2019
 */

#include <iostream>
#include <fstream>
#include "BloomFilter.hpp"
#include <iomanip>
#define MAX_ARG 4 /** Defines number of max arguments allowed to pass in */
#define BADURL_ARG 1 /** Defines the argument index for bad url file */
#define MIXEDURL_ARG 2 /** Defines the argument index of mixed url file */
#define GOODURL_ARG 3 /** Defines the argument index of output file */

using namespace std;

/** Function Name: main(int argc, char** argv)
 *  Description: The main driver of the firewall program. This program will
 *               take in 3 arguments: (1) the bad urls, (2) the mixed urls, and
 *               (3) the output file name. The program will populate a bloom
 *               filter with the bad urls and pick out the good urls
 *               from the mixed urls ultimately placing the good urls into
 *               the output file.
 *  Parameters: argc - The number of arguments passed in by user
 *              argv - An array of char * representing user's arguments
 *  Return Value: An int representing the success of the program
 */
int main(int argc, char** argv) {
    /** Check for correct number of arguments */
    if( argc != MAX_ARG) {
        cout << "This program requires 3 arguments!" << endl;
        return -1;
    }
    /** Read in bad urls to filter out */
    ifstream badUrlFile(argv[BADURL_ARG]);
    /** Read in mixed urls to file stream */ 
    ifstream mixedUrlFile(argv[MIXEDURL_ARG], ios::in);
    /** Read in bad urls to find the file size */ 
    ifstream fileSize(argv[BADURL_ARG], ifstream::ate | ifstream::binary);
    /** Create file to store good urls to file */
    fstream outputFile;
    /** Stores a line of the file */
    string line;
    /** Used to determine size of hash table */
    size_t numBytes = 0;
    /** Number of lines in the bad url text file */
    double badUrl = 0;
    /** Number of lines in the output url text file */
    double outputUrl = 0;
    /** Number of lines in the good url text file */
    double safeUrl = 0;

    /** Go through each line of bad url file and count lines */ 
    while(getline(badUrlFile, line)) {
        /** Increment number of bad url lines */
        badUrl++;
        /** Increment number of bad url lines to be used as num of bytes */
        numBytes++;
    }
    /** Assign value to numBytes to be (1.5)*(number of bad urls) */
    numBytes = ((numBytes*3)/2);
    /** Create BloomFilter object to store bad urls */
    BloomFilter BF(numBytes);
    /** Clear eof flag */
    badUrlFile.clear();
    /** Seek back to start of file */
    badUrlFile.seekg(0, ios::beg);
    /** Populate the bloom filter with the bad urls */
    while(getline(badUrlFile, line)) {
        BF.insert(line);
    }

    /** Open output file using arg from user to write to */
    outputFile.open(argv[GOODURL_ARG], fstream::in | fstream::out |
            fstream::trunc);
    /** Go through every line of the mixed url file */
    while(getline(mixedUrlFile, line)) {
        /** Increment number of total urls */
        safeUrl++;
        /** Found bad url */
        if( !(BF.find(line))) {
            /** Increment number of urls outputted */
            outputUrl++;
            /** Write line to output file */
            outputFile << line << endl; 
        }
    }
    /** Calculate number of safe urls */
    safeUrl = safeUrl - badUrl;
    /** Calculate the rate of false positives */
    double rate = ((safeUrl - outputUrl)/safeUrl);

    /** Set precision to print out double */
    cout.precision(7);
    /** Print out False positive rate */
    cout << "False positive rate: " << fixed << rate << endl;
    /** Calculate the saved memory ratio */
    double memoryRate= (double)fileSize.tellg()/numBytes;
    /** Set precision to print out double */
    cout.precision(4);
    /** Print out Saved memory ratio */
    cout << "Saved memory ratio: " << fixed << memoryRate << endl;
    /** Close output file */
    outputFile.close();
}
