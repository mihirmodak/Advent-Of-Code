#include <iostream>
#include <fstream>

using namespace std;

struct Reindeer {};

int main() {

    ifstream data("/Users/mihir/Library/CloudStorage/OneDrive-Personal/Programs/Advent of Code/Advent of Code 2015/day14/data.txt");
    if (!data.is_open()) {
        cout << "Error: Could not open the input file" << endl;
        return 1;
    }

    return 0;
}