#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

void day1() {
    ifstream data ("data/day1.txt");
    string line;
    int floor = 0;

    // Part 1

    if (data.is_open()) {
        getline(data, line);

        for (int i=0; i < line.length(); i++) {
            if (line[i] == '(') {
                floor++;
            } else if (line[i] == ')') {
                floor--;
            }
        }
    }

    cout << "Part 1 -> Santa ends up at floor " << floor << "." << endl; 

    // Part 2

    int char_count;
    floor = 0;
    // using the line from before

    for (char_count=0; char_count < line.length(); char_count++) {

        if (line[char_count] == '(') {
            floor++;
        } else if (line[char_count] == ')') {
            floor--;
        }

        if (floor < 0) {
            break;
            // this causes the loop to break with char_count = the index of the character that caused floor < 0
            // The position of the character is char_count + 1
        }

    }

    cout << "Part 2 -> Santa enters the basement at character " << char_count+1 << "." <<endl;

    data.close();

}

void day2() {
    ifstream data ("data/day2.txt");
    string line, lstr, wstr, hstr;
    int total_area = 0;

    // Part 1
    if (data.is_open()) {
        while (getline(data, line)) {
            stringstream linestream (line);

            getline(linestream, lstr, 'x');
            getline(linestream, wstr, 'x');
            getline(linestream, hstr, 'x');

            int l =stoi(lstr); int w = stoi(wstr); int h = stoi(hstr);

            int lw = l*w;
            int lh = l*h;
            int wh = w*h;

            int extra = min( min(lw, lh), wh);

            int area = 2* (lw + lh + wh) + extra;

            total_area += area;

        }
    }

    cout << "Part 1 -> The total area needed is " << total_area << " sq. ft." << endl;

    // Part 2
    int total_ribbon = 0;
    if (data.is_open()) { // use the same data filestream as part 1
        
        // reset file to beginning by clearing out eof and fail flags, then seeking to the beginning of the file
        data.clear(); data.seekg(0);

        // 
        while (getline(data,line)) {
            stringstream linestream (line);

            getline(linestream, lstr, 'x');
            getline(linestream, wstr, 'x');
            getline(linestream, hstr, 'x');

            int l = stoi(lstr); int w = stoi(wstr); int h = stoi(hstr);

            int smallest_perim = 2* (l + w + h - max( max(l,w), h ));
            int bow = l*w*h;

            total_ribbon += smallest_perim + bow; 
        }

        cout << "Part 2 -> The total length of ribbon needed is " << total_ribbon << " ft." << endl;
    }

    data.close();
}

void day3() {
    ifstream data ("data/day3.txt");
    string line;
    int coords[2] = {0,0};
    map<int*, int> coord_ref;

    if (data.is_open()) {
        getline(data, line);

        for (char instruction : line) {

            // parse out the instructions and modify the coordinates accordingly
            if (instruction == '^') { coords[1]++; }
            else if (instruction == 'v') {coords[1]--;}
            else if (instruction == '>') {coords[0]++;}
            else if (instruction == '<') {coords[0]--;}
            
            // if coords is not in coords_ref keys
            if ( coord_ref.find(coords) == coord_ref.end() ) {
                coord_ref[ coords ] = 1; // set the new value to 1
            } else {
                coord_ref[ coords ]++; // increment the value by 1
            }
        }

        cout << coords << endl;
    }
}

int main() {
    day3();
    return 0;
}