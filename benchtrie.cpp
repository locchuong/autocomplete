/** Filename: benchtrie.cpp
 *  Name: Loc Chuong
 *  Userid: cs100sp19aj
 *  Description: Used to test the runtime of the DictionaryTrie
 *  Date: 5/6/2019
 *  Created by Zizhou zhai on 2/1/16.
 */

#include "util.hpp"
#include "DictionaryTrie.hpp"
#include <fstream>
#include <sstream>
using namespace std;

void testStudent(string dict_filename){

    ifstream in;
    in.open(dict_filename, ios::binary);


    // Testing student's trie
    cout << "\nTiming your solution" << endl;
    cout << "\nLoading dictionary..." << endl;
    DictionaryTrie* dictionary_trie = new DictionaryTrie();

    Utils::load_dict(*dictionary_trie, in);

    cout << "Finished loading dictionary." << endl;
    cout << "\nStarting timing tests for your solution." << endl;

    Timer T;
    vector<string> results;
    long long time_duration;

    // Test 1
    cout << "\n\tTest 1: prefix= \"*iterating through alphabet*\"," <<
        " num_completions= 10" << endl;
    T.begin_timer();
    int count = 0;
    results = dictionary_trie->predictCompletions("a",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("b",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("c",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("d",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("e",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("f",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("g",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("h",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("i",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("j",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("k",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("l",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("m",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("n",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("o",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("p",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("q",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("r",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("s",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("t",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("u",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("v",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("w",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("x",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("y",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("z",10);
    count += results.size();
    time_duration = T.end_timer();
    cout << "\tTest 1: time taken: " << time_duration << " nanoseconds."
        << endl;
    cout << "\tTest 1: results found: " <<  count << endl;

    // Test 2
    cout << "\n\tTest 2: prefix= \"a\", num_completions= 10" << endl;
    T.begin_timer();
    results = dictionary_trie->predictCompletions("a",10);
    time_duration = T.end_timer();
    cout << "\tTest 2: time taken: " << time_duration << " nanoseconds."
        << endl;
    cout << "\tTest 2: results found: " <<  results.size() << endl;

    // Test 3
    cout << "\n\tTest 3: prefix= \"the\", num_completions= 10" << endl;
    T.begin_timer();
    results = dictionary_trie->predictCompletions("the",10);
    time_duration = T.end_timer();
    cout << "\tTest 3: time taken: " << time_duration << " nanoseconds."
        << endl;
    cout << "\tTest 3: results found: " <<  results.size() << endl;

    // Test 4
    cout << "\n\tTest 4: prefix= \"app\", num_completions= 10" << endl;
    T.begin_timer();
    results = dictionary_trie->predictCompletions("app",10);
    time_duration = T.end_timer();
    cout << "\tTest 4: time taken: " << time_duration << " nanoseconds."
        << endl;
    cout << "\tTest 4: results found: " <<  results.size() << endl;

    // Test 5
    cout << "\n\tTest 5: prefix= \"man\", num_completions= 10" << endl;
    T.begin_timer();
    results = dictionary_trie->predictCompletions("man",10);
    time_duration = T.end_timer();
    cout << "\tTest 5: time taken: " << time_duration << " nanoseconds."
        << endl;
    cout << "\tTest 5: results found: " <<  results.size() << endl;

    cout << "\nWould you like to run additional tests? y/n\n";
    string response;
    getline(cin, response);

    if(response.compare("y") == 0){
        string prefix;
        string ws;
        int num_completions;

        cout << "\nAdditional user tests." << endl;
        cout << "Enter prefix: ";

        while(getline(cin, prefix)){

            cout << "Enter num_completions: ";
            getline(cin, ws);
            num_completions = stoi(ws);

            cout << "\n\tUser Test: prefix= \"" << prefix <<
                "\" num_completions= " << num_completions << endl;
            T.begin_timer();
            results = dictionary_trie->predictCompletions(prefix,
                    num_completions);
            time_duration = T.end_timer();
            cout << "\tUser Test: time taken: " << time_duration 
                << " nanoseconds." << endl;
            cout << "\tUser Test: results found: " <<  results.size()
                << "\n\n";
            cout << "Enter prefix: ";

        }

    }




    cout << "\nFinished timing your solution." << endl;
    delete dictionary_trie;


}

int main(int argc, char *argv[]) {

    if(argc < 2){
        cout << "Incorrect number of arguments." << endl;
        cout << "\t First argument: name of dictionary file." << endl;
        cout << endl;
        exit(-1);
    }

    testStudent(argv[1]);

}
