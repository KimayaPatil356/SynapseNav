// ============================================================
// BFSFinder.h — BFS Algorithm (Derived Class)
// ============================================================
// Inherits from RouteFinder. Finds the path with MINIMUM
// number of stops (edges), regardless of distance.
// ============================================================

#ifndef BFS_FINDER_H
#define BFS_FINDER_H

#include "RouteFinder.h"

class BFSFinder : public RouteFinder {
public:
    // --- Polymorphism: Override the pure virtual findPath() ---
    vector<string> findPath(const TransportNetwork& network,
                             const string& src,
                             const string& dest) override;

    string getAlgorithmName() const override;
};

#endif // BFS_FINDER_H
