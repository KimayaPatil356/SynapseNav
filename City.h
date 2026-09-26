// ============================================================
// City.h — Derived Class (Inheritance + Polymorphism)
// ============================================================
// Inherits from Location. Adds city-specific attributes.
//
// OOP Concepts:
//   - Inheritance:   City IS-A Location (public inheritance)
//   - Polymorphism:  Overrides display() and getType()
//   - Encapsulation: Private members with public interface
// ============================================================

#ifndef CITY_H
#define CITY_H

#include "Location.h"

class City : public Location {
private:
    int population;   // City population
    bool isMetro;     // Whether it's a metro/major city

public:
    // Constructors & Destructor
    City();
    City(string name, float lat, float lon, int pop, bool metro);
    ~City() override;

    // Getters
    int getPopulation() const;
    bool getIsMetro() const;

    // Setters
    void setPopulation(int pop);
    void setIsMetro(bool metro);

    // --- Polymorphism: Override base class virtual methods ---
    void display() const override;
    string getType() const override;
};

#endif // CITY_H
