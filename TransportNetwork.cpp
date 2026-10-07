// ============================================================
// TransportNetwork.cpp — Graph Implementation
// ============================================================
// Full implementation of the weighted undirected graph using
// adjacency list. Includes road blocking and rerouting support.
// ============================================================

#include "TransportNetwork.h"
#include <iomanip>

// Constructor
TransportNetwork::TransportNetwork() {}

// Destructor
TransportNetwork::~TransportNetwork() {}

// ============================================================
// Helper: Create a consistent route key
// ============================================================
// By always sorting city names alphabetically, we ensure:
//   "Delhi->Mumbai" and "Mumbai->Delhi" produce the SAME key.
// This is critical for the blocked routes set and fare HashMap.
// ============================================================
string TransportNetwork::makeRouteKey(const string& from, const string& to) const {
    if (from < to) return from + "->" + to;
    return to + "->" + from;
}

// ============================================================
// addCity — Add a node to the graph
// ============================================================
// If city doesn't exist, create an empty adjacency list entry.
// Time: O(1) average (hash map insertion)
// ============================================================
void TransportNetwork::addCity(const string& city) {
    if (adjList.find(city) == adjList.end()) {
        adjList[city] = vector<pair<string, int>>();
    }
}

// ============================================================
// removeCity — Remove a node and all its edges
// ============================================================
// Steps:
//   1. For each neighbor of the city, remove the back-edge
//   2. Erase the city's adjacency list entry
// Time: O(V + E) worst case (must clean up all back-edges)
// ============================================================
void TransportNetwork::removeCity(const string& city) {
    if (adjList.find(city) == adjList.end()) return;

    // Step 1: Remove all back-edges from neighbors
    for (auto& [neighbor, dist] : adjList[city]) {
        auto& neighborList = adjList[neighbor];
        neighborList.erase(
            remove_if(neighborList.begin(), neighborList.end(),
                [&city](const pair<string, int>& p) { return p.first == city; }),
            neighborList.end()
        );
        // Also unblock any routes involving this city
        blockedRoutes.erase(makeRouteKey(city, neighbor));
    }

    // Step 2: Remove the city itself
    adjList.erase(city);
}

// ============================================================
// addRoute — Add a weighted bidirectional edge
// ============================================================
// Adds edge in BOTH directions (undirected graph).
// Also creates city nodes if they don't exist yet.
// Time: O(1) average
// ============================================================
void TransportNetwork::addRoute(const string& from, const string& to, int distance) {
    // Auto-create cities if they don't exist
    addCity(from);
    addCity(to);

    // Check if route already exists to avoid duplicates
    for (auto& [neighbor, dist] : adjList[from]) {
        if (neighbor == to) {
            dist = distance;  // Update distance if route exists
            // Also update reverse direction
            for (auto& [n2, d2] : adjList[to]) {
                if (n2 == from) { d2 = distance; break; }
            }
            return;
        }
    }

    // Add edge in both directions (undirected graph)
    adjList[from].push_back({to, distance});
    adjList[to].push_back({from, distance});
}

// ============================================================
// removeRoute — Remove a bidirectional edge
// ============================================================
// Removes the edge from BOTH adjacency lists.
// Uses the erase-remove idiom for clean removal.
// Time: O(degree)
// ============================================================
void TransportNetwork::removeRoute(const string& from, const string& to) {
    // Remove from->to
    if (adjList.find(from) != adjList.end()) {
        auto& fromList = adjList[from];
        fromList.erase(
            remove_if(fromList.begin(), fromList.end(),
                [&to](const pair<string, int>& p) { return p.first == to; }),
            fromList.end()
        );
    }

    // Remove to->from (undirected)
    if (adjList.find(to) != adjList.end()) {
        auto& toList = adjList[to];
        toList.erase(
            remove_if(toList.begin(), toList.end(),
                [&from](const pair<string, int>& p) { return p.first == from; }),
            toList.end()
        );
    }

    // Also unblock if it was blocked
    blockedRoutes.erase(makeRouteKey(from, to));
}

// ============================================================
// blockRoute — Mark a route as blocked (without deleting)
// ============================================================
// The route remains in the adjacency list but getNeighbors()
// will filter it out. This enables "rerouting" — the pathfinding
// algorithms will automatically find alternative paths.
// Time: O(1) average
// ============================================================
void TransportNetwork::blockRoute(const string& from, const string& to) {
    blockedRoutes.insert(makeRouteKey(from, to));
}

// ============================================================
// unblockRoute — Remove the block on a route
// ============================================================
void TransportNetwork::unblockRoute(const string& from, const string& to) {
    blockedRoutes.erase(makeRouteKey(from, to));
}

// ============================================================
// isRouteBlocked — Check if a route is currently blocked
// ============================================================
bool TransportNetwork::isRouteBlocked(const string& from, const string& to) const {
    return blockedRoutes.count(makeRouteKey(from, to)) > 0;
}

// ============================================================
// hasCity — Check if a city exists in the network
// ============================================================
bool TransportNetwork::hasCity(const string& city) const {
    return adjList.find(city) != adjList.end();
}

// ============================================================
// hasRoute — Check if a direct route exists between two cities
// ============================================================
bool TransportNetwork::hasRoute(const string& from, const string& to) const {
    auto it = adjList.find(from);
    if (it == adjList.end()) return false;
    for (const auto& [neighbor, dist] : it->second) {
        if (neighbor == to) return true;
    }
    return false;
}

// ============================================================
// getNeighbors — Get active neighbors (excludes blocked routes)
// ============================================================
// This is the KEY method used by pathfinding algorithms.
// By filtering blocked routes here, Dijkstra and BFS automatically
// reroute around blocked roads without any code changes.
// Time: O(degree)
// ============================================================
vector<pair<string, int>> TransportNetwork::getNeighbors(const string& city) const {
    vector<pair<string, int>> result;
    auto it = adjList.find(city);
    if (it == adjList.end()) return result;

    for (const auto& [neighbor, dist] : it->second) {
        // Only include non-blocked routes
        if (!isRouteBlocked(city, neighbor)) {
            result.push_back({neighbor, dist});
        }
    }
    return result;
}

// ============================================================
// getAllCities — Return names of all cities in the network
// ============================================================
vector<string> TransportNetwork::getAllCities() const {
    vector<string> cities;
    for (const auto& [city, _] : adjList) {
        cities.push_back(city);
    }
    sort(cities.begin(), cities.end());  // Sort alphabetically
    return cities;
}

// ============================================================
// getDistance — Get direct distance between two connected cities
// ============================================================
// Returns -1 if cities are not directly connected.
// ============================================================
int TransportNetwork::getDistance(const string& from, const string& to) const {
    auto it = adjList.find(from);
    if (it == adjList.end()) return -1;
    for (const auto& [neighbor, dist] : it->second) {
        if (neighbor == to) return dist;
    }
    return -1;
}

// ============================================================
// calculatePathCost — Total distance along a path
// ============================================================
// Given a path like [Delhi, Jaipur, Ahmedabad, Mumbai],
// computes: dist(Delhi,Jaipur) + dist(Jaipur,Ahmedabad) + dist(Ahmedabad,Mumbai)
// Returns -1 if any segment is not directly connected.
// Time: O(path_length * average_degree)
// ============================================================
int TransportNetwork::calculatePathCost(const vector<string>& path) const {
    if (path.size() < 2) return 0;

    int totalCost = 0;
    for (size_t i = 0; i < path.size() - 1; i++) {
        int segmentDist = getDistance(path[i], path[i + 1]);
        if (segmentDist == -1) return -1;  // Broken path
        totalCost += segmentDist;
    }
    return totalCost;
}

// ============================================================
// displayNetwork — Pretty-print the entire graph
// ============================================================
void TransportNetwork::displayNetwork() const {
    if (adjList.empty()) {
        cout << "  Network is empty. No cities added yet." << endl;
        return;
    }

    // Get sorted city list for consistent display
    vector<string> cities = getAllCities();

    cout << "\n  ┌─────────────────────────────────────────────────────┐" << endl;
    cout << "  │           TRANSPORT NETWORK MAP                     │" << endl;
    cout << "  ├─────────────────────────────────────────────────────┤" << endl;
    cout << "  │  Cities: " << setw(3) << getCityCount()
         << "  |  Routes: " << setw(3) << getRouteCount()
         << "  |  Blocked: " << setw(3) << blockedRoutes.size()
         << "   │" << endl;
    cout << "  └─────────────────────────────────────────────────────┘\n" << endl;

    for (const string& city : cities) {
        cout << "  [" << city << "]" << endl;
        auto it = adjList.find(city);
        if (it->second.empty()) {
            cout << "     └── (no connections)" << endl;
        } else {
            for (size_t i = 0; i < it->second.size(); i++) {
                const auto& [neighbor, dist] = it->second[i];
                bool blocked = isRouteBlocked(city, neighbor);
                string connector = (i == it->second.size() - 1) ? "└" : "├";
                cout << "     " << connector << "── " << neighbor
                     << " (" << dist << " km)";
                if (blocked) cout << " [BLOCKED]";
                cout << endl;
            }
        }
        cout << endl;
    }
}

// ============================================================
// displayBlockedRoutes — Show all currently blocked routes
// ============================================================
void TransportNetwork::displayBlockedRoutes() const {
    if (blockedRoutes.empty()) {
        cout << "  No routes are currently blocked." << endl;
        return;
    }
    cout << "  Blocked Routes:" << endl;
    for (const string& route : blockedRoutes) {
        cout << "    [X] " << route << endl;
    }
}

// ============================================================
// Statistics
// ============================================================
int TransportNetwork::getCityCount() const {
    return adjList.size();
}

int TransportNetwork::getRouteCount() const {
    int count = 0;
    for (const auto& [city, neighbors] : adjList) {
        count += neighbors.size();
    }
    return count / 2;  // Each edge counted twice (undirected)
}
