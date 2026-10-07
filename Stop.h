// ============================================================
// Stop.h — Derived Class (Inheritance + Polymorphism)
// ============================================================
// Represents a bus/metro stop. Inherits from Location.
//
// OOP Concepts:
//   - Inheritance:   Stop IS-A Location
//   - Polymorphism:  Overrides display() and getType()
// ============================================================

#ifndef STOP_H
#define STOP_H

#include "Location.h"

class Stop : public Location {
private:
    string stopType;     // "Bus" or "Metro"
    string routeNumber;  // Route identifier (e.g., "R-42")

public:
    // Constructors & Destructor
    Stop();
    Stop(string name, float lat, float lon, string type, string route);
    ~Stop() override;

    // Getters
    string getStopType() const;
    string getRouteNumber() const;

    // Setters
    void setStopType(string type);
    void setRouteNumber(string route);

    // --- Polymorphism: Override base class virtual methods ---
    void display() const override;
    string getType() const override;
};

#endif // STOP_H
