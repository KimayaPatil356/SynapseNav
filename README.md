# 🚂 NexusNav — Graph Routing & Transit Engine

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white) 
![OOP](https://img.shields.io/badge/OOP-Enabled-brightgreen?style=for-the-badge)
![DSA](https://img.shields.io/badge/DSA-Optimized-orange?style=for-the-badge)

A complete console-based **Smart Transport & Navigation System** built in pure C++ using advanced **Data Structures & Algorithms (DSA)** and strict **Object-Oriented Programming (OOP)** principles. 

This project is tailored for a B.Tech Final Year Submission, demonstrating the practical routing differences between shortest-distance algorithms and minimum-stops algorithms using an interactive terminal interface.

---

## 🌟 Key Features

✔ **OOP Architecture:** Real-world modeling using Encapsulation, Abstraction, Inheritance (`City`, `Stop` → `Location`), and Runtime Polymorphism (`DijkstraFinder`, `BFSFinder` → `RouteFinder`).  
✔ **Graph Algorithms:** Core transportation network modeled using a dynamically weighted Adjacency List.  
✔ **Dijkstra vs BFS Comparison:** Provides a side-by-side execution mapping for the shortest overall distance vs minimum hops.   
✔ **Dynamic Road Blocking:** Simulate real-time road closures that force the pathfinding algorithms to find alternate routes.  
✔ **Ultra-Fast Search:** Incorporates a case-insensitive `Trie` (Prefix Tree) for auto-completing city names.  
✔ **Recent Searches:** Employs a fixed-capacity Sliding Window `Stack` for storing navigation history.  
✔ **`O(1)` Fare Lookup:** Custom `HashMap` utilizing Separate Chaining and a polynomial rolling hash to retrieve routing fares efficiently.  
✔ **Pre-Loaded Indian Map:** Auto-boots with a sample dataset covering 12 major Indian cities and 20 major highways to instantly demonstrate all functionalities out-of-the-box.  

---

## 📊 DSA Implementation Summary

| Functionality | DSA Used | Purpose |
|---|---|---|
| **Road Network Structure** | **Weighted Graph** (Adjacency List) | Stores cities as nodes and roads/distances as edges. |
| **Shortest Path (Distance)** | **Dijkstra's Algorithm** | Greedily finds the routing path with the absolute minimum km length. |
| **Priority Queueing** | **Min-Heap** | Optimizes Dijkstra's edge relaxation to `O((V + E) log V)`. |
| **Minimum Stops (Hops)** | **BFS** | Finds the direct path with the least amount of layovers. |
| **City Name Autocomplete** | **Trie (Prefix Tree)** | Extremely fast search & extraction of cities by prefix string. |
| **Search History**| **Stack** | Stores the last 5 searched routes acting as a sliding window buffer. |
| **Ticket Fare Lookup** | **Custom Hash Map** | Fast retrieval of fares resolving collisions using Separate Chaining. |

---

## 🚀 How to Run

No external libraries or packages are required. Standard C++ STL only.

**1. Clone the repository & Enter Directory:**
```bash
git clone https://github.com/sde-saharsh/Smart-Transport-Navigation-System.git
cd "Smart Transport & Navigation System"
```

**2. Compile & Run using Makefile:**
```bash
make run
```
*(Optionally you can just run `make` to compile and `./SmartTransport` to execute)*

---

## 🖥️ Application Menu Preview

The CLI greets users with an interactive, robust 19-option menu pane:

```text
  ┌──────────────────────────────────────────────┐
  │              MAIN MENU                       │
  ├──────────────────────────────────────────────┤
  │  [1]  Add City                            │
  │  [2]  Add Route (Road)                    │
  │  [3]  Remove City                         │
  │  [4]  Remove Route                        │
  ├──────────────────────────────────────────────┤
  │  [5]  Block a Road                        │
  │  [6]  Unblock a Road                      │
  ├──────────────────────────────────────────────┤
  │  [7]  Shortest Path (Dijkstra)            │
  │  [8]  Minimum Stops Path (BFS)            │
  │  [9]  Compare Dijkstra vs BFS             │
  ├──────────────────────────────────────────────┤
  │  ...and much more! (Up to 19 options)        │
  └──────────────────────────────────────────────┘
```

---

## 🏛️ Project Directory Structure

```text
SmartTransport/
│
├── main.cpp                 ← Menu-driven entry point
├── Makefile                 ← Compile definitions
│
├── Location.h / .cpp        ← Base Class (Encapsulation + Abstraction)
├── City.h / .cpp            ← Derived Class (Inheritance)
├── Stop.h / .cpp            ← Derived Class (Inheritance)
│
├── TransportNetwork.h/.cpp  ← Core Graph Engine
├── RouteFinder.h            ← Abstract base for routing (Polymorphism)
├── DijkstraFinder.cpp       ← Distance-optimized path logic
├── BFSFinder.cpp            ← Stop-optimized path logic
│
├── Trie.h / .cpp            ← Prefix tree autocomplete search
├── Stack.h                  ← Sliding window history keeper
└── HashMap.h                ← Fare storage mapping
```

---

*Authored for B.Tech Final Year demonstrating applied capabilities in object-oriented system design and low-level C++ algorithmic manipulation.*
# Smart-Transport-Navigation-System-
