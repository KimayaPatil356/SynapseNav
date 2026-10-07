// ============================================================
// Location.h — Base Class (Abstraction + Encapsulation)
// ============================================================
// This is the BASE CLASS for all geographical locations.
//
// OOP Concepts Demonstrated:
//   - Encapsulation: private data with public getters/setters
//   - Abstraction:   pure virtual methods hide implementation
//   - Inheritance:   City and Stop derive from this class
//
// The virtual destructor ensures proper cleanup when deleting
// derived class objects through a base class pointer.
// ============================================================

#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <iostream>

using namespace std;

class Location {
private:
    // --- Encapsulated Data Members ---
    string name;        // Name of the location
    float latitude;     // Geographic latitude
    float longitude;    // Geographic longitude

public:
    // --- Constructors & Destructor ---
    Location();
    Location(string name, float lat, float lon);
    virtual ~Location();  // Virtual destructor for safe polymorphic deletion

    // --- Getters (Encapsulation) ---
    string getName() const;
    float getLatitude() const;
    float getLongitude() const;

    // --- Setters (Encapsulation) ---
    void setName(string name);
    void setLatitude(float lat);
    void setLongitude(float lon);

    // --- Pure Virtual Methods (Abstraction) ---
    // These MUST be overridden by derived classes.
    // This makes Location an abstract class — cannot be instantiated directly.
    virtual void display() const = 0;
    virtual string getType() const = 0;
};

#endif // LOCATION_H
