<h1 align="center">Roommate Finder System</h1>
<p align="center"><strong>A comprehensive command-line system designed to match roommates based on behavioral compatibility.</strong></p>

---

<p align="center">
  <img src="https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++" />
  <img src="https://img.shields.io/badge/Console_App-4D4D4D?style=for-the-badge&logo=windows-terminal&logoColor=white" alt="Console App" />
</p>

---

## Overview / Problem Statement
Finding compatible roommates is often a trial-and-error process fraught with friction. **Roommate Finder System** aims to solve this by providing a structured, quantifiable way to match individuals. Built entirely in C++, it evaluates users across dimensions like cleanliness, sleep schedules, and study habits to propose the most compatible living arrangements.

## Key Features
- **User & Admin Portals**: Dedicated executable workflows for standard users (registration, match requests) and administrators (system management).
- **Compatibility Algorithm**: Computes match suitability scores based on multiple lifestyle factors.
- **Match Request System**: Allows users to view potential roommates and send/receive/accept match requests.
- **Persistent Data Storage**: Uses structured text files (`users.txt`, `matches.txt`) for lightweight, offline data persistence without requiring a database server.

## Architecture & Workflow
1. **User Input**: Users register and input their lifestyle preferences via `user_system.exe`.
2. **Data Persistence**: Data is serialized to `data/*.txt` files securely.
3. **Match Engine**: The C++ algorithm parses user files to find intersections in lifestyle habits.
4. **Admin Verification**: Administrators oversee match requests and system logs via `admin_system.exe`.

## Directory Structure
```text
RoommateFinderSystem/
├── data/
│   ├── match_requests.txt     # Serialized pending/accepted requests
│   ├── matches.txt            # Finalized matches data
│   └── users.txt              # Registered user profiles
├── outputs/                   # Demo screenshots and diagrams
├── admin_system.cpp           # Admin workflow source code
├── admin_system.exe           # Compiled admin executable
├── common.h                   # Shared structs and file I/O utilities
├── user_system.cpp            # User workflow source code
└── user_system.exe            # Compiled user executable
```

## Getting Started & Local Setup

### Prerequisites
- Windows OS (to run the `.exe` files out of the box)
- C++ Compiler (GCC/MinGW or MSVC) if you wish to recompile the source code.

### Step-by-Step Setup
1. **Clone the repository**:
   ```bash
   git clone https://github.com/divit-w/RoommateFinderSystem.git
   cd RoommateFinderSystem
   ```
2. **Run the Application**:
   - Double-click `user_system.exe` to register a new user and explore matches.
   - Double-click `admin_system.exe` to manage the system.
3. **Compile from Source (Optional)**:
   ```bash
   g++ user_system.cpp -o user_system.exe
   g++ admin_system.cpp -o admin_system.exe
   ```

## License & Credits
- **Author**: divit-w
- **License**: MIT License
