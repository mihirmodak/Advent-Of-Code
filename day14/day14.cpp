#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

using namespace std;

// ---- OBJECT AND RELATED FUNCTIONS ----
struct Reindeer {
    string name;
    int flying_speed, flying_time, resting_time;
    int distance = 0, points = 0;

    Reindeer() {}
    Reindeer(string name) : name(name) {}
    Reindeer(string name, int flying_speed, int flying_time, int resting_time) : 
        name(name), flying_speed(flying_speed), flying_time(flying_time), resting_time(resting_time) {};

};
ostream &operator<<(ostream &os, Reindeer const &r) { 
    os << "Reindeer [" << r.name << "] {" << '\n';
    os << "  Flying Speed: " << r.flying_speed << " km/sec\n";
    os << "  Flying Time: " << r.flying_time << " sec\n";
    os << "  Resting Time: " << r.resting_time << " sec\n";
    os << "}";
    return os;
}

// ---- HELPER FUNCTIONS ----
vector<Reindeer> parse_data(ifstream & data) {
    vector<Reindeer> deers;

    regex pattern ("(\\w+) can fly (\\d+) km/s for (\\d+) seconds, but then must rest for (\\d+) seconds.");
    string line, name;
    while (getline(data, line)) {
        smatch match;
        if (regex_search(line, match, pattern)) {
            Reindeer r { match[1].str(), stoi(match[2].str()), stoi(match[3].str()), stoi(match[4].str()) };
            deers.push_back(r);
        }
    }

    return deers;
}

void simulate_full_travel(Reindeer & r, const int timeTaken) {

    for (int currentTime = 0; currentTime < timeTaken; currentTime++) {
        
        if (currentTime % (r.flying_time+r.resting_time) < r.flying_time | currentTime < r.flying_time) {
            r.distance += r.flying_speed;
        } 

    }

}
Reindeer * calculate_farthest_reindeer(vector<Reindeer> & deers, const int secondsTravelled) {
    int max_distance_travelled;
    Reindeer * farthest_reindeer;

    cout << "All Reindeer:\n";
    for (Reindeer & rd: deers) {
        simulate_full_travel(rd, secondsTravelled);

        if (rd.distance > max_distance_travelled) {
            max_distance_travelled = rd.distance;
            farthest_reindeer = & rd;
        }

        cout << "Reindeer " << rd.name << " | " << rd.distance  << endl;
    }

    return farthest_reindeer;
}

int get_max_speed(vector<Reindeer> deers) {
    int max_speed = 0;

    for(Reindeer r : deers) {
        if (r.flying_speed > max_speed) {
            max_speed = r.flying_speed;
        }
    }

    return max_speed;
}
Reindeer * calculate_most_points(vector<Reindeer> & deers, const int secondsTravelled) {
    int max_distance = get_max_speed(deers);    // The initial max_distance should be equal to the farthest deer after second 1
                                                // That way the fastest deer (which should have gone the farthest after 1 second) gets the first point
    int max_points = 0;
    Reindeer * most_points_reindeer;


    for (int currentTime = 0; currentTime < secondsTravelled; currentTime++) {

        // First calculate all the distances for the current second and set the max_distance
        for (Reindeer & rd : deers) {
            if (currentTime % (rd.flying_time+rd.resting_time) < rd.flying_time | currentTime < rd.flying_time) {
                rd.distance += rd.flying_speed;
            } 
            if (rd.distance >= max_distance) {
                max_distance = rd.distance;
            }
        }

        // Based on the max_distance for the current second, award points
        for (Reindeer & rd : deers) {
            if (rd.distance >= max_distance) {
                rd.points++;
            }
        }
    }


    for (Reindeer & rd : deers) {
        if (rd.points > max_points) {
            max_points = rd.points;
            most_points_reindeer = & rd;
        }
        cout << "Reindeer " << rd.name << " | Distance: " << rd.distance << " | Points: " << rd.points  << endl;
    }

    return most_points_reindeer;
}

int main() {

    ifstream data("/Users/mihir/Library/CloudStorage/OneDrive-Personal/Programs/Advent of Code/Advent of Code 2015/day14/data.txt");
    if (!data.is_open()) {
        cout << "Error: Could not open the input file" << endl;
        return 1;
    }

    string secondsTravelledString;
    int secondsTravelled;
    cout << "Enter the total time: ";
    cin >> secondsTravelledString;
    cout << endl;
    secondsTravelled = stoi(secondsTravelledString);
    

    vector<Reindeer> deers1 = parse_data(data);
    Reindeer * farthest_reindeer = calculate_farthest_reindeer(deers1, secondsTravelled);
    cout << "\nReindeer " << farthest_reindeer->name << " travelled " << farthest_reindeer->distance << " km in " << secondsTravelled << " seconds.\n\n" << endl;

    // reset file to beginning by clearing out eof and fail flags, then seeking to the beginning of the file
    data.clear(); data.seekg(0);

    vector<Reindeer> deers2 = parse_data(data);
    Reindeer * most_points_reindeer = calculate_most_points(deers2, secondsTravelled);
    cout << "\nReindeer " << most_points_reindeer->name << " had " << most_points_reindeer->points << " points in " << secondsTravelled << " seconds.\n\n" << endl;

    return 0;
}