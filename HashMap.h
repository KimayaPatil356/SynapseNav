// ============================================================
// HashMap.h — Custom Hash Map for Fare/Distance Lookup
// ============================================================
//
// DSA Used: HASH TABLE with SEPARATE CHAINING
//
// Purpose: Store and look up fares for routes.
//          Key: route identifier (e.g., "Delhi->Mumbai")
//          Value: fare amount (e.g., 450)
//
// Collision Resolution: SEPARATE CHAINING
//   Each bucket is a linked list (std::list). When two keys
//   hash to the same bucket, they are stored as separate
//   entries in the list.
//
//   bucket[0]: → (key1, val1) → (key2, val2) → nullptr
//   bucket[1]: → (key3, val3) → nullptr
//   bucket[2]: → nullptr  (empty)
//   ...
//
// Hash Function:
//   Uses polynomial rolling hash: hash = sum(c * 31^i) % BUCKETS
//   The multiplier 31 is a prime that gives good distribution.
//   Using a prime number for BUCKET_COUNT reduces clustering.
//
// Template: HashMap<V> allows any value type with string keys.
//
// Time Complexity:
//   - Insert: O(1) average, O(n) worst case (all keys in 1 bucket)
//   - Get:    O(1) average, O(n) worst case
//   - Remove: O(1) average, O(n) worst case
//   - Contains: O(1) average
//
// Space Complexity: O(BUCKET_COUNT + n) where n = number of entries
// ============================================================

#ifndef HASHMAP_H
#define HASHMAP_H

#include <string>
#include <list>
#include <iostream>
#include <iomanip>

using namespace std;

template <typename V>
class HashMap {
private:
    // ============================================================
    // Entry struct — one key-value pair in a bucket chain
    // ============================================================
    struct Entry {
        string key;
        V value;
        Entry(string k, V v) : key(k), value(v) {}
    };

    // Number of buckets — using a PRIME NUMBER for better distribution
    // Prime numbers reduce the chance of patterns in hash values
    // causing systematic collisions.
    static const int BUCKET_COUNT = 53;

    // Array of linked lists (separate chaining)
    list<Entry> buckets[BUCKET_COUNT];

    // Current number of key-value pairs stored
    int currentSize;

    // ============================================================
    // hash — Polynomial Rolling Hash Function
    // ============================================================
    // Formula: hash = (c0 * 31^0 + c1 * 31^1 + ... + cn * 31^n) % BUCKETS
    //
    // WHY 31?
    //   - It's an odd prime, reducing collision probability
    //   - 31 = 2^5 - 1, so the compiler can optimize: 31*x = (x<<5) - x
    //   - Empirically proven to give good distribution for strings
    //
    // WHY unsigned long?
    //   - Prevents negative values from signed overflow
    //   - Allows natural wraparound for large hash values
    // ============================================================
    int hash(const string& key) const {
        unsigned long hashValue = 0;
        for (char c : key) {
            hashValue = hashValue * 31 + c;
        }
        return hashValue % BUCKET_COUNT;
    }

public:
    HashMap() : currentSize(0) {}

    // ============================================================
    // insert — Add or update a key-value pair
    // ============================================================
    // Steps:
    //   1. Compute hash to find the target bucket
    //   2. Search the bucket chain for existing key
    //   3. If found: update value (no duplicate keys allowed)
    //   4. If not found: append new entry to chain
    // ============================================================
    void insert(const string& key, const V& value) {
        int idx = hash(key);

        // Search existing entries in this bucket
        for (auto& entry : buckets[idx]) {
            if (entry.key == key) {
                entry.value = value;  // Update existing entry
                return;
            }
        }

        // Key not found — create new entry
        buckets[idx].push_back(Entry(key, value));
        currentSize++;
    }

    // ============================================================
    // get — Retrieve value by key
    // ============================================================
    // Returns true if key found (value stored in output parameter).
    // Returns false if key not found.
    // ============================================================
    bool get(const string& key, V& value) const {
        int idx = hash(key);
        for (const auto& entry : buckets[idx]) {
            if (entry.key == key) {
                value = entry.value;
                return true;
            }
        }
        return false;  // Key not found
    }

    // ============================================================
    // remove — Delete a key-value pair
    // ============================================================
    bool remove(const string& key) {
        int idx = hash(key);
        for (auto it = buckets[idx].begin(); it != buckets[idx].end(); ++it) {
            if (it->key == key) {
                buckets[idx].erase(it);
                currentSize--;
                return true;
            }
        }
        return false;  // Key not found
    }

    // ============================================================
    // contains — Check if a key exists
    // ============================================================
    bool contains(const string& key) const {
        int idx = hash(key);
        for (const auto& entry : buckets[idx]) {
            if (entry.key == key) return true;
        }
        return false;
    }

    // Get number of stored entries
    int getSize() const { return currentSize; }

    // Check if empty
    bool isEmpty() const { return currentSize == 0; }

    // ============================================================
    // display — Show all key-value pairs
    // ============================================================
    void display() const {
        if (currentSize == 0) {
            cout << "  No fares stored yet." << endl;
            return;
        }

        cout << "\n  ┌─────────────────────────────────────────────┐" << endl;
        cout << "  │           FARE TABLE (" << setw(2) << currentSize << " routes)             │" << endl;
        cout << "  ├─────────────────────────────────────────────┤" << endl;

        for (int i = 0; i < BUCKET_COUNT; i++) {
            for (const auto& entry : buckets[i]) {
                cout << "  │  " << left << setw(30) << entry.key
                     << " Rs." << setw(6) << entry.value << "  │" << endl;
            }
        }

        cout << "  └─────────────────────────────────────────────┘" << endl;
    }
};

#endif // HASHMAP_H
