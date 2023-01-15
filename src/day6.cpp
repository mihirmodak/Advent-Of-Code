#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <algorithm>
#include "../matrix.hpp"
#include <array>

using namespace std;

vector<string> split(string str, char delim) {
    stringstream ss (str);
    string part;
    vector<string> result;

    while (getline(ss, part, delim)) {
        result.push_back(part);
    }

    return result;
}

int day6_1(ifstream & data) {
    
    Matrix lights (3, 4);
    lights.show();

    int start_coords[2] = {1,0}, end_coords[2] = {1,4};
    vector<int> new_vals = {1,1,1,1};
    lights.replace( start_coords, end_coords, new_vals );
    lights.show();

    int subset_start[] = {1,1};
    int subset_end[] = {2,2};
    Matrix subset = lights.slice( subset_start, subset_end );
    subset.show();
    
    string line;

    while (getline(data, line)) {
        // string start, connector, end; 
        vector <string> parts;

        parts = split(line, ' ');

        string end = *(parts.rbegin());
        string connector = *(parts.rbegin()+1);
        string start = *(parts.rbegin()+2);
        string instruction = *(parts.rbegin()+3); // don't need "turn off", just "off" works





    }

    return 0;

}

void day6() {
    ifstream data ("data/test.txt");

    if (data.is_open()) {
        
        // Part 1
        int lit = day6_1(data);
    }
}

