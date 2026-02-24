![Banner](https://cdn.thenewstack.io/media/2021/12/521cd034-advent-of-code-2021.jpg)

![Last Commit](https://img.shields.io/github/last-commit/mihirmodak/Advent-Of-Code)
![Commits](https://img.shields.io/github/commit-activity/t/mihirmodak/Advent-Of-Code/2015)

The [Advent of Code](https://adventofcode.com) is an annual series of programming puzzles released daily from December 1–25. The difficulty ramps up as the month progresses, covering topics from string parsing and graph traversal to dynamic programming and simulation.

## How This Repo Is Organized

Each year's solutions live on their own branch, named by year (e.g. [`2015`](https://github.com/mihirmodak/Advent-Of-Code/tree/2015)). Within each branch:

- Each day has its own folder (`day01/`, `day02/`, …)
- Each folder contains the solution source file and the puzzle input (`data.txt`)
- Both parts of a day's puzzle are solved in the same source file, with each part's result printed separately
- Each branch has its own README with language-specific setup instructions

To browse a specific year, switch to its branch or click the year link in the table above.

## Running the Code

These solutions use [CMake](https://cmake.org). From the root of the `2015` branch:

```bash
cmake -S . -B build
cmake --build build
./build/dayXX/dayXX   # replace XX with the day number, e.g. day01
```

Each binary reads its puzzle input from `data.txt` in the corresponding day folder and prints the answers for both parts.

An easier way to do this from Visual Studio code is to use the `Code Runner` extension. Add the following line to the extension settings' **Executor Map**:

```json
"code-runner.executorMap": {
    ...
    "cpp": "cd $dir && clang++ -O2 -std=c++20 $fileName -o $fileNameWithoutExt -I/opt/homebrew/opt/openssl@3/include -L/opt/homebrew/opt/openssl@3/lib -lssl -lcrypto && ./$fileNameWithoutExt",
    ...
}
```
