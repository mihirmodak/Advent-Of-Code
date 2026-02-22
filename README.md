<!-- ![Banner](./assets/banner.png) -->

# Advent of Code

![Last Commit](https://img.shields.io/github/last-commit/mihirmodak/Advent-Of-Code)


[Advent of Code](https://adventofcode.com) is an annual series of programming puzzles released daily from December 1–25. The difficulty ramps up as the month progresses, covering topics from string parsing and graph traversal to dynamic programming and simulation.

## Challenge Index

Year | Language | Status
---- | -------- | ------
[2015](https://github.com/mihirmodak/Advent-Of-Code/tree/2015) | `C/C++` | 🟡&nbsp;&nbsp;In Progress
2016 | `Java` | 🔴&nbsp;&nbsp;Not Started
2017 | `Python` | 🔴&nbsp;&nbsp;Not Started
2018 | `Swift` | 🔴&nbsp;&nbsp;Not Started
2019 | `Rust` | 🔴&nbsp;&nbsp;Not Started
2020 | `JavaScript` | 🔴&nbsp;&nbsp;Not Started
2021 | `C#` | 🔴&nbsp;&nbsp;Not Started
2022 | TBD | 🔴&nbsp;&nbsp;Not Started
2023 | TBD | 🔴&nbsp;&nbsp;Not Started
2024 | TBD | 🔴&nbsp;&nbsp;Not Started

**Status legend:** 🟢&nbsp;Complete &nbsp;|&nbsp; 🟡&nbsp;In Progress &nbsp;|&nbsp; 🔴&nbsp;Not Started

## How This Repo Is Organized

Each year's solutions live on their own branch, named by year (e.g. [`2015`](https://github.com/mihirmodak/Advent-Of-Code/tree/2015)). Within each branch:

- Each day has its own folder (`day01/`, `day02/`, …)
- Each folder contains the solution source file and the puzzle input (`data.txt`)
- Both parts of a day's puzzle are solved in the same source file, with each part's result printed separately
- Each branch has its own README with language-specific setup instructions

To browse a specific year, switch to its branch or click the year link in the table above.

## Running the Code

### 2015 — C++ (C++20)

The 2015 solutions use [CMake](https://cmake.org). From the root of the `2015` branch:

```bash
cmake -S . -B build
cmake --build build
./build/dayXX/dayXX   # replace XX with the day number, e.g. day01
```

Each binary reads its puzzle input from `data.txt` in the corresponding day folder and prints the answers for both parts.

> Other years will document their own build and run steps in their branch READMEs as solutions are added.

## Up Next

**2016 — Java**

The plan for 2016 is to work through the challenges in Java, leaning into object-oriented design patterns and the standard library. Solutions will appear on the [`2016`](https://github.com/mihirmodak/Advent-Of-Code/tree/2016) branch once started.
