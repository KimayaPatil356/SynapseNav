// ============================================================
// Stop.cpp — Stop Class Implementation
// ============================================================

#include "Stop.h"

Stop::Stop() : Location(), stopType(""), routeNumber("") {}

Stop::Stop(string name, float lat, float lon, string type, string route)
    : Location(name, lat, lon), stopType(type), routeNumber(route) {}

Stop::~Stop() {}

// --- Getters ---
string Stop::getStopType() const { return stopType; }
string Stop::getRouteNumber() const { return routeNumber; }

// --- Setters ---
void Stop::setStopType(string type) { stopType = type; }
void Stop::setRouteNumber(string route) { routeNumber = route; }

// --- Polymorphism: display() override ---
void Stop::display() const {
    cout << "  [STOP] " << getName()
         << " | Type: " << stopType
         << " | Route: " << routeNumber
         << " | Coords: (" << getLatitude() << ", " << getLongitude() << ")"
         << endl;
}

// --- Polymorphism: getType() override ---
string Stop::getType() const { return "Stop (" + stopType + ")"; }
