#ifndef UTIL_HPP
#define UTIL_HPP

#include <chrono>
#include "DictionaryTrie.hpp"
#include <iostream>
#include <vector>

using namespace std;

using std::istream;

class Timer{
private:
  std::chrono::time_point<std::chrono::high_resolution_clock> start;

public:

  /*
   * Function called when starting the timer.
   */
  void begin_timer();

  /*
   * Function called when ending the timer. Returns duration in nanoseconds
   * PRECONDITION: begin_timer() must be called before this function
   */
  long long end_timer();


};

class Utils{
public:

    static unsigned int stripFrequency(string& line);
    static std::vector<string> getWordsFromLine(string& line);

    /*
     * Load the words in the file into the dictionary
     */
    void static load_dict(DictionaryTrie& dict, istream& words);


    /*
     * Load num_words from words stream into the dictionary
     */
    void static load_dict(DictionaryTrie& dict, istream& words, unsigned int num_words);


    void static load_dict(vector<string>& dict, istream& words);

};


#endif //UTIL_HPP
