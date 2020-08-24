/** Filename: DictionaryTrie.cpp
 *  Name: Loc Chuong
 *  Userid: cs100sp19aj
 *  Description: This file defines the Trie used to store words as a
 *               dictionary. Additional functionalities include the
 *               autocomplete function, inserting a word into the TST, and
 *               finding if a word is in the TST.
 *  Date: 5/2/2019
 */

#include "util.hpp"
#include "TrieNode.hpp"
#include "DictionaryTrie.hpp"
#include <iostream>
#include <algorithm>
#include <string>

/** Struct Word
 *  Description: Used to hold a string and its frequency in the TST
 */
struct Word {

    int freq; /** Frequency of the string s in the TST */
    string s; /** The string created by traversing the TST */

    /** Default construct
     *  Description: Initializes s and freq to zero-like values
     */
    Word() : freq(0), s() {}

    /** Constructor
     *  Description: Initalizes instance variables s and freq to the passed
     *               in parameters s and freq
     */
    Word(const string s, const unsigned int freq) {
        this->s = s;
        this->freq = freq;
    }

    /** Operator()
     *  Description: Used to compare two Word structs based first on freq,
     *               but if freq is the same, then it is based alphabetically
     *  Return Value: True if w1 is less than w2, False otherwise
     */
    bool operator() (const Word & w1, const Word & w2) {
        /** Frequency is the same, sort by alphabetical order */
        if( w1.freq == w2.freq) {
            return w1.s < w2.s;
        }
        /** Frequency differ, sort by frequency */
        return w1.freq > w2.freq;
    }
};

/** Constructor
 *  Description: Create a new Dictionary that uses a Trie back end
 */
DictionaryTrie::DictionaryTrie() : root(nullptr), isize(0), iheight(0) {
}

/** Function Name: insert(std::string word, unsigned int freq)
 *  Description: Insert a word with its frequency into the dictionary
 *  Parameters: word - The word to insert into the dictionary
 *              freq - The frequency of the word to insert into the dictionary
 *  Return Value: Return true if the word was inserted, and false if it
 *                was not (i.e. it was already in the dictionary or it was
 *                invalid (empty string). This might be useful for testing
 *                when you want to test a certain case, but don't want to
 *                write out a specific word 300 times.
 */
bool DictionaryTrie::insert(std::string word, unsigned int freq) {
    /** Delegates to private instance of insert */
    return insert(word, freq, root, 0);
}

/** Function Name: insert(std::string word, unsigned int freq,
 *                      TrieNode * & root, unsigned int height)
 *  Description: Private instance helper to insert. Insert a word with its
 *               frequency into the dictionary.
 *  Parameters: word - The word to insert into the dictionary
 *              freq - The frequency of the word to insert into the dictionary
 *              root - A pointer reference to the root of the TST
 *              height - height of the TST, used to determine new height and
 *                       as the index of the word
 *  Return Value: Return true if the word was inserted, and false if it
 *                was not (i.e. it was already in the dictionary or it was
 *                invalid (empty string). This might be useful for testing
 *                when you want to test a certain case, but don't want to
 *                write out a specific word 300 times.
 */
bool DictionaryTrie::insert(std::string word, unsigned int freq,
        TrieNode * & root, unsigned int height) {
    /** Base Case: current node is null */
    if( root == nullptr) {
        /** Create new node for corresponding char in word */
        root = new TrieNode(word[height]);
    }
    /** Current character greater than current node's char */
    if (word[height] > root->data) {
        /** Traverse right with current height (Keep current char) */
        return insert(word, freq, root->right, height);
    }
    /** Current character less than current node's char */
    else if (word[height] < root->data) {
        /** Traverse left with current height (Keep current char) */
        return insert(word, freq, root->left, height);
    }
    /** Current character is equal to current node's char */
    else {
        /** There exists another character in word */
        if(height+1 < word.size()) {
            /** Traverse down with height + 1 (Use next char in word) */
            return insert(word, freq, root->down, height+1);
        }
        /** There does not exist another character in word */
        else {
            /** Word is already in Trie, don't add it */
            if( root->word) {
                return false;
            }
            /** Word not in Trie, add it */
            else {
                /** Current node is a word node, set instance variables */
                root->word = true;
                root->freq = freq;
                if( iheight < height) {
                    iheight = height;
                }
                return true;
            }
        }
    }
    return false;
}

/** Function Name: find(std::string word)
 *  Description: Finds if a word is in the dictionary
 *  Parameters: The word to find in the dictionary (The TST)
 *  Return Value: Return true if word is in the dictionary, and false otherwise
 */
bool DictionaryTrie::find(std::string word) const {
    /** Delegates to private instance of find */
    return find(word, root, 0);
}

/** Function Name: find(std::string word, TrieNode * root, unsigned int height)
 *                      const
 *  Description: Helper to the public find(std::string word) function. Finds
 *               if a word is in the dictionary. True if word is in the
 *               dictionary, false otherwise.
 *  Parameters: word - The word to find in the Trie
 *              root - The root of the Trie
 *              height - The height of the Trie
 *  Return Value: True if word is in the dictionary, false otherwise
 */
bool DictionaryTrie::find(std::string word, TrieNode * root,
        unsigned int height) const {
    /** Letters of word were not found in TST, not found */
    if( root == nullptr) {
        return false;
    }
    /** Traverse to right child */
    if (word[height] > root->data) {
        return find(word, root->right, height);
    }
    /** Traverse to left child */
    else if (word[height] < root->data) {
        return find(word, root->left, height);
    }
    /** Traverse to child below it (Letter found) */
    else {
        /** Check if there exists another letter in the word to find */
        if( height+1 < word.size()) {
            return find(word, root->down, height+1);
        }
        /** Word may be in TST or just a prefix to a word in the TST */
        else {
            /** Word is found in TST*/
            if( root->word) {
                return true;
            }
            /** Word was just a prefix in TST, not found */
            else {
                return false;
            }
        }
    }
    return false;
}

/** Function Name: findNode(std::string prefix, TrieNode * currNode,
 *                      unsigned int height)
 *  Description: Used to find the node corresponding to the ending char in
 *               prefix in TST
 *  Parameters: prefix - The string used to search the dictionary with
 *              currNode - Presumed to be the root pointer
 *              height - Height of tree, also used as index of prefix
 *  Return Value: A pointer to the node corresponding to the ending char in
 *                prefix
 */
TrieNode* DictionaryTrie::findNode(std::string prefix, TrieNode * currNode, 
        unsigned int height) {
    /** Base Case: Current node is nullptr */
    if( currNode == nullptr) {
        return nullptr;
    }
    /** Traverse to right child */
    if(prefix[height] > currNode->data) {
        return findNode(prefix, currNode->right, height);
    }
    /** Traverse to left child */
    else if (prefix[height] < currNode->data) {
        return findNode(prefix, currNode->left, height);
    }
    else {
        /** Check if there exists another letter in the word to find */
        if( height+1 < prefix.size()) {
            return findNode(prefix, currNode->down, height+1);
        }
        /** Found the prefix node, return it */
        else  {
            return currNode;
        }
    }
}
/** Function Name: findCompletions(std::string prefix,
 *                      unsigned int num_completions, TrieNode * currNode,
 *                      std::vector<Word> * wordNodes)
 *  Description: Used to find all the words starting form the currNode
 *  Parameters: prefix - The prefix of any searched word
 *              num_completions - The number of words to find
 *              currNode - A node pointer used to traverse the trie
 *              wordNodes - A vector of Words with prefix in its word
 */
void DictionaryTrie::findCompletions(std::string prefix,
        unsigned int num_completions, TrieNode * currNode,
        std::priority_queue<Word,vector<Word>,Word> & wordNodes) {
    /** Base Case: Return if the current node does not exist */
    if( currNode == nullptr) {
        return;
    }
    /** Adds the word if the current node is a word node */
    if( currNode->word == true) {
        /** wordNodes is full */
        if( wordNodes.size() == num_completions) {
            /** Sort alphabetically if freq is the same, otherwise by freq */
            if( (wordNodes.top().freq == currNode->freq && 
                        wordNodes.top().s > prefix+currNode->data) || 
                    (wordNodes.top().freq < currNode->freq)) {
                /** Pop top (lowest in freq and alpha) element */
                wordNodes.pop();
                /** Push new (higher than prev lowest) element */
                wordNodes.push(Word(prefix+currNode->data, currNode->freq));
            }
        }
        /** Push if wordNodes is not of size num_completions yet */
        else {
            wordNodes.push(Word(prefix+currNode->data, currNode->freq));
        }
    }
    /** Traverse down the tree */
    if( currNode->down != nullptr) {
        findCompletions(prefix+currNode->data, num_completions, currNode->down,
                wordNodes);
    }
    /** Traverse right of the current node */
    if( currNode->right != nullptr) {
        findCompletions(prefix, num_completions, currNode->right, wordNodes);
    }
    /** Traverse left of the current node */
    if( currNode->left != nullptr) {
        findCompletions(prefix, num_completions, currNode->left, wordNodes);
    }
}

/** Function Name: predictCompletions(std::string prefix,
 *                      unsigned int num_completions) 
 *  Description: Return up to num_completions of the most frequent completions
 *               of the prefix, such that the completions are words in the
 *               dictionary. These completions should be listed from most
 *               frequent to least. If there are fewer than num_completions
 *               legal completions, this function returns a vector with as
 *               many completions as possible. If no completions exist, then
 *               the function returns a vector of size 0. The prefix itself
 *               might be included in the returned words if the prefix is a
 *               word (and is among the num_completions most frequent
 *               completions of the prefix)
 * Parameters: prefix - The prefix of any word to be searched
 *             num_completions - The number of words to find with the prefix
 * Return Value: A vector of strings of words that have the prefix
 */
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix,
        unsigned int num_completions) {
    /** Find the node corresponding to the last char in the prefix */
    TrieNode * currNode = findNode(prefix, root, 0);
    /** Handles the case where the prefix is not in the tree */
    if( currNode == nullptr || num_completions == 0) {
        return {};
    }
    /** Create a vector of TrieNode pointers to hold potential candidates */
    std::priority_queue<Word, vector<Word>, Word> wordNodes;
    /** Determine if the prefix is a word, if so add it, else don't add it */
    if( currNode->word == true) {
        wordNodes.push(Word(prefix, currNode->freq));
    }
    /** Move down to include the prefix regardless if it is a word */
    currNode = currNode->down;
    /** Find predictions and place them into wordNodes */
    findCompletions(prefix, num_completions, currNode, wordNodes);
    /** Initialize size of return vector */
    unsigned int size = num_completions;
    /** Adjust size of return vector if we found less words */
    if( wordNodes.size() < num_completions) {
        size = wordNodes.size();
    }
    /** Create vector of strings to hold completions */
    std::vector<std::string> predictions(size);
    /** Transfer strings from vector of Word struct to vector of completions */
    for( int i = size-1; i >= 0 ; i--) {
        /** Grab lowest freq/alphabetic element to highest index in vector */
        predictions[i] = wordNodes.top().s;
        /** Pop lowest freq/alphabetic element in vector  of Word struc */
        wordNodes.pop();
    }
    return predictions;
}

/* Function Name: findPattern(std::string pattern, std::string prefix,
 *                      std::string postUnderscore, TrieNode * currNode, 
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
 *             num_completions - The number of words to find via the pattern
 *             wordNodes - Vector holding the predictions from pattern
 * Return Value: None
 */
void DictionaryTrie::findPattern(std::string pattern, std::string prefix,
        std::string postUnderscore, TrieNode * currNode,
        unsigned int num_completions, 
        std::priority_queue<Word,vector<Word>,Word> & wordNodes) {
    /** Base Case: Return if the current node does not exist */
    if( currNode == nullptr) {
        return;
    }
    /** Adds word if it is a word, of correct size, and matches the pattern */
    if( currNode->word == true &&
            (prefix+currNode->data).size() == pattern.size() &&
            (prefix+currNode->data).substr(pattern.find(UNDERSCORE)+1,
                string::npos) == postUnderscore) {
        /** Push word to priority queue */
        wordNodes.push(Word(prefix+currNode->data, currNode->freq));
    }
    /** Traverse down the tree */
    if( currNode->down != nullptr) {
        findPattern(pattern, prefix+currNode->data, postUnderscore, 
                currNode->down, num_completions, wordNodes);
    }
    /** Traverse right of the current node */
    if( currNode->right != nullptr) {
        findPattern(pattern, prefix, postUnderscore, 
                currNode->right, num_completions, wordNodes);
    }
    /** Traverse left of the current node */
    if( currNode->left != nullptr) {
        findPattern(pattern, prefix, postUnderscore, 
                currNode->left, num_completions, wordNodes);
    }
}

/* Function Name: predictUnderscore(std::string pattern, unsigned int
 *                      num_completions)
 * Description: Return up to num_completions of the most frequent completions
 *              of the pattern, such that the completions are words in the
 *              dictionary. These completions should be listed from most
 *              frequent to least. If there are fewer than num_completions
 *              legal completions, this function returns a vector with as many
 *              completions as possible. If no completions exist, then the
 *              function returns a vector of size 0. The pattern itself might
 *              be included in the returned words if the pattern is a word 
 *              (and is among the num_completions most frequent completions
 *              of the pattern)
 * Parameters: pattern - The pattern to find in the TST
 *             num_completions - The number of words to find via the pattern
 * Return Value: A vector of strings with words that are apart of the pattern
 */
std::vector<string> DictionaryTrie::predictUnderscore(std::string pattern,
        unsigned int num_completions) {
    /** Validity test for num_completions */
    if( num_completions == 0 || pattern.empty()) {
        return {};
    }
    /** Finds the index at which the underscore is in the string */
    unsigned int underScoreIdx = pattern.find(UNDERSCORE);
    /** Create string to hold chars before the underscore, acts as a prefix */
    string preUnderscore = pattern.substr(0, underScoreIdx);
    /** Create string to hold chars after the underscore */
    string postUnderscore;
    /** Finds the string after the underscore */
    if( underScoreIdx+1 < pattern.size()) {
        postUnderscore = pattern.substr(underScoreIdx+1, string::npos);
    }
    /** Create node pointer to find predictions */
    TrieNode * currNode;
    /** Underscore was the first character in the pattern */
    if( preUnderscore.empty()) {
        /** Set starting node to search as root */
        currNode = root; 
    }
    /** Find the starting node to search with characters before underscore */
    else {
        /** Node is set to the node corresponding to char before underscore */
        currNode = findNode(preUnderscore, root, 0);
    }
    /** Did not find the characters before underscore in tree */
    if( currNode == nullptr) {
        return {};
    }
    /** Take in the node corresponding to the first char before underscore */
    currNode = currNode->down;
    /** Create priority queue to hold and sort predictions */
    std::priority_queue<Word, vector<Word>, Word> wordNodes;
    /** Handles finding predictions for when underscore is the first char */
    if( underScoreIdx == 0) {
        /** Set current node to the root node */
        currNode = root;
        findPattern(pattern, preUnderscore, postUnderscore, currNode,
                num_completions, wordNodes);
    }
    /** Handles finding predictions for underscore is not the first char */
    else {
        findPattern(pattern, preUnderscore, postUnderscore, currNode,
                num_completions, wordNodes);
    }
    /** Holds size of the vector to hold predictions */
    unsigned int size = num_completions;
    /** Int representing the diff in sizes of words found and words printed */
    int diff = 0;
    /** Found less elem than num_completions, size is how much we found*/
    if( wordNodes.size() < num_completions) {
        /** New size of return vector is wordNode's size */
        size = wordNodes.size();
    }
    /** Found more/equal to num_completions elem, size is num_completions */
    else {
        /** Find the number of elements to pop */
        diff = wordNodes.size()-num_completions;
        /** Pop elements not printed out to user */
        for( int i = 0; i < diff; i++) {
            wordNodes.pop();
        }
    }
    /** Create vector to hold final strings printed to user */
    std::vector<std::string> predictions(size);
    /** Transfer strings from priority queue to vector */
    for( int i = size-1; i >= 0; i--) {
        /** Set last element in predictions to be smallest element */
        predictions[i] = wordNodes.top().s;
        /** Pop smallest element from priority queue */
        wordNodes.pop();
    }
    return predictions;
}

/** Function Name: deleteTrie(TrieNode * currNode)
 *  Description: Helper to delete the tree from the root node
 */
void DictionaryTrie::deleteTrie(TrieNode * currNode) {
    /** Recursively traverse down the tree and delete all nodes */
    if(currNode != nullptr) {
        deleteTrie(currNode->left);
        deleteTrie(currNode->right);
        deleteTrie(currNode->down);
        delete currNode;
    }
}

/* Destructor
 * Description: Deletes the tree nodes
 */
DictionaryTrie::~DictionaryTrie() {
    deleteTrie(root);
}
