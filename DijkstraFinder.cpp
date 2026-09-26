// ============================================================
// DijkstraFinder.cpp — Dijkstra's Algorithm Implementation
// ============================================================
//
// DSA Used: DIJKSTRA'S ALGORITHM + MIN-HEAP (Priority Queue)
//
// Purpose: Find the shortest path by TOTAL DISTANCE between
//          a source and destination city.
//
// Algorithm Steps:
//   1. Initialize all distances to INF, source distance to 0
//   2. Use a min-heap (priority_queue) to always process the
//      node with the SMALLEST cumulative distance first
//   3. For each node, relax all its neighbors:
//      if (dist[u] + weight(u,v) < dist[v]) → update dist[v]
//   4. Track parent pointers to reconstruct the path
//   5. Stop when destination is reached
//
// Data Structures Used:
//   - priority_queue (min-heap): O(log V) for push/pop
//   - unordered_map<string, int>: distance from source
//   - unordered_map<string, string>: parent pointers for path
//   - unordered_set<string>: visited set
//
// Time Complexity:  O((V + E) * log V) with min-heap
// Space Complexity: O(V) for dist, parent, visited maps
// ============================================================

#include "DijkstraFinder.h"
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <climits>
#include <algorithm>
#include <iostream>

vector<string> DijkstraFinder::findPath(const TransportNetwork& network,
                                         const string& src,
                                         const string& dest) {

    // ── Step 1: Initialize data structures ──────────────────

    // dist[city] = shortest known distance from src to city
    unordered_map<string, int> dist;

    // parent[city] = previous city on the shortest path to city
    // Used to reconstruct the path after algorithm completes
    unordered_map<string, string> parent;

    // visited set — once a node is finalized, we don't revisit it
    unordered_set<string> visited;

    // ── Step 2: Min-Heap (Priority Queue) ───────────────────
    // pair<int, string> = (distance_from_source, city_name)
    // greater<> makes it a MIN-heap (smallest distance on top)
    //
    // WHY MIN-HEAP?
    //   Dijkstra's greedy strategy requires processing the node
    //   with the smallest tentative distance first. A min-heap
    //   gives us O(log V) extraction of the minimum element.
    priority_queue<
        pair<int, string>,
        vector<pair<int, string>>,
        greater<pair<int, string>>
    > pq;

    // ── Step 3: Initialize all distances to infinity ────────
    vector<string> allCities = network.getAllCities();
    for (const string& city : allCities) {
        dist[city] = INT_MAX;  // "infinity"
    }

    // Source distance is 0 (distance from src to itself)
    dist[src] = 0;
    pq.push({0, src});  // Push source into min-heap

    // ── Step 4: Main Dijkstra Loop ──────────────────────────
    while (!pq.empty()) {
        // Extract the node with MINIMUM distance (greedy choice)
        auto [currentDist, u] = pq.top();
        pq.pop();

        // Skip if already visited (we may have stale entries in heap)
        // This happens because we push new entries instead of updating
        if (visited.count(u)) continue;
        visited.insert(u);

        // Early termination: if we reached destination, stop
        if (u == dest) break;

        // ── Step 5: Relax all neighbors ─────────────────────
        // For each neighbor v of u with edge weight w:
        //   If dist[u] + w < dist[v], we found a shorter path!
        for (const auto& [v, w] : network.getNeighbors(u)) {
            if (!visited.count(v) && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;  // Update shorter distance
                parent[v] = u;          // Record the path
                pq.push({dist[v], v});  // Push updated distance
            }
        }
    }

    // ── Step 6: Reconstruct the path ────────────────────────
    // Trace back from destination to source using parent pointers
    vector<string> path;

    // If destination was never reached, return empty path
    if (dist.find(dest) == dist.end() || dist[dest] == INT_MAX) {
        return path;
    }

    // Build path in reverse: dest → ... → src
    string current = dest;
    while (current != src) {
        path.push_back(current);
        if (parent.find(current) == parent.end()) {
            return vector<string>();  // No path exists
        }
        current = parent[current];
    }
    path.push_back(src);

    // Reverse to get: src → ... → dest
    reverse(path.begin(), path.end());

    return path;
}

string DijkstraFinder::getAlgorithmName() const {
    return "Dijkstra's Algorithm (Shortest Distance)";
}
