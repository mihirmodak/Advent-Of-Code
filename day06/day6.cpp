#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "matrix.hpp"
#include <array>

using namespace std;

vector<string> split(string str, char delim, vector<string>& result) {
    stringstream ss (str);
    string part;

    while (getline(ss, part, delim)) {
        result.push_back(part);
    }

    return result;
}

int part1(ifstream & data) {
    
    Matrix lights (1000,1000);
    string line;

    while (getline(data, line)) {
        // string start, connector, end; 
        vector <string> parts;
        split(line, ' ', parts);
        string end_str = *(parts.rbegin());
        string connector = *(parts.rbegin()+1);
        string start_str = *(parts.rbegin()+2);
        string instruction = *(parts.rbegin()+3); // don't need "turn off", just "off" works

        vector<string> start_vec, end_vec;
        split(start_str, ',', start_vec);
        split(end_str, ',', end_vec);

        if (instruction == "off") {
            off( stoi(start_vec[0]),stoi(start_vec[1]), stoi(end_vec[0]),stoi(end_vec[1]), lights );
        } else if (instruction == "on") {
            on( stoi(start_vec[0]),stoi(start_vec[1]), stoi(end_vec[0]),stoi(end_vec[1]), lights );
        } else if (instruction == "toggle") {
            toggle( stoi(start_vec[0]),stoi(start_vec[1]), stoi(end_vec[0]),stoi(end_vec[1]), lights );
        } else {
            string msg = "Unknown instruction: " + instruction;
            throw invalid_argument(msg);
        }

    }

    int num_lights_on = 0;

    for (int i : lights.getValues()) {
        num_lights_on += i;
    }

    return num_lights_on;

}

int part2(ifstream & data) {

    Matrix lights (1000,1000);
    string line;

    while (getline(data, line)) {
        // string start, connector, end; 
        vector <string> parts;
        split(line, ' ', parts);
        string end_str = *(parts.rbegin());
        string connector = *(parts.rbegin()+1);
        string start_str = *(parts.rbegin()+2);
        string instruction = *(parts.rbegin()+3); // don't need "turn off", just "off" works

        vector<string> start_vec, end_vec;
        split(start_str, ',', start_vec);
        split(end_str, ',', end_vec);

        if (instruction == "off") {
            adjustBrightness( -1, stoi(start_vec[0]),stoi(start_vec[1]), stoi(end_vec[0]),stoi(end_vec[1]), lights );
        } else if (instruction == "on") {
            adjustBrightness( 1, stoi(start_vec[0]),stoi(start_vec[1]), stoi(end_vec[0]),stoi(end_vec[1]), lights );
        } else if (instruction == "toggle") {
            adjustBrightness( 2, stoi(start_vec[0]),stoi(start_vec[1]), stoi(end_vec[0]),stoi(end_vec[1]), lights );
        } else {
            string msg = "Unknown instruction: " + instruction;
            throw invalid_argument(msg);
        }

        // lights.show();

    }

    int num_lights_on = 0;

    for (int i : lights.getValues()) {
        num_lights_on += i;
    }

    return num_lights_on;
}

int main() {

    ifstream data ("day6.txt");

    if (data.is_open()) {
        
        // Part 1
        int lit = part1(data);
        cout << "Part 1 -> There are " << lit << " lights turned on." << endl;

        // reset file to beginning by clearing out eof and fail flags, then seeking to the beginning of the file
        data.clear(); data.seekg(0);

        int lit2 = part2(data);
        cout << "Part 2 -> There are " << lit2 << " lights turned on." << endl;

    }

    data.close();

    return 0;
}