/** Filename: autocomplete.cpp
 *  Name: Loc Chuong
 *  Userid: cs100sp19aj
 *  Description: This file defines the autocomplete function using a TST. It
 *               will ask users for prefix/pattern to search for in a
 *               dictionary and output the predictions to the user.
 *  Date: 4/29/2019
 */

#include "DictionaryTrie.hpp"
#include "util.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#define FILE_ARG 1
#define MAX_ARG 2
#define NULLCHAR '\0'
#define CONTINUE "y"

using namespace std;

/** Function Name: main(int argc, char** argv)
 *  Description: This is the driver of the program that will ask users for
 *               input and uses their one file argument as the basis for the
 *               TST.
 *  Parameters: argc - Number of arguments passed in by the user
 *              argv - Pointer to the actual arguments passed in by user
 */
int main(int argc, char** argv) {

    /** Check for correct number of arguments */
    if( argc != MAX_ARG) {
        cout << "This program needs exactly one argument!" << endl;
        return -1;
    }
    /** Read in file */
    ifstream readFile(argv[FILE_ARG], ios::in);
    /** Checks for invalid file */
    if( !readFile) {
        cout << "Could not open file or invalid file" << endl;
        return -1;
    }
    /** Create Trie to hold insertions */
    DictionaryTrie * DT = new DictionaryTrie();
    cout << "Reading file: " << argv[FILE_ARG] << endl;
    /** Popualte DictionaryTrie using helper function from Util */
    Utils::load_dict(*DT, readFile);
    /** Keep checking for user input until user exits via input */
    while(1) {
        /** Holds prefix or pattern to search for */
        string search;
        /** Holds number of completions */
        string num_completions;
        /** Holds value to continue or end program */
        string cont;
        cout << "Enter a prefix/pattern to search for:" << endl;
        getline(cin, search);
        cout << "Enter a number of completions:" << endl;
        getline(cin, num_completions);
        /** Turn string to unsigned int */
        unsigned int completions = stoul(num_completions);
        /** Create variable to hold occurances of underscore in user input */
        unsigned int underScore = 0;
        /** Search the prefix/pattern for underscore characters */
        for( string::iterator it = search.begin(); it != search.end(); it++) {
            if(*it == UNDERSCORE) {
                underScore++;
            }
        }
        /** Create return vector of strings for completions or underscore */
        std::vector<std::string> str;
        /** No underscore characters in prefix/pattern to search for */
        if( underScore == 0) { 
            /** Find predictions where search is a prefix */
            str = DT->predictCompletions(search, completions);
        }
        /** One underscore characters in prefix/pattern to search for */
        else if( underScore == 1) {
            /** Find predictions where search is a pattern */
            str = DT->predictUnderscore(search, completions);
        }
        /** Print out results of predictions to user */
        for( unsigned int i = 0; i < str.size(); i++) {
            cout << str[i] << endl;
        }
        cout << "Continue? (y/n)" << endl;
        /** Grab user input */
        getline(cin, cont);
        /** Exit program if user does not input "y" when asked */ 
        if( cont.compare(CONTINUE) != 0) {
            /** Delete the DictionaryTrie */
            delete DT;
            /** Return program ended successfully */
            return 0;
        }
    }

}
