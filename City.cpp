// ============================================================
// City.cpp — City Class Implementation
// ============================================================

#include "City.h"

// Default constructor — calls Location's default constructor
City::City() : Location(), population(0), isMetro(false) {}

// Parameterized constructor — passes name, lat, lon to Location
City::City(string name, float lat, float lon, int pop, bool metro)
    : Location(name, lat, lon), population(pop), isMetro(metro) {}

City::~City() {}

// --- Getters ---
int City::getPopulation() const { return population; }
bool City::getIsMetro() const { return isMetro; }

// --- Setters ---
void City::setPopulation(int pop) { population = pop; }
void City::setIsMetro(bool metro) { isMetro = metro; }

// --- Polymorphism: display() override ---
// When called through a Location pointer, this version runs (runtime dispatch)
void City::display() const {
    cout << "  [CITY] " << getName()
         << " | Pop: " << population
         << " | Metro: " << (isMetro ? "Yes" : "No")
         << " | Coords: (" << getLatitude() << ", " << getLongitude() << ")"
         << endl;
}

// --- Polymorphism: getType() override ---
string City::getType() const { return "City"; }
