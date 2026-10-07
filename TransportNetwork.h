// ============================================================
// TransportNetwork.h — Core Graph Class
// ============================================================
//
// DSA Used: WEIGHTED GRAPH (Adjacency List)
//
// The transport network is modeled as a weighted undirected graph:
//   - Nodes  = Cities / Stops
//   - Edges  = Roads / Routes with distances (weights)
//
// Internal Representation:
//   unordered_map<string, vector<pair<string, int>>> adjList
//   Key:   city name (string)
//   Value: list of (neighbor_name, distance) pairs
//
// Complexity Analysis:
//   - Add city:     O(1) average
//   - Add route:    O(1) average
//   - Remove route: O(degree) where degree = number of neighbors
//   - Get neighbors: O(degree)
//   - Space: O(V + E) where V = cities, E = routes
//
// The "blocked routes" feature uses an unordered_set for O(1) lookup
// to check if a route is blocked, enabling dynamic rerouting.
// ============================================================

#ifndef TRANSPORT_NETWORK_H
#define TRANSPORT_NETWORK_H

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <algorithm>

using namespace std;

class TransportNetwork {
private:
    // --- Core Data Structure: Adjacency List ---
    // Maps each city to its list of (neighbor, distance) pairs
    unordered_map<string, vector<pair<string, int>>> adjList;

    // --- Blocked Routes Set ---
    // Stores route keys like "CityA->CityB" for O(1) blocked check
    unordered_set<string> blockedRoutes;

    // Helper: creates a consistent key for a route (alphabetically sorted)
    // e.g., makeRouteKey("Mumbai", "Delhi") => "Delhi->Mumbai"
    string makeRouteKey(const string& from, const string& to) const;

public:
    TransportNetwork();
    ~TransportNetwork();

    // ========== Graph Modification Operations ==========

    // Add a city (node) to the graph
    void addCity(const string& city);

    // Remove a city and ALL its connected routes
    void removeCity(const string& city);

    // Add a bidirectional route (undirected edge) with distance weight
    void addRoute(const string& from, const string& to, int distance);

    // Remove a bidirectional route between two cities
    void removeRoute(const string& from, const string& to);

    // ========== Road Blocking (Dynamic Rerouting) ==========

    // Block a route — it stays in the graph but is treated as unusable
    void blockRoute(const string& from, const string& to);

    // Unblock a previously blocked route
    void unblockRoute(const string& from, const string& to);

    // Check if a specific route is currently blocked
    bool isRouteBlocked(const string& from, const string& to) const;

    // ========== Query Operations ==========

    // Check if a city exists in the network
    bool hasCity(const string& city) const;

    // Check if a direct route exists between two cities
    bool hasRoute(const string& from, const string& to) const;

    // Get all ACTIVE neighbors (filters out blocked routes)
    vector<pair<string, int>> getNeighbors(const string& city) const;

    // Get names of all cities in the network
    vector<string> getAllCities() const;

    // Get direct distance between two connected cities (-1 if not connected)
    int getDistance(const string& from, const string& to) const;

    // Calculate total path cost given a sequence of cities
    int calculatePathCost(const vector<string>& path) const;

    // ========== Display & Statistics ==========

    void displayNetwork() const;
    void displayBlockedRoutes() const;
    int getCityCount() const;
    int getRouteCount() const;
};

#endif // TRANSPORT_NETWORK_H
