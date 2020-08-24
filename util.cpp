#include <iostream>
#include <sstream>
#include "util.hpp"

using std::istream;
using std::endl;
using std::cout;
using std::istringstream;
using std::string;
using std::vector;

/**
 * Starts the timer. Saves the current time.
 */
void Timer::begin_timer()
{
    
    start = std::chrono::high_resolution_clock::now();
}

/**
 * Ends the timer. Compares end time with the start time and returns number of nanoseconds
 */
long long Timer::end_timer()
{
    
    std::chrono::time_point<std::chrono::high_resolution_clock> end;
    end = std::chrono::high_resolution_clock::now();
    
    return (long long)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

/**
 * Parse a line by taking the number at the beginning of a file.
 * This might be helpful if you want make your own test files of
 * the following format:
 * 
 * ----
 * 7 word
 * 8 words
 * 9 wordlike
 * ----
 * 
 * For example, you could use the following snippet:
 * 
 * getline(words, line);
 *      if (words.eof())
 *          break;
 *      unsigned int freq = Utils::stripFrequency(line);
 *      dict.insert(line, freq);
 *
 * Input: a line from a dictionary file. This line will be modified.
 */
unsigned int Utils::stripFrequency(string& line)
{
    // Count the number of characters past the first space
    int count = 0;
    string::iterator last = line.end();
    for (string::iterator it = line.begin(); it != last; ++it) {
        count++;
        if (*it == ' ') {
            break;
        }
    }
    unsigned int freq = std::stoi(line.substr(0, count));
    line.erase(0, count);
    return freq;
}

/**
 * Parses all the tokens on a given line, returning them
 * in a vector.
 */
vector<string> Utils::getWordsFromLine(string& line)
{
    vector<string> words;
    std::stringstream ss(line);
    string word;
    while (!ss.eof())
    {
        ss >> word;
        words.push_back(word);
    }
    return words;
}


/*
 * Load the words in the file into the dictionary trie
 */
void Utils::load_dict(DictionaryTrie& dict, istream& words)
{
    unsigned int freq;
    string data = "";
    string temp_word = "";
    string word = "";
    vector<string> word_string;
    unsigned int i = 0;
    while(getline(words, data))
    {
        if(words.eof()) break;
        temp_word = "";
        word = "";
        data = data + " .";
        istringstream iss(data);
        iss >> freq;
        while(1)
        {
            iss >> temp_word;
            if(temp_word == ".") break;
            if(temp_word.length() > 0) word_string.push_back(temp_word);
        }
        for(i = 0; i < word_string.size(); i++)
        {
            if(i > 0) word = word + " ";
            word = word + word_string[i];
        }
        dict.insert(word, freq);
        word_string.clear();
    }
}


/*
 * Load num_words from words stream into the dictionary trie
 */
void Utils::load_dict(DictionaryTrie& dict, istream& words, unsigned int num_words)
{
    unsigned int freq;
    string data = "";
    string temp_word = "";
    string word = "";
    vector<string> word_string;
    unsigned int i = 0;
    unsigned int j = 0;
    for(; j < num_words; j++)
    {
        getline(words, data);
        if(words.eof()) break;
        temp_word = "";
        word = "";
        data = data + " .";
        istringstream iss(data);
        iss >> freq;
        while(1)
        {
            iss >> temp_word;
            if(temp_word == ".") break;
            if(temp_word.length() > 0) word_string.push_back(temp_word);
        }
        for(i = 0; i < word_string.size(); i++)
        {
            if(i > 0) word = word + " ";
            word = word + word_string[i];
        }
        dict.insert(word, freq);
        word_string.clear();
    }
}


void Utils::load_dict(vector<string>& dict, istream& words)
{
    unsigned int junk;
    string data = "";
    string temp_word = "";
    string word = "";
    vector<string> word_string;
    unsigned int i = 0;

    while(getline(words, data))
    {
        if(words.eof()) break;
        temp_word = "";
        word = "";
        data = data + " .";
        istringstream iss(data);
        iss >> junk;
        while(1)
        {
            iss >> temp_word;
            if(temp_word == ".") break;
            if(temp_word.length() > 0) word_string.push_back(temp_word);
        }
        for(i = 0; i < word_string.size(); i++)
        {
            if(i > 0) word = word + " ";
            word = word + word_string[i];
        }
        dict.push_back(word);
        word_string.clear();
    }
}
