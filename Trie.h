// ============================================================
// Trie.h — Prefix Tree for City Name Search
// ============================================================
//
// DSA Used: TRIE (Prefix Tree)
//
// Purpose: Efficiently search for cities by name prefix.
//          e.g., typing "De" suggests "Delhi"
//
// Structure:
//   Each TrieNode has 26 children (a-z). A path from root
//   to a node spells out a prefix. Nodes marked isEndOfWord
//   indicate complete city names.
//
//   Example for cities: Delhi, Dehradun
//         root
//          |
//         [d]
//          |
//         [e]
//        /    (branch)
//      [l]    [h]
//       |      |
//      [h]    [r]
//       |      |
//      [i]*   [a]   (* = end of word "delhi")
//              |
//             [d]
//              |
//             [u]
//              |
//             [n]*  (* = end of word "dehradun")
//
// Time Complexity:
//   - Insert: O(L) where L = length of word
//   - Search: O(L)
//   - Prefix search: O(L + K) where K = total chars in matches
//
// Space Complexity: O(ALPHABET_SIZE * L * N) worst case
//                   where N = number of words
// ============================================================

#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

// ============================================================
// TrieNode — One node in the prefix tree
// ============================================================
class TrieNode {
public:
    TrieNode* children[26];   // Pointers to child nodes (a-z)
    bool isEndOfWord;          // Marks the end of a valid word
    string originalWord;       // Stores the original (case-preserved) name

    TrieNode();
};

// ============================================================
// Trie — The prefix tree class
// ============================================================
class Trie {
private:
    TrieNode* root;

    // Recursive helper: collect all words in subtree
    void collectWords(TrieNode* node, string prefix, vector<string>& results) const;

    // Recursive helper: destroy trie (free memory)
    void destroyTrie(TrieNode* node);

    // Helper: convert string to lowercase for case-insensitive search
    string toLower(const string& word) const;

public:
    Trie();
    ~Trie();

    // Insert a city name into the trie
    void insert(const string& word);

    // Check if an exact word exists
    bool search(const string& word) const;

    // Find all cities matching a prefix (e.g., "De" → ["Delhi", "Dehradun"])
    vector<string> searchByPrefix(const string& prefix) const;

    // Remove a word from the trie
    void remove(const string& word);

    // Display all words in the trie (alphabetical order)
    void displayAll() const;
};

#endif // TRIE_H
