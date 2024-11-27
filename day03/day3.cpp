#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

class Claus {
    public:
        vector<int> coords = {0,0};
        map<vector<int>, int> history; // maps are the c++ version of dicts
        void move(char instruction) {
            switch (instruction) {
                case '^': 
                    coords[1]++;
                    break;
                case 'v': 
                    coords[1]--;
                    break;
                case '>': 
                    coords[0]++;
                    break;
                case '<': 
                    coords[0]--;
                    break;
            }
        }
        // void present_delivered(map<vector<int>, int> houses) {
        //     map<vector<int>, int>::iterator itr = houses.find(coords);
        //     if ( itr == houses.end() ) {
        //         houses.insert(map<vector<int>, int>::value_type(coords, 1)); // set the new value to 1
        //     } else {
        //             // increment the value (itr->second) by 1
        //             itr->second++;
        //     }
        // }
        // int calculate_multiples() {
        //     int multiples = 0;
        //     map<vector<int>, int>::iterator itr;
        //     for (itr = history.begin(); itr != history.end(); ++itr) {
        //         if (itr->second >= 1) {
        //             multiples++;
        //         }
        //     }
        //     return multiples;
        // }
        string position() {return "(" +  to_string(coords[0]) + ", " + to_string(coords[1]) + ")";}
};

class Area {
    public:
        map< vector<int>, int > houses;
        void present_delivered(Claus c) {
            map<vector<int>, int>::iterator itr = houses.find(c.coords);
            if ( itr == houses.end() ) {
                houses.insert(map<vector<int>, int>::value_type(c.coords, 1)); // set the new value to 1
            } else {
                // increment the value (itr->second) by 1
                itr->second++;
            }
        }
        int calculate_multiples() {
            int multiples = 0;
            map<vector<int>, int>::iterator itr;
            for (itr = houses.begin(); itr != houses.end(); ++itr) {
                if (itr->second >= 1) {
                    multiples++;
                }
            }
            return multiples;
        }
        string status() {
            string result = "";
            for(const auto& elem : houses) {
                result += "(" + to_string(elem.first[0]) + "," + to_string(elem.first[1]) + ") " + to_string(elem.second) + "\n";
            }
            return result;
        }
};

int part1(ifstream & data) {
    string line;
    Claus santa;
    Area houses;
    
    getline(data, line);

    // Deliver a present to the starting house
    houses.present_delivered(santa);

    for (char instruction : line) { // for each instruction

        // parse out the instructions and move to the next set of coords
        santa.move(instruction);
        
        // increment the present counter by 1 for the current set of coordinates
        houses.present_delivered(santa);
    }

    return houses.calculate_multiples();
    
}

int part2(ifstream & data) {
    string line;
    Claus santa, robo;
    Area houses;

    getline(data, line);

    // Deliver a present to the starting house
    houses.present_delivered(santa);
    houses.present_delivered(robo);

    for (int i=0; i < line.length(); i+=2) {

        char santa_instruction = line[i];
        char robo_instruction = line[i+1];

        // parse out the instructions and move to the next house
        santa.move(santa_instruction);
        robo.move(robo_instruction);

        // increment the presnet counter for the current house
        houses.present_delivered(santa);
        houses.present_delivered(robo);
    }

    int multiples = houses.calculate_multiples();
    return multiples;

}


int main() {
    ifstream data ("day3.txt");

    if (data.is_open()) {
        //Part 1
        int multiples1 = part1(data);
        cout << "Part 1 -> The number of houses with at least one present is " << multiples1 << endl;

        // reset file to beginning by clearing out eof and fail flags, then seeking to the beginning of the file
        data.clear(); data.seekg(0);

        //Part 2
        int multiples2 = part2(data);
        cout << "Part 2 -> The number of houses with at least one present is " << multiples2 << endl;
    }

    data.close();

    return 0;
}