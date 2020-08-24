/** Filename: DictionaryTrie.hpp
 *  Name: Loc Chuong
 *  Userid: cs100sp19aj
 *  Description: The class for a dictionary ADT, implented as a Trie (TST).
 *               Some functionality include the autocomplete where user may
 *               enter a prefix or pattern in which a vector of strings
 *               fitting the description will be returned.
 *  Date: 4/29/2019
 */

#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include "TrieNode.hpp"
#include <vector>
#include <string>
#include <queue>
#define UNDERSCORE '_'

using namespace std;

/** Declares a struct Word used to hold a string and its frequency in the TST
*/
struct Word;

/** Class Name: DictionaryTrie
 *  Description: The class for a dictionary ADT, implented as a Trie (TST) 
 */
class DictionaryTrie
{
    public:

        /** Constructor
         *  Description: Create a new Dictionary that uses a Trie back end
         */
        DictionaryTrie();

        /** Function Name: insert(std::string word, unsigned int freq)
         *  Description: Insert a word with its frequency into the dictionary
         *  Parameters: word - The word to insert into the dictionary
         *              freq - The frequency of the word to insert into the
         *                     dictionary
         *  Return Value: Return true if the word was inserted, and false if it
         *                was not (i.e. it was already in the dictionary or it
         *                was invalid (empty string). This might be useful for
         *                testing when you want to test a certain case, but
         *                don't want to write out a specific word 300 times.
         */
        bool insert(std::string word, unsigned int freq);

        /** Function Name: find(std::string word)
         *  Description: Finds if a word is in the dictionary
         *  Parameters: The word to find in the dictionary (The TST)
         *  Return Value: Return true if word is in the dictionary, and false
         *                otherwise
         */
        bool find(std::string word) const;

        /** Function Name: predictCompletions(std::string prefix,
         *                      unsigned int num_completions) 
         *  Description: Return up to num_completions of the most frequent
         *               completions of the prefix, such that the completions
         *               are words in the dictionary. These completions should
         *               be listed from most frequent to least. If there are
         *               fewer than num_completions legal completions, this
         *               function returns a vector with as many completions as
         *               possible. If no completions exist, then the function
         *               returns a vector of size 0. The prefix itself might be
         *               included in the returned words if the prefix is a word
         *               (and is among the num_completions most frequent
         *               completions of the prefix)
         * Parameters: prefix - The prefix of any word to be searched
         *             num_completions - The number of words to find with the
         *                               prefix
         * Return Value: A vector of strings of words that have the prefix
         */
        std::vector<std::string> predictCompletions(std::string prefix,
                unsigned int num_completions);

        /* Function Name: predictUnderscore(std::string pattern, unsigned int
         *                      num_completions)
         * Description: Return up to num_completions of the most frequent
         *              completions of the pattern, such that the completions
         *              are words in the dictionary. These completions should
         *              be listed from most frequent to least. If there are
         *              fewer than num_completions legal completions, this
         *              function returns a vector with as many completions as
         *              possible. If no completions exist, then the function
         *              returns a vector of size 0. The pattern itself might
         *              be included in the returned words if the pattern is a
         *              word (and is among the num_completions most frequent
         *              completions of the pattern)
         * Parameters: pattern - The pattern to find in the TST
         *             num_completions - The number of words to find via the
         *                               pattern
         * Return Value: A vector of strings with words that are apart of the
         *               pattern
         */
        std::vector<std::string> predictUnderscore(std::string pattern,
                unsigned int num_completions);

        /* Destructor
         * Description: Deletes the tree nodes
         */
        ~DictionaryTrie();

    private:

        TrieNode * root; /** Root of TernaryTrie */
        unsigned int isize; /** Size of Ternary Trie */
        unsigned int iheight; /** Height of Ternary Trie */

        /** Function Name: insert(std::string word, unsigned int freq,
         *                      TrieNode * & root, unsigned int height)
         *  Description: Private instance helper to insert. Insert a word with
         *               its frequency into the dictionary.
         *  Parameters: word - The word to insert into the dictionary
         *              freq - The frequency of the word to insert into the
         *                     dictionary
         *              root - A pointer reference to the root of the TST
         *              height - height of the TST, used to determine new
         *                       height and as the index of the word
         *  Return Value: Return true if the word was inserted, and false if it
         *                was not (i.e. it was already in the dictionary or it
         *                was invalid (empty string). This might be useful for
         *                testing when you want to test a certain case, but
         *                don't want to write out a specific word 300 times.
         */
        bool insert(std::string word, unsigned int freq, TrieNode * & root,
                unsigned int height);

        /** Function Name: find(std::string word, TrieNode * root,
         *                      unsigned int height) const
         *  Description: Helper to the public find(std::string word) function.
         *               Finds if a word is in the dictionary. True if word is
         *               in the dictionary, false otherwise.
         *  Parameters: word - The word to find in the Trie
         *              root - The root of the Trie
         *              height - The height of the Trie
         *  Return Value: True if word is in the dictionary, false otherwise
         */
        bool find(std::string word, TrieNode *root, unsigned int height) const;

        /** Function Name: findNode(std::string prefix, TrieNode * currNode,
         *                      unsigned int height)
         *  Description: Used to find the node corresponding to the ending char
         *               in prefix in TST
         *  Parameters: prefix - The string used to search the dictionary with
         *              currNode - Presumed to be the root pointer
         *              height - Height of tree, also used as index of prefix
         *  Return Value: A pointer to the node corresponding to the ending
         *                char in prefix
         */
        TrieNode* findNode(std::string prefix, TrieNode * currNode,
                unsigned int height);

        /** Function Name: findCompletions(std::string prefix,
         *                      unsigned int num_completions,
         *                      TrieNode * currNode,
         *                      std::vector<Word> * wordNodes)
         *  Description: Used to find all the words starting form the currNode
         *  Parameters: prefix - The prefix of any searched word
         *              num_completions - The number of words to find
         *              currNode - A node pointer used to traverse the trie
         *              wordNodes - A vector of Words with prefix in its word
         */
        void findCompletions(std::string prefix, unsigned int num_completions,
                TrieNode * currNode,
                std::priority_queue<Word,vector<Word>,Word> & wordNodes);

        /* Function Name: findUnderscore(std::string pattern,
         *                      std::string prefix, std::string postUnderscore,
         *                      TrieNode * currNode, 
         *                      unsigned int num_completions,
         *                      std::priority_queue<Word,vector<Word>,Word> &
         *                      wordNodes);
         * Description: Pushes up to num_completions of the most frequent
         *              completions of the pattern, such that the completions
         *              are words in the dictionary to the parameter wordNodes
         * Parameters: pattern - The pattern to find in the TST
         *             prefix - The prefix to look for in the TST
         *             postUnderscore - The string after the underscore char
         *             currNode - A pointer used to traverse the tree
         *             num_completions - The number of words to find via the
         *                               pattern
         *             wordNodes - Vector holding the predictions from pattern
         * Return Value: None
         */
        void findPattern(std::string pattern, std::string prefix,
                std::string postUnderscore, TrieNode * currNode,
                unsigned int num_completions,
                std::priority_queue<Word,vector<Word>,Word> & wordNodes);

        /** Function Name: deleteTrie(TrieNode * currNode)
         *  Description: Helper to delete the tree from the root node
         */
        void deleteTrie(TrieNode * currNode);
};

#endif // DICTIONARY_TRIE_H
