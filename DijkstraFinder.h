// ============================================================
// DijkstraFinder.h — Dijkstra's Algorithm (Derived Class)
// ============================================================
// Inherits from RouteFinder. Finds the SHORTEST PATH by
// total distance (sum of edge weights).
// ============================================================

#ifndef DIJKSTRA_FINDER_H
#define DIJKSTRA_FINDER_H

#include "RouteFinder.h"

class DijkstraFinder : public RouteFinder {
public:
    // --- Polymorphism: Override the pure virtual findPath() ---
    vector<string> findPath(const TransportNetwork& network,
                             const string& src,
                             const string& dest) override;

    string getAlgorithmName() const override;
};

#endif // DIJKSTRA_FINDER_H
