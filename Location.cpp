// ============================================================
// Location.cpp — Base Class Implementation
// ============================================================

#include "Location.h"

// Default constructor — initializes with empty/zero values
Location::Location() : name(""), latitude(0.0f), longitude(0.0f) {}

// Parameterized constructor — uses initializer list for efficiency
Location::Location(string name, float lat, float lon)
    : name(name), latitude(lat), longitude(lon) {}

// Virtual destructor — empty but necessary for polymorphism
Location::~Location() {}

// --- Getter Implementations ---
string Location::getName() const { return name; }
float Location::getLatitude() const { return latitude; }
float Location::getLongitude() const { return longitude; }

// --- Setter Implementations ---
void Location::setName(string name) { this->name = name; }
void Location::setLatitude(float lat) { latitude = lat; }
void Location::setLongitude(float lon) { longitude = lon; }
