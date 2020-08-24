/** Filename: TrieNode.cpp
 *  Name: Loc Chuong
 *  Userid: cs100sp19aj
 *  Description: Defines a TrieNode object used to create the Trie.
 *  Date: 4/29/2019
 */

#include "TrieNode.hpp"
#include "DictionaryTrie.hpp"
#include <iostream>

/** Default constructor
 *  Description: Creates a node with instance variables of zero-like value
 */
TrieNode::TrieNode() : data(0), word(false), freq(0), left(nullptr), right(nullptr), down(nullptr) {
}

/** Constructor
 *  Description: Creaters a TrieNode using the parameter data
 *  Parameters: data - The data held by the node
 */
TrieNode::TrieNode(char data) : data(data), word(false), freq(0) {
    left = right = down = nullptr;
}
