# Cz-Thermal-Stress-Solver (C++)

![Status](https://img.shields.io/badge/Status-In%20Development-yellow)
![Language](https://img.shields.io/badge/Language-C%2B%2B-blue)
![Focus](https://img.shields.io/badge/Focus-Finite%20Element%20Method-red)

## 📌 Overview
A lightweight, ground-up implementation of a **Finite Element Solver** written in C++. 
This project is a study in computational mechanics, moving from 1D elasticity to **2D Thermal Stress analysis** (relevant to Silicon Crystal Growth/Czochralski processes).

**Goal:** To build a transparent, pointer-based FEM engine without reliance on "black box" commercial libraries, demonstrating core competency in numerical methods and memory management.

## 🚀 Current Progress (Phase 1)
The core architecture is being built using an Object-Oriented approach.

- [x] **Git Architecture:** Repository set up with meaningful commit history.
- [x] **Mesh Data Structures:** - `Node` class (Coordinates & DOF).
    - `Element` class (Connectivity via Pointers).
- [x] **Connectivity Logic:** Efficient memory management using `Node*` pointers to avoid data duplication.
- [ ] **Stiffness Matrix:** Assembly of local $K$ matrices (Coming Soon).
- [ ] **Solver:** Gaussian Elimination / Linear Algebra solver.

## 🗺️ Roadmap (90-Day Plan)
| Phase | Focus | Status |
| :--- | :--- | :--- |
| **Phase 1** | **1D/2D Elastic Solver** | 🚧 In Progress |
| **Phase 2** | **2D Thermal Stress (Plane Strain)** | ⏳ Pending |
| **Phase 3** | **Performance Optimization** | ⏳ Pending |
| **Phase 4** | **AI/PINN Comparison (Python)** | ⏳ Pending |

## 🛠️ Build & Run
This project uses `g++` (MinGW) for compilation.

```bash
# Clone the repository
git clone [https://github.com/YourUsername/Cz-Thermal-Stress-Solver.git](https://github.com/YourUsername/Cz-Thermal-Stress-Solver.git)

# Compile
g++ main.cpp -o solver

# Run
./solver