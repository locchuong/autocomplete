/** Filename: TrieNode.hpp
 *  Name: Loc Chuong
 *  Userid: cs100sp19aj
 *  Description: Defines a TrieNode object used to create the Trie.
 *  Date: 4/29/2019
 */
#ifndef TRIE_NODE_HPP
#define TRIE_NODE_HPP

#include <vector>
#include <string>
#include <queue>

using namespace std;
/** Class Name: TrieNode
 *  Description: Class that defines a TrieNode with certain char data and
 *               pointers to its children(left, right, and down). Used to
 *               create a Ternary Trie.
 */
class TrieNode {
    
    public:
    
        TrieNode * left; /** Pointer to left child */
        TrieNode * right; /** Pointer to right child */
        TrieNode * down; /** Pointer to child directly below it */
        char data; /** Data held by TrieNode */
        bool word; /** True if this creates a word, false otherwise */
        int freq; /** 0 if word is false, otherwise the frequency of word */
                            

        /** Default Constructor
         *  Description: Creates a node with instance variables of zero-like
         *               value
         */
        TrieNode();

        /** Constructor
         *  Description: Creates a TrieNode with data and bool word false
         *  Parameters: data - The data for the TrieNode to hold
         */
        TrieNode(char data);
};

#endif
