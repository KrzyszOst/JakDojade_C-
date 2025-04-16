# 🗺️ Pathfinding System on a City Map – C++ (Without STL)

This is a university project created for the **Algorithms and data structures** course.  
It implements a simulation of a rectangular map consisting of cities, roads, and one-way flight connections, allowing for shortest path queries between cities using a custom implementation of Dijkstra's algorithm.

---

## 📌 Project Overview

- The map is a grid-based structure where:
  - `.` – non-passable field
  - `#` – drivable road (1 minute per move)
  - `*` – a city's location
  - Letters/digits – city names (non-passable)

- Cities are connected:
  - Via **roads** in 4 directions (up, down, left, right)
  - Via **flights** with given durations between named cities

- The program answers queries about the **shortest travel time** between two cities, and optionally outputs the route.

---

## 🧠 Key Features

- Custom string class (`Strings`) instead of `std::string`
- Manual memory handling – no STL containers or smart pointers
- Dynamic map parsing and adjacency matrix creation
- Combined use of:
  - DFS for road path discovery
  - Dijkstra’s algorithm for shortest paths
- Optional output of full travel path (city-by-city)


