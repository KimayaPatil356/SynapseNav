#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>

#include "Location.h"
#include "City.h"
#include "Stop.h"
#include "TransportNetwork.h"
#include "RouteFinder.h"
#include "DijkstraFinder.h"
#include "BFSFinder.h"
#include "Trie.h"
#include "Stack.h"
#include "HashMap.h"

using namespace std;

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define DIM     "\033[2m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void displayPath(const vector<string>& path,
                 const TransportNetwork& network,
                 const string& algoName) {
    if (path.empty()) {
        cout << RED << "No path found!" << RESET << endl;
        return;
    }

    cout << GREEN << "\nPath found using " << algoName << ":" << RESET << endl;

    cout << CYAN << "Route: " << RESET;

    for (size_t i = 0; i < path.size(); i++) {
        cout << BOLD << path[i] << RESET;

        if (i < path.size() - 1) {
            int dist = network.getDistance(path[i], path[i + 1]);
            cout << YELLOW << " --(" << dist << " km)--> " << RESET;
        }
    }

    cout << endl;

    int totalCost = network.calculatePathCost(path);
    int stops = path.size() - 1;

    cout << "\nStatistics:" << endl;
    cout << "Total Distance : " << GREEN << totalCost << " km" << RESET << endl;
    cout << "Number of Stops: " << GREEN << stops << RESET << endl;
}

void displayBanner() {
    cout << CYAN << BOLD;
    cout << "\nSMART TRANSPORT & NAVIGATION SYSTEM" << endl;
    cout << "DSA + OOP Project | B.Tech" << endl;
    cout << RESET << endl;
}

void displayMenu() {
    cout << YELLOW << "\nMAIN MENU" << RESET << endl;

    cout << "[1]  Add City" << endl;
    cout << "[2]  Add Route (Road)" << endl;
    cout << "[3]  Remove City" << endl;
    cout << "[4]  Remove Route" << endl;

    cout << "[5]  Block a Road" << endl;
    cout << "[6]  Unblock a Road" << endl;

    cout << "[7]  Shortest Path (Dijkstra)" << endl;
    cout << "[8]  Minimum Stops Path (BFS)" << endl;
    cout << "[9]  Compare Dijkstra vs BFS" << endl;

    cout << "[10] Search City by Prefix (Trie)" << endl;
    cout << "[11] View Recent Searches (Stack)" << endl;

    cout << "[12] Add / Update Fare (HashMap)" << endl;
    cout << "[13] Lookup Fare (HashMap)" << endl;
    cout << "[14] Display All Fares" << endl;

    cout << "[15] Display Network Map" << endl;
    cout << "[16] Display Blocked Routes" << endl;
    cout << "[17] Display All Cities (Trie)" << endl;
    cout << "[18] Show OOP Demo (Polymorphism)" << endl;

    cout << "[19] Load Sample Network" << endl;
    cout << "[0]  Exit" << endl;

    cout << CYAN << "\nEnter choice: " << RESET;
}

void loadSampleNetwork(TransportNetwork& network,
                       Trie& trie,
                       HashMap<int>& fareMap,
                       vector<Location*>& locations) {

    cout << YELLOW << "\nLoading sample network..." << RESET << endl;

    locations.push_back(new City("Delhi", 28.6139, 77.2090, 19000000, true));
    locations.push_back(new City("Mumbai", 19.0760, 72.8777, 21000000, true));
    locations.push_back(new City("Kolkata", 22.5726, 88.3639, 15000000, true));
    locations.push_back(new City("Chennai", 13.0827, 80.2707, 10000000, true));
    locations.push_back(new City("Bangalore", 12.9716, 77.5946, 12000000, true));
    locations.push_back(new City("Hyderabad", 17.3850, 78.4867, 10000000, true));
    locations.push_back(new City("Jaipur", 26.9124, 75.7873, 4000000, false));
    locations.push_back(new City("Lucknow", 26.8467, 80.9462, 3500000, false));
    locations.push_back(new City("Pune", 18.5204, 73.8567, 7000000, false));
    locations.push_back(new City("Ahmedabad", 23.0225, 72.5714, 8000000, true));

    locations.push_back(new Stop("Nagpur", 21.1458, 79.0882, "Railway", "NH-44"));
    locations.push_back(new Stop("Bhopal", 23.2599, 77.4126, "Railway", "NH-46"));

    vector<string> cityNames = {
        "Delhi", "Mumbai", "Kolkata", "Chennai", "Bangalore",
        "Hyderabad", "Jaipur", "Lucknow", "Pune", "Ahmedabad",
        "Nagpur", "Bhopal"
    };

    for (const string& name : cityNames) {
        network.addCity(name);
        trie.insert(name);
    }

    network.addRoute("Delhi", "Jaipur", 280);
    network.addRoute("Jaipur", "Ahmedabad", 660);
    network.addRoute("Ahmedabad", "Mumbai", 530);
    network.addRoute("Mumbai", "Pune", 150);
    network.addRoute("Pune", "Bangalore", 840);
    network.addRoute("Bangalore", "Chennai", 350);
    network.addRoute("Chennai", "Kolkata", 1660);
    network.addRoute("Delhi", "Lucknow", 550);
    network.addRoute("Lucknow", "Kolkata", 990);
    network.addRoute("Hyderabad", "Bangalore", 570);
    network.addRoute("Mumbai", "Hyderabad", 710);
    network.addRoute("Delhi", "Nagpur", 1100);
    network.addRoute("Nagpur", "Hyderabad", 500);
    network.addRoute("Delhi", "Bhopal", 780);
    network.addRoute("Bhopal", "Mumbai", 780);
    network.addRoute("Nagpur", "Pune", 720);

    network.addRoute("Delhi", "Bangalore", 2700);
    network.addRoute("Delhi", "Mumbai", 1500);
    network.addRoute("Delhi", "Chennai", 2800);
    network.addRoute("Kolkata", "Bangalore", 2500);

    fareMap.insert("Delhi->Jaipur", 450);
    fareMap.insert("Jaipur->Ahmedabad", 800);
    fareMap.insert("Ahmedabad->Mumbai", 650);
    fareMap.insert("Mumbai->Pune", 200);
    fareMap.insert("Pune->Bangalore", 1100);
    fareMap.insert("Bangalore->Chennai", 500);
    fareMap.insert("Chennai->Kolkata", 2000);
    fareMap.insert("Delhi->Lucknow", 700);
    fareMap.insert("Lucknow->Kolkata", 1200);
    fareMap.insert("Hyderabad->Bangalore", 750);
    fareMap.insert("Mumbai->Hyderabad", 900);
    fareMap.insert("Delhi->Bangalore", 3500);
    fareMap.insert("Delhi->Mumbai", 1800);
    fareMap.insert("Delhi->Nagpur", 1500);
    fareMap.insert("Nagpur->Hyderabad", 600);
    fareMap.insert("Delhi->Bhopal", 1000);
    fareMap.insert("Bhopal->Mumbai", 1000);
    fareMap.insert("Nagpur->Pune", 950);
    fareMap.insert("Delhi->Chennai", 3600);
    fareMap.insert("Kolkata->Bangalore", 3000);

    cout << GREEN << "Sample network loaded successfully!" << RESET << endl;
    cout << network.getCityCount() << " cities added" << endl;
    cout << network.getRouteCount() << " routes added" << endl;
    cout << fareMap.getSize() << " fares configured" << endl;
    cout << "All city names indexed in Trie" << endl;
}

int main() {
    TransportNetwork network;
    Trie trie;
    Stack<string> recentSearches(5);
    HashMap<int> fareMap;

    RouteFinder* dijkstra = new DijkstraFinder();
    RouteFinder* bfs = new BFSFinder();

    vector<Location*> locations;

    int choice;
    string city1, city2, prefix;
    int distance, fare;
    bool networkLoaded = false;

    displayBanner();

    loadSampleNetwork(network, trie, fareMap, locations);
    networkLoaded = true;

    do {
        displayMenu();

        if (!(cin >> choice)) {
            clearInput();
            choice = -1;
        }

        switch (choice) {

        case 1: {
            cout << CYAN << "\nADD CITY" << RESET << endl;
            cout << "Enter city name: ";
            cin >> city1;

            if (network.hasCity(city1)) {
                cout << YELLOW << "City '" << city1
                     << "' already exists!" << RESET << endl;
            } else {
                network.addCity(city1);
                trie.insert(city1);

                float lat, lon;
                int pop;
                char metro;

                cout << "Enter latitude: ";
                cin >> lat;

                cout << "Enter longitude: ";
                cin >> lon;

                cout << "Enter population: ";
                cin >> pop;

                cout << "Is it a metro city? (y/n): ";
                cin >> metro;

                locations.push_back(
                    new City(city1, lat, lon, pop,
                             (metro == 'y' || metro == 'Y'))
                );

                cout << GREEN << "City '" << city1
                     << "' added successfully!" << RESET << endl;
            }

            break;
        }

        case 2: {
            cout << CYAN << "\nADD ROUTE" << RESET << endl;

            cout << "Enter source city: ";
            cin >> city1;

            cout << "Enter destination city: ";
            cin >> city2;

            cout << "Enter distance (km): ";
            cin >> distance;

            if (distance <= 0) {
                cout << RED << "Distance must be positive!" << RESET << endl;
            } else {
                network.addRoute(city1, city2, distance);

                trie.insert(city1);
                trie.insert(city2);

                cout << GREEN << "Route added: "
                     << city1 << " <-> " << city2
                     << " (" << distance << " km)"
                     << RESET << endl;
            }

            break;
        }

        case 3: {
            cout << CYAN << "\nREMOVE CITY" << RESET << endl;

            cout << "Enter city name: ";
            cin >> city1;

            if (!network.hasCity(city1)) {
                cout << RED << "City '" << city1
                     << "' not found!" << RESET << endl;
            } else {
                network.removeCity(city1);
                trie.remove(city1);

                cout << GREEN << "City '" << city1
                     << "' removed along with all its routes."
                     << RESET << endl;
            }

            break;
        }

        case 4: {
            cout << CYAN << "\nREMOVE ROUTE" << RESET << endl;

            cout << "Enter source city: ";
            cin >> city1;

            cout << "Enter destination city: ";
            cin >> city2;

            if (!network.hasRoute(city1, city2)) {
                cout << RED << "No route exists between '"
                     << city1 << "' and '" << city2
                     << "'!" << RESET << endl;
            } else {
                network.removeRoute(city1, city2);

                cout << GREEN << "Route removed: "
                     << city1 << " <-> " << city2
                     << RESET << endl;
            }

            break;
        }

        case 5: {
            cout << CYAN << "\nBLOCK ROAD" << RESET << endl;

            cout << "Enter source city: ";
            cin >> city1;

            cout << "Enter destination city: ";
            cin >> city2;

            if (!network.hasRoute(city1, city2)) {
                cout << RED << "No route exists between '"
                     << city1 << "' and '" << city2
                     << "'!" << RESET << endl;
            } else if (network.isRouteBlocked(city1, city2)) {
                cout << YELLOW << "Route already blocked!"
                     << RESET << endl;
            } else {
                network.blockRoute(city1, city2);

                cout << RED << "Road BLOCKED: "
                     << city1 << " <-> " << city2
                     << RESET << endl;

                cout << "Pathfinding algorithms will now reroute around this road."
                     << endl;
            }

            break;
        }

        case 6: {
            cout << CYAN << "\nUNBLOCK ROAD" << RESET << endl;

            cout << "Enter source city: ";
            cin >> city1;

            cout << "Enter destination city: ";
            cin >> city2;

            if (!network.isRouteBlocked(city1, city2)) {
                cout << YELLOW << "Route is not currently blocked!"
                     << RESET << endl;
            } else {
                network.unblockRoute(city1, city2);

                cout << GREEN << "Road UNBLOCKED: "
                     << city1 << " <-> " << city2
                     << RESET << endl;
            }

            break;
        }

        case 7: {
            cout << CYAN << "\nSHORTEST PATH (DIJKSTRA)" << RESET << endl;

            cout << "Enter source city: ";
            cin >> city1;

            cout << "Enter destination city: ";
            cin >> city2;

            if (!network.hasCity(city1)) {
                cout << RED << "Source city '" << city1
                     << "' not found!" << RESET << endl;
                break;
            }

            if (!network.hasCity(city2)) {
                cout << RED << "Destination city '" << city2
                     << "' not found!" << RESET << endl;
                break;
            }

            vector<string> path =
                dijkstra->findPath(network, city1, city2);

            displayPath(
                path,
                network,
                dijkstra->getAlgorithmName()
            );

            string searchEntry =
                city1 + " -> " + city2 + " [Dijkstra]";

            recentSearches.push(searchEntry);

            break;
        }

        case 8: {
            cout << CYAN << "\nMINIMUM STOPS PATH (BFS)" << RESET << endl;

            cout << "Enter source city: ";
            cin >> city1;

            cout << "Enter destination city: ";
            cin >> city2;

            if (!network.hasCity(city1)) {
                cout << RED << "Source city '" << city1
                     << "' not found!" << RESET << endl;
                break;
            }

            if (!network.hasCity(city2)) {
                cout << RED << "Destination city '" << city2
                     << "' not found!" << RESET << endl;
                break;
            }

            vector<string> path =
                bfs->findPath(network, city1, city2);

            displayPath(
                path,
                network,
                bfs->getAlgorithmName()
            );

            string searchEntry =
                city1 + " -> " + city2 + " [BFS]";

            recentSearches.push(searchEntry);

            break;
        }

        case 9: {
            cout << CYAN << "\nCOMPARE: DIJKSTRA vs BFS"
                 << RESET << endl;

            cout << "Enter source city: ";
            cin >> city1;

            cout << "Enter destination city: ";
            cin >> city2;

            if (!network.hasCity(city1) ||
                !network.hasCity(city2)) {

                cout << RED << "One or both cities not found!"
                     << RESET << endl;
                break;
            }

            vector<string> dijkstraPath =
                dijkstra->findPath(network, city1, city2);

            vector<string> bfsPath =
                bfs->findPath(network, city1, city2);

            cout << "\n" << MAGENTA
                 << "Algorithm Comparison: "
                 << city1 << " -> " << city2
                 << RESET << endl;

            cout << BLUE << "\n"
                 << dijkstra->getAlgorithmName()
                 << ":" << RESET << endl;

            if (dijkstraPath.empty()) {
                cout << RED << "No path found." << RESET << endl;
            } else {
                cout << "Path: ";

                for (size_t i = 0; i < dijkstraPath.size(); i++) {
                    cout << dijkstraPath[i];

                    if (i < dijkstraPath.size() - 1)
                        cout << " -> ";
                }

                cout << endl;

                int dCost =
                    network.calculatePathCost(dijkstraPath);

                cout << "Distance : "
                     << GREEN << dCost << " km"
                     << RESET << endl;

                cout << "Stops    : "
                     << (dijkstraPath.size() - 1)
                     << endl;
            }

            cout << BLUE << "\n"
                 << bfs->getAlgorithmName()
                 << ":" << RESET << endl;

            if (bfsPath.empty()) {
                cout << RED << "No path found." << RESET << endl;
            } else {
                cout << "Path: ";

                for (size_t i = 0; i < bfsPath.size(); i++) {
                    cout << bfsPath[i];

                    if (i < bfsPath.size() - 1)
                        cout << " -> ";
                }

                cout << endl;

                int bCost =
                    network.calculatePathCost(bfsPath);

                cout << "Distance : "
                     << GREEN << bCost << " km"
                     << RESET << endl;

                cout << "Stops    : "
                     << (bfsPath.size() - 1)
                     << endl;
            }

            if (!dijkstraPath.empty() && !bfsPath.empty()) {
                int dCost =
                    network.calculatePathCost(dijkstraPath);

                int bCost =
                    network.calculatePathCost(bfsPath);

                int dStops =
                    dijkstraPath.size() - 1;

                int bStops =
                    bfsPath.size() - 1;

                cout << YELLOW << "\nComparison"
                     << RESET << endl;

                if (dCost < bCost) {
                    cout << GREEN
                         << "Dijkstra saves "
                         << (bCost - dCost)
                         << " km in distance!"
                         << RESET << endl;
                }

                if (bStops < dStops) {
                    cout << GREEN
                         << "BFS saves "
                         << (dStops - bStops)
                         << " stop(s)!"
                         << RESET << endl;
                }

                if (dCost == bCost && dStops == bStops) {
                    cout << GREEN
                         << "Both algorithms found the same optimal path!"
                         << RESET << endl;
                }
            }

            string searchEntry =
                city1 + " -> " + city2 + " [Compare]";

            recentSearches.push(searchEntry);

            break;
        }

        case 10: {
            cout << CYAN
                 << "\nSEARCH CITY BY PREFIX (TRIE)"
                 << RESET << endl;

            cout << "Enter prefix: ";
            cin >> prefix;

            vector<string> results =
                trie.searchByPrefix(prefix);

            if (results.empty()) {
                cout << YELLOW
                     << "No cities found with prefix '"
                     << prefix << "'"
                     << RESET << endl;
            } else {
                cout << GREEN
                     << "Found " << results.size()
                     << " match(es):"
                     << RESET << endl;

                for (const string& r : results) {
                    cout << "  " << r << endl;
                }
            }

            break;
        }

        case 11: {
            cout << CYAN
                 << "\nRECENT SEARCHES (STACK)"
                 << RESET << endl;

            recentSearches.display();

            break;
        }

        case 12: {
            cout << CYAN
                 << "\nADD/UPDATE FARE (HASHMAP)"
                 << RESET << endl;

            cout << "Enter source city: ";
            cin >> city1;

            cout << "Enter destination city: ";
            cin >> city2;

            cout << "Enter fare (Rs.): ";
            cin >> fare;

            string key =
                (city1 < city2)
                ? city1 + "->" + city2
                : city2 + "->" + city1;

            fareMap.insert(key, fare);

            cout << GREEN
                 << "Fare updated: "
                 << key << " = Rs." << fare
                 << RESET << endl;

            break;
        }

        case 13: {
            cout << CYAN
                 << "\nLOOKUP FARE (HASHMAP)"
                 << RESET << endl;

            cout << "Enter source city: ";
            cin >> city1;

            cout << "Enter destination city: ";
            cin >> city2;

            string key =
                (city1 < city2)
                ? city1 + "->" + city2
                : city2 + "->" + city1;

            int foundFare;

            if (fareMap.get(key, foundFare)) {
                cout << GREEN
                     << "Fare for "
                     << city1 << " <-> " << city2
                     << " : Rs." << foundFare
                     << RESET << endl;
            } else {
                cout << YELLOW
                     << "No fare configured for this route."
                     << RESET << endl;
            }

            break;
        }

        case 14: {
            cout << CYAN
                 << "\nALL FARES (HASHMAP)"
                 << RESET << endl;

            fareMap.display();

            break;
        }

        case 15: {
            cout << CYAN
                 << "\nNETWORK MAP"
                 << RESET << endl;

            network.displayNetwork();

            break;
        }

        case 16: {
            cout << CYAN
                 << "\nBLOCKED ROUTES"
                 << RESET << endl;

            network.displayBlockedRoutes();

            break;
        }

        case 17: {
            cout << CYAN
                 << "\nALL CITIES IN TRIE"
                 << RESET << endl;

            trie.displayAll();

            break;
        }

        case 18: {
            cout << MAGENTA
                 << "\nOOP DEMO: POLYMORPHISM"
                 << RESET << endl;

            if (locations.empty()) {
                cout << YELLOW
                     << "No locations loaded. Use option 19 first."
                     << RESET << endl;
                break;
            }

            cout << "\nRuntime Polymorphism:\n" << endl;

            for (Location* loc : locations) {
                cout << "Type: "
                     << CYAN << loc->getType()
                     << RESET << " -> ";

                loc->display();
            }

            cout << "\nRouteFinder Polymorphism:" << endl;

            cout << "dijkstra->getAlgorithmName() = "
                 << CYAN
                 << dijkstra->getAlgorithmName()
                 << RESET << endl;

            cout << "bfs->getAlgorithmName()      = "
                 << CYAN
                 << bfs->getAlgorithmName()
                 << RESET << endl;

            break;
        }

        case 19: {
            if (networkLoaded) {
                cout << YELLOW
                     << "Sample network is already loaded!"
                     << RESET << endl;
            } else {
                loadSampleNetwork(
                    network,
                    trie,
                    fareMap,
                    locations
                );

                networkLoaded = true;
            }

            break;
        }

        case 0: {
            cout << CYAN << BOLD
                 << "\nThank you for using Smart Transport!"
                 << RESET << endl;

            cout << "Have a safe journey!" << endl;

            break;
        }

        default:
            cout << RED
                 << "Invalid choice! Please try again."
                 << RESET << endl;
        }

    } while (choice != 0);

    delete dijkstra;
    delete bfs;

    for (Location* loc : locations) {
        delete loc;
    }

    return 0;
}