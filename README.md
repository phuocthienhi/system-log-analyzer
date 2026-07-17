# System Log Analyzer

A high-performance system log analysis and query tool written in **C++**, leveraging optimized data structures and algorithms to handle large-scale datasets efficiently.

## Key Features
- **Modular Architecture:** Clean separation between data definitions (`analyzer.h`), core logic (`analyzer.cpp`), and the execution entry point (`main.cpp`).
- **Robust String Parsing:** Structured parsing of raw `.log` lines into standard C++ structures (`Struct`).
- **Optimized Range Search:** Utilizes **Binary Search** (`std::lower_bound` and `std::upper_bound`) to isolate specific time frames in `O(log N)` time complexity.
- **Instant Error Analytics:** Implements a **Prefix Sum** array to calculate total critical errors (`ERROR` / `CRITICAL`) within any given range in absolute `O(1)` time complexity.

##  Getting Started

### 1. Compile the Project
Build the entire source tree using the `g++` compiler:
```bash
g++ src/main.cpp src/analyzer.cpp -o LogAnalyzer.exe
```
### 2. Run the Executable
Execute the compiled binary to process logs:

```Bash
.\LogAnalyzer.exe
```
---

##  Author

- **ThienLQD** - *Computer science students from Le Quy Don High School for the Gifted* - [GitHub Profile](https://github.com/phuocthienhi)