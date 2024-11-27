#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int part1(ifstream & data) {
    string line, lstr, wstr, hstr;
    int total_area = 0;

    while (getline(data, line)) {
        stringstream linestream (line);

        getline(linestream, lstr, 'x');
        getline(linestream, wstr, 'x');
        getline(linestream, hstr, 'x');

        int l = stoi(lstr); int w = stoi(wstr); int h = stoi(hstr);

        int lw = l*w;
        int lh = l*h;
        int wh = w*h;

        int extra = min( min(lw, lh), wh);

        int area = 2* (lw + lh + wh) + extra;

        total_area += area;

    }

    return total_area;
}

int part2(ifstream & data) {
    int total_ribbon = 0;
    string line, lstr, wstr, hstr;

    while (getline(data,line)) {
        stringstream linestream (line);

        getline(linestream, lstr, 'x');
        getline(linestream, wstr, 'x');
        getline(linestream, hstr, 'x');

        int l = stoi(lstr); int w = stoi(wstr); int h = stoi(hstr);


        // find the smallest perimeter by
        // - adding up all 3 measurements
        // - and subtracting the longest one
        // - then doubling the result
        int smallest_perim = 2* (l + w + h - max( max(l,w), h ));
        int bow = l*w*h;

        total_ribbon += smallest_perim + bow; 
    }

    return total_ribbon;
}

int main() {
    ifstream data ("day2.txt");

    if (data.is_open()) {
        // Part 1
        int total_area = part1(data);
        cout << "Part 1 -> The total area needed is " << total_area << " sq. ft." << endl;

        // reset file to beginning by clearing out eof and fail flags, then seeking to the beginning of the file
        data.clear(); data.seekg(0);

        // Part 2
        int total_ribbon = part2(data);
        cout << "Part 2 -> The total length of ribbon needed is " << total_ribbon << " ft." << endl;
    }

    data.close();

    return 0;
}

