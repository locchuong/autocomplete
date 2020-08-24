# autocomplete
## Description
The main focus of this repo is to demonstrate the autocomplete function used search engines, spell-checking, text-messengers, etc. In addition, this repo explores a bloom filter that provides memory efficient check of whether an item has been inserted before through the use of hashing algorithms (FNV1AHash, CRCHash, and SBDMHash).

## Data Structures
### Trie (TST)
* This provided data structure is my own implementation of the Ternary Search Trie. In addition to the `insert` and `find` methods, the dictionarytrie class implements a `predictCompletions` method which does the bulk of the auto-complete feature. `predictCompletions` takes in *prefix* and *num_completions* and returns the words beginning with *prefix* up to *num_completions* (If there are fewer words than *num_completions*, this method will return as many completions as possible. Additionally, there is the `predictUnderscore` method which takes in a string with an underscore in it and finds the words which complete the string. `predictUnderscore` takes in *pattern* and *num_completions*, similar to `predictCompletions`. Note that both `predictCompletions` and `predictUnderscore` will return the words from most common to least common.
## Usage
The program itself will take in a text document as the one and only argument that is formatted in such a way in which each line starts with a frequency followed by a space and the word. 

Below is an example stdout from using autocomplete
```
./autocomplete unique_freq_dict.txt
Reading file: unique_freq_dict.txt
Enter a prefix/pattern to search for:
hel_
Enter a number of completions:
100
help
hell
held
helt
helo
helm
hele
hela
Continue? (y/n)
y
Enter a prefix/pattern to search for:
hello
Enter a number of completions:
10
hello
hellos
helloed
helloes
helloing
helloooo
hellooo
helloo
Continue? (y/n)
n
```
