// ============================================================
// RouteFinder.h — Abstract Base Class (Polymorphism)
// ============================================================
//
// OOP Concept: POLYMORPHISM (Runtime / Dynamic Dispatch)
//
// This is an abstract base class with a pure virtual method
// findPath(). Different pathfinding algorithms (Dijkstra, BFS)
// inherit from this class and provide their own implementation.
//
// Usage in main():
//   RouteFinder* finder = new DijkstraFinder();
//   vector<string> path = finder->findPath(network, "Delhi", "Mumbai");
//
// The same interface works with ANY algorithm — this is
// the power of polymorphism. We can swap algorithms at runtime
// without changing the calling code.
// ============================================================

#ifndef ROUTE_FINDER_H
#define ROUTE_FINDER_H

#include <vector>
#include <string>
#include "TransportNetwork.h"

using namespace std;

class RouteFinder {
public:
    // Virtual destructor for proper cleanup
    virtual ~RouteFinder() {}

    // ============================================================
    // Pure Virtual Method — MUST be overridden by derived classes
    // ============================================================
    // Parameters:
    //   network — the transport graph to search
    //   src     — source city name
    //   dest    — destination city name
    // Returns:
    //   Vector of city names forming the path (empty if no path)
    // ============================================================
    virtual vector<string> findPath(const TransportNetwork& network,
                                     const string& src,
                                     const string& dest) = 0;

    // Returns the name of the algorithm for display
    virtual string getAlgorithmName() const = 0;
};

#endif // ROUTE_FINDER_H
