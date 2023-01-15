#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int day1_1(string input) {
    int floor = 0;
    for (int i=0; i < input.length(); i++) {
        if (input[i] == '(') {
            floor++;
        } else if (input[i] == ')') {
            floor--;
        }
    }
    return floor;
}

int day1_2(string input) {
    int char_count;
    int floor = 0;
    // using the line from before

    cout << input.length() << endl;

    for (char_count=0; char_count < input.length(); char_count++) {

        if (input[char_count] == '(') {
            floor++;
        } else if (input[char_count] == ')') {
            floor--;
        }

        if (floor < 0) {
            break;
            // this causes the loop to break with char_count = the index of the character that caused floor < 0
            // The position of the character is char_count + 1
        }
    }
    return char_count;
}

void day1() {
    ifstream data ("data/day1.txt");
    string line;

    if (data.is_open()) {
        getline(data, line);

        // Part 1
        int result1 = day1_1(line);
        cout << "Part 1 -> Santa ends up at floor " << result1 << "." << endl; 

        // Part 2
        int result2 = day1_2(line);
        cout << "Part 2 -> Santa enters the basement at character " << result2+1 << "." <<endl;
    }

    data.close();

}

