// ============================================================
// Trie.cpp — Trie (Prefix Tree) Implementation
// ============================================================

#include "Trie.h"
#include <algorithm>


TrieNode::TrieNode() : isEndOfWord(false), originalWord("") {
    for (int i = 0; i < 26; i++) {
        children[i] = nullptr;
    }
}


Trie::Trie() {
    root = new TrieNode();
}
Trie::~Trie() {
    destroyTrie(root);
}

void Trie::destroyTrie(TrieNode* node) {
    if (!node) return;
    for (int i = 0; i < 26; i++) {
        destroyTrie(node->children[i]);
    }
    delete node;
}

string Trie::toLower(const string& word) const {
    string result = word;
    for (char& c : result) {
        if (c >= 'A' && c <= 'Z') {
            c = c - 'A' + 'a';
        }
    }
    return result;
}


void Trie::insert(const string& word) {
    if (word.empty()) return;

    string lower = toLower(word);  // Case-insensitive
    TrieNode* current = root;

    for (char c : lower) {
        // Skip non-alphabetic characters
        if (c < 'a' || c > 'z') continue;

        int index = c - 'a';  // Map 'a'-'z' to 0-25

        // If child doesn't exist, create a new TrieNode
        if (!current->children[index]) {
            current->children[index] = new TrieNode();
        }

        // Move to the child node
        current = current->children[index];
    }

    // Mark the last node as end of a valid word
    current->isEndOfWord = true;
    current->originalWord = word;  // Preserve original casing
}


bool Trie::search(const string& word) const {
    string lower = toLower(word);
    TrieNode* current = root;

    for (char c : lower) {
        if (c < 'a' || c > 'z') continue;
        int index = c - 'a';
        if (!current->children[index]) {
            return false;  // Character not found — word doesn't exist
        }
        current = current->children[index];
    }

    // We've consumed all characters. But is this a complete word?
    // e.g., searching "Del" in a trie that only has "Delhi" → false
    return current->isEndOfWord;
}

// ============================================================
// searchByPrefix — Find all words matching a prefix
// ============================================================
// Steps:
//   1. Navigate to the node representing the prefix
//   2. From that node, collect ALL words in the subtree
//
// Example: prefix = "De" in trie with [Delhi, Dehradun]
//   1. Navigate: root → [d] → [e]
//   2. Collect: traverse subtree to find "delhi" and "dehradun"
//   3. Return: ["Delhi", "Dehradun"] (original case)
//
// Time: O(P + K) where P = prefix length, K = total output chars
// ============================================================
vector<string> Trie::searchByPrefix(const string& prefix) const {
    vector<string> results;
    string lower = toLower(prefix);
    TrieNode* current = root;

    // Step 1: Navigate to the prefix node
    for (char c : lower) {
        if (c < 'a' || c > 'z') continue;
        int index = c - 'a';
        if (!current->children[index]) {
            return results;  // Prefix not found — no matches
        }
        current = current->children[index];
    }

    // Step 2: Collect all words from this subtree
    collectWords(current, lower, results);

    return results;
}

// ============================================================
// collectWords — Recursive DFS to collect all words in subtree
// ============================================================
// Performs a depth-first traversal of the trie subtree,
// building up the word character by character.
// When we hit isEndOfWord, add the original word to results.
// ============================================================
void Trie::collectWords(TrieNode* node, string prefix, vector<string>& results) const {
    if (!node) return;

    // If this node marks the end of a word, add it
    if (node->isEndOfWord) {
        results.push_back(node->originalWord);
    }

    // Recurse into all existing children (a-z order = alphabetical)
    for (int i = 0; i < 26; i++) {
        if (node->children[i]) {
            char c = 'a' + i;
            collectWords(node->children[i], prefix + c, results);
        }
    }
}

// ============================================================
// remove — Remove a word from the trie
// ============================================================
// Simple approach: just unmark isEndOfWord.
// The nodes remain in the trie but the word is no longer valid.
// (Full branch pruning is more complex and not needed here)
// ============================================================
void Trie::remove(const string& word) {
    string lower = toLower(word);
    TrieNode* current = root;

    for (char c : lower) {
        if (c < 'a' || c > 'z') continue;
        int index = c - 'a';
        if (!current->children[index]) return;  // Word not found
        current = current->children[index];
    }

    // Unmark end-of-word (soft delete)
    current->isEndOfWord = false;
    current->originalWord = "";
}

// ============================================================
// displayAll — Show all words stored in the trie
// ============================================================
void Trie::displayAll() const {
    vector<string> allWords;
    collectWords(root, "", allWords);

    if (allWords.empty()) {
        cout << "  Trie is empty. No cities stored." << endl;
        return;
    }

    // Sort alphabetically
    sort(allWords.begin(), allWords.end());
    cout << "  Cities in Trie (" << allWords.size() << " total):" << endl;
    for (const string& word : allWords) {
        cout << "    • " << word << endl;
    }
}
