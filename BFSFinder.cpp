// ============================================================
// BFSFinder.cpp — BFS (Breadth-First Search) Implementation
// ============================================================
//
// DSA Used: BFS (Breadth-First Search) + QUEUE
//
// Purpose: Find the path with MINIMUM NUMBER OF STOPS between
//          source and destination (ignores edge weights).
//
// Algorithm Steps:
//   1. Start from source, mark as visited, push to queue
//   2. While queue is not empty:
//      a. Dequeue front node (FIFO order)
//      b. If it's the destination, stop
//      c. For each unvisited neighbor, mark visited,
//         record parent, and enqueue
//   3. Reconstruct path using parent pointers
//
// WHY BFS finds minimum stops:
//   BFS explores nodes LEVEL BY LEVEL (distance 1, then 2, ...).
//   The first time we reach the destination, we've found the
//   path with the FEWEST edges (stops). This is guaranteed
//   because BFS explores all k-hop neighbors before any
//   (k+1)-hop neighbors.
//
// Key Difference from Dijkstra:
//   - Dijkstra minimizes TOTAL WEIGHT (distance in km)
//   - BFS minimizes NUMBER OF EDGES (stops/transfers)
//
// Time Complexity:  O(V + E)
// Space Complexity: O(V) for visited set, parent map, queue
// ============================================================

#include "BFSFinder.h"
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <iostream>

vector<string> BFSFinder::findPath(const TransportNetwork& network,
                                    const string& src,
                                    const string& dest) {

    // ── Step 1: Initialize data structures ──────────────────

    // parent[city] = previous city on the shortest path
    unordered_map<string, string> parent;

    // visited set — ensures each node is processed only once
    unordered_set<string> visited;

    // ── Step 2: Queue for BFS traversal ─────────────────────
    // WHY QUEUE?
    //   BFS uses FIFO (First In, First Out) order to ensure
    //   level-by-level exploration. Nodes at distance k are
    //   processed before nodes at distance k+1.
    queue<string> q;

    // Start BFS from source
    visited.insert(src);
    q.push(src);

    bool found = false;

    // ── Step 3: Main BFS Loop ───────────────────────────────
    while (!q.empty()) {
        // Dequeue the front node (FIFO)
        string u = q.front();
        q.pop();

        // Check if we've reached the destination
        if (u == dest) {
            found = true;
            break;
        }

        // ── Step 4: Explore all neighbors ───────────────────
        // getNeighbors() automatically filters blocked routes
        for (const auto& [v, w] : network.getNeighbors(u)) {
            // Only process unvisited neighbors
            if (!visited.count(v)) {
                visited.insert(v);   // Mark as visited BEFORE enqueueing
                parent[v] = u;       // Record parent for path reconstruction
                q.push(v);           // Enqueue for future processing
            }
        }
        // Note: We mark nodes as visited when ENQUEUEING, not when
        // DEQUEUEING. This prevents the same node from being added
        // to the queue multiple times, saving time and space.
    }

    // ── Step 5: Reconstruct the path ────────────────────────
    vector<string> path;

    // If destination was never reached, return empty path
    if (!found && !visited.count(dest)) {
        return path;
    }

    // Build path in reverse: dest → ... → src
    string current = dest;
    while (current != src) {
        path.push_back(current);
        if (parent.find(current) == parent.end()) {
            return vector<string>();  // No path (shouldn't happen if found=true)
        }
        current = parent[current];
    }
    path.push_back(src);

    // Reverse to get: src → ... → dest
    reverse(path.begin(), path.end());

    return path;
}

string BFSFinder::getAlgorithmName() const {
    return "BFS (Minimum Stops)";
}
