# 🚀 RoverRun

> Pathfinding algorithm for a Mars rover navigating a terrain map — Algo 2 Project, EFREI Paris (S3, 2024–2025)

---

## 📌 Overview

RoverRun simulates a Mars rover that must find its way back to a **base station** on a grid-based terrain map. The rover has a limited set of randomly drawn moves and must use a **decision tree** to determine the optimal sequence of moves that minimizes the total traversal cost.

The project focuses on implementing core **data structures from scratch** in C and applying them to a concrete pathfinding problem.

---

## 🗺️ How It Works

The map is a grid where each cell has a **terrain type** with an associated traversal cost:

| Terrain       | Code | Cost  |
|---------------|------|-------|
| Base Station  | 0    | 0     |
| Plain         | 1    | 1     |
| Erg (sand)    | 2    | 2     |
| Reg (gravel)  | 3    | 4     |
| Crevasse      | 4    | 10000 |

The rover:
1. Starts at a given position and orientation (N/S/E/W)
2. Receives a random set of possible moves (Forward 10/20/30m, Backward 10m, Turn Left/Right, U-Turn)
3. Builds a **decision tree** of all possible move sequences
4. Finds the **path with the minimum cost** to reach the base station

---

## 🏗️ Data Structures Implemented

All data structures are implemented from scratch in C (no external libraries):

- **Stack** (`stack.c / stack.h`) — used for tree traversal
- **Queue** (`queue.c / queue.h`) — used for BFS exploration
- **Tree** (`tree.c / tree.h`) — decision tree of rover moves
- **Node** (`node.c / node.h`) — tree node with localisation and cost

---

## 📁 Project Structure

```
RoverRun/
├── main.c              # Entry point, menu, game loop
├── map.c / map.h       # Map loading, terrain costs, display
├── loc.c / loc.h       # Rover localisation (position + orientation)
├── moves.c / moves.h   # Move types and localisation updates
├── tree.c / tree.h     # Decision tree construction and pathfinding
├── node.c / node.h     # Tree node structure
├── stack.c / stack.h   # Stack implementation
├── queue.c / queue.h   # Queue implementation
├── draw.c / draw.h     # Random move drawing
├── maps/               # Example map files (.map)
└── CMakeLists.txt      # Build configuration
```

---

## ⚙️ Build & Run

**Requirements:** GCC or any C compiler, CMake (optional)

```bash
# Clone the repo
git clone https://github.com/maliklahrichi/RoverRun.git
cd RoverRun

# Compile manually
gcc -o roverrun main.c map.c loc.c moves.c tree.c node.c stack.c queue.c draw.c

# Run
./roverrun
```

---

## 🗂️ Map Format

Maps are stored as `.map` files:

```
7        ← number of rows
6        ← number of columns
3 2 2 1 4 3
2 1 0 1 3 3   ← 0 = base station
...
```

---

## 🧠 Key Algorithms

- **Decision tree construction** — recursive generation of all move sequences up to a fixed depth
- **Minimum cost leaf search** — finds the leaf node with the lowest cumulative terrain cost
- **Pathfinding to base** — traces back the optimal path from the best leaf to the root

---

## 👥 Team

Project realized as part of the **Algorithmics 2** course at **EFREI Paris** (Semester 3, 2024–2025).

---
