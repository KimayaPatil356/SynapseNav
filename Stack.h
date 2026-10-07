// ============================================================
// Stack.h — Template Stack for Recent Searches
// ============================================================
//
// DSA Used: STACK (LIFO — Last In, First Out)
//
// Purpose: Store the last N recently searched routes.
//          When the user searches for a route, push it.
//          When the stack exceeds max capacity, the OLDEST
//          search is removed (sliding window behavior).
//
// Template: Stack<T> allows storing any data type.
//           Here we use Stack<string> for route descriptions.
//
// Implementation: Uses a vector as the underlying container.
//   - push(): Add to back. If full, remove from front (oldest).
//   - pop():  Remove and return from back (newest).
//   - top():  Peek at back (newest) without removing.
//
// Time Complexity:
//   - push: O(1) amortized (O(n) when removing oldest)
//   - pop:  O(1)
//   - top:  O(1)
// ============================================================

#ifndef STACK_H
#define STACK_H

#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class Stack {
private:
    vector<T> data;    // Underlying storage
    int maxSize;       // Maximum number of elements to keep

public:
    // Constructor: default max size is 5 (last 5 searches)
    Stack(int maxSize = 5) : maxSize(maxSize) {}

    // ============================================================
    // push — Add an element to the top of the stack
    // ============================================================
    // If stack is at max capacity, remove the OLDEST element (front)
    // to maintain a sliding window of recent searches.
    // This is a slight modification of the classic stack to support
    // the "recent history" feature with bounded memory.
    // ============================================================
    void push(const T& item) {
        // If at capacity, remove the oldest element (front of vector)
        if ((int)data.size() >= maxSize) {
            data.erase(data.begin());
        }
        // Add new element to the top (back of vector)
        data.push_back(item);
    }

    // ============================================================
    // pop — Remove and return the top (newest) element
    // ============================================================
    T pop() {
        if (isEmpty()) {
            throw runtime_error("Stack Underflow: Cannot pop from empty stack!");
        }
        T item = data.back();
        data.pop_back();
        return item;
    }

    // ============================================================
    // top — Peek at the top element without removing it
    // ============================================================
    T top() const {
        if (isEmpty()) {
            throw runtime_error("Stack is empty: Cannot peek!");
        }
        return data.back();
    }

    // Check if stack is empty
    bool isEmpty() const {
        return data.empty();
    }

    // Get current number of elements
    int size() const {
        return data.size();
    }

    // Get maximum capacity
    int capacity() const {
        return maxSize;
    }

    // ============================================================
    // display — Show all elements (newest first)
    // ============================================================
    // Iterates from back to front (top to bottom of stack),
    // displaying the most recent search first.
    // ============================================================
    void display() const {
        if (isEmpty()) {
            cout << "  No recent searches yet." << endl;
            return;
        }

        cout << "\n  ╔═══════════════════════════════════════════════╗" << endl;
        cout << "  ║        RECENT SEARCHES (Last " << maxSize << ")              ║" << endl;
        cout << "  ╠═══════════════════════════════════════════════╣" << endl;

        // Display from newest to oldest (back to front)
        for (int i = data.size() - 1; i >= 0; i--) {
            cout << "  ║  " << (data.size() - i) << ". " << data[i];
            // Pad with spaces for alignment
            int padding = 42 - (int)data[i].length();
            if (padding > 0) {
                for (int j = 0; j < padding; j++) cout << " ";
            }
            cout << "║" << endl;
        }

        cout << "  ╚═══════════════════════════════════════════════╝" << endl;
    }

    // Clear all elements
    void clear() {
        data.clear();
    }
};

#endif // STACK_H
