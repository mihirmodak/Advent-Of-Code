#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

class Distance {
    public:
        // properties
        string source;
        string destination;
        int length;
        
        // Utility functions
        void print() {
            cout << source << " to " << destination << " = " << length << endl;
        }

        void clear() {
            this->source = "";
            this->destination = "";
            this->length = 0;
        }

        static bool compareByLength(const Distance& self, const Distance& other) {
            return self.length < other.length;
        }

        // Constructors
        Distance () {}
        Distance (string source_value, string destination_value, int length_value) : source(source_value), destination(destination_value), length(length_value) {}
};

bool comparePathsByLength(const pair<string,int> self, const pair<string,int> other) {
    return self.second < other.second;
}

vector<Distance> filterKeepDistancesBySource(const vector<Distance>& distances, const string& desired_source) {
    vector<Distance> filtered_distances;

    for (const Distance& distance : distances) {
        if (distance.source == desired_source) {
            filtered_distances.push_back(distance);
        }
    }

    return filtered_distances;
}

vector<Distance> filterRemoveDistancesBySource(const vector<Distance>& distances, const string& source_to_remove) {
    vector<Distance> filtered_distances;

    for (const Distance& distance : distances) {
        if (distance.source != source_to_remove) {
            filtered_distances.push_back(distance);
        }
    }

    return filtered_distances;
}

vector<Distance> filterRemoveDistancesByDestination(const vector<Distance>& distances, const string& destination_to_remove) {
    vector<Distance> filtered_distances;

    for (const Distance& distance : distances) {
        if (distance.destination != destination_to_remove) {
            filtered_distances.push_back(distance);
        }
    }

    return filtered_distances;
}

Distance greedyPathStepDecider(const string& current_node_name, vector<Distance>& distances, string mode) {

    // Filter distances to keep only those that have source at current_node_name
    vector<Distance> filtered_distances = filterKeepDistancesBySource(distances, current_node_name);

    if (filtered_distances.empty()) {
        // Handle the case when the vector is empty
        throw logic_error("Vector is empty when filtering for distances starting at " + current_node_name);
    } 

    // Get the Distance with the smallest length and return it
    if (mode == "min_distance") {
        auto distance_to_next_node_iterator = min_element(filtered_distances.begin(), filtered_distances.end(), Distance::compareByLength);
        return *distance_to_next_node_iterator;
    } else if (mode == "max_distance") {
        auto distance_to_next_node_iterator = max_element(filtered_distances.begin(), filtered_distances.end(), Distance::compareByLength);
        return *distance_to_next_node_iterator;
    } else {
        throw logic_error("Invalid entry for mode: " + mode + ". Must be either min_distance or max_distance.");
    }
    
}

pair<string, int> greedyPathFinder(const string& start_node_name,  vector<Distance> distances, set<string> locations, string mode) {

    size_t iteration_counter = 0;
    string full_path = start_node_name;
    int running_total_distance = 0;
    Distance next_step_distance;
    next_step_distance.destination = start_node_name;

    while (distances.size() > 0) {

        
        // I used the stones to destroy the stones
        // Use the destination of the previous step as the source of the next one
        // Then assign the calculated step to the same variable
        bool exception_caught = false;
        try{
            next_step_distance = greedyPathStepDecider(next_step_distance.destination, distances, mode);
        } catch (logic_error) {
            exception_caught = true;
            break;
        }

        // if the greedyPathStepDecider did not fail
        if (!exception_caught) {
            distances = filterRemoveDistancesByDestination(distances, next_step_distance.source);

            full_path += (" -> " + next_step_distance.destination);
            running_total_distance += next_step_distance.length;
        }

    }

    cout << full_path << " = " << running_total_distance << endl;

    return make_pair(full_path, running_total_distance);

}

    /* 
    For every unique location in the locations set, find the shortest path that covers all the other locations
        i.e. the shortest path that has locations.size()-1 nodes.
        for every `entry` in locations:
            1. get a filtered version of distances where the source is `entry`
            2. choose the shortest distance among those and add it to the record
            3. Create a filtered version of locations where the current one and the shortest distance one are removed.
            4. Repeat 1-3 until the length of the record is equal to locations(original).size()-1

    */

int part1(ifstream& data) {

    string line, buffer_word, equal_sign;
    vector<Distance> distances;
    set<string> locations;
    istringstream path_code_stringstream;
    Distance new_distance, reverse_new_distance;

    // build the locations set and distances vector
    while(getline(data, line)) {
        
        // Each line will be of the form: source to destination = length
        // Initialize the stringstream with the data from the line
        path_code_stringstream.clear();
        path_code_stringstream.str(line);

        // Reset the Distance object and add the new values
        new_distance.clear();
        path_code_stringstream >> new_distance.source >> buffer_word >> new_distance.destination >> equal_sign >> new_distance.length;

        // Reset the istringstream to the start
        path_code_stringstream.seekg(0);

        // Update the reverse new distance for the reverse journey with the same distance
        reverse_new_distance.clear();
        path_code_stringstream >> reverse_new_distance.destination >> buffer_word >> reverse_new_distance.source >> equal_sign >> reverse_new_distance.length;

        // // Debugging
        // new_distance.print();
        // cout << new_distance.length*2 << "\n"; // Verify that the length was being read in as a numeric type

        // Add the distance to the global vector of distances
        distances.push_back(new_distance);
        distances.push_back(reverse_new_distance);

        // Add the source and destination to the locations set (ignores duplicates)
        locations.insert(new_distance.source);
        locations.insert(new_distance.destination);

    }

   vector<pair<string, int>> paths;

    // // Debugging
    // auto [path, path_distance] = greedyPathFinder("London", distances, locations);
    // return 0;

    for (string starting_location : locations) {
        cout << "\nStarting Location: " << starting_location << endl;
        pair<string, int> curr_shortest_path = greedyPathFinder(starting_location, distances, locations, "min_distance");
        paths.push_back(curr_shortest_path);
    }

    // Get the Distance with the smallest length and return it
    auto minimum_distance_to_next_node_iterator = min_element(paths.begin(), paths.end(), comparePathsByLength);
    pair<string,int> shortest_path = *minimum_distance_to_next_node_iterator;
    cout << "\n" << shortest_path.first << " = " << shortest_path.second << endl;
    return shortest_path.second;

}

int part2(ifstream& data) {

    string line, buffer_word, equal_sign;
    vector<Distance> distances;
    set<string> locations;
    istringstream path_code_stringstream;
    Distance new_distance, reverse_new_distance;

    // build the locations set and distances vector
    while(getline(data, line)) {
        
        // Each line will be of the form: source to destination = length
        // Initialize the stringstream with the data from the line
        path_code_stringstream.clear();
        path_code_stringstream.str(line);

        // Reset the Distance object and add the new values
        new_distance.clear();
        path_code_stringstream >> new_distance.source >> buffer_word >> new_distance.destination >> equal_sign >> new_distance.length;

        // Reset the istringstream to the start
        path_code_stringstream.seekg(0);

        // Update the reverse new distance for the reverse journey with the same distance
        reverse_new_distance.clear();
        path_code_stringstream >> reverse_new_distance.destination >> buffer_word >> reverse_new_distance.source >> equal_sign >> reverse_new_distance.length;

        // // Debugging
        // new_distance.print();
        // cout << new_distance.length*2 << "\n"; // Verify that the length was being read in as a numeric type

        // Add the distance to the global vector of distances
        distances.push_back(new_distance);
        distances.push_back(reverse_new_distance);

        // Add the source and destination to the locations set (ignores duplicates)
        locations.insert(new_distance.source);
        locations.insert(new_distance.destination);

    }

   vector<pair<string, int>> paths;

    // // Debugging
    // auto [path, path_distance] = greedyPathFinder("London", distances, locations);
    // return 0;

    for (string starting_location : locations) {
        cout << "\nStarting Location: " << starting_location << endl;
        pair<string, int> curr_shortest_path = greedyPathFinder(starting_location, distances, locations, "max_distance");
        paths.push_back(curr_shortest_path);
    }

    // Get the Distance with the smallest length and return it
    auto minimum_distance_to_next_node_iterator = max_element(paths.begin(), paths.end(), comparePathsByLength);
    pair<string,int> shortest_path = *minimum_distance_to_next_node_iterator;
    cout << "\n" << shortest_path.first << " = " << shortest_path.second << endl;
    return shortest_path.second;

}


int main() {
    ifstream data ("day9.txt");

    if (data.is_open()) {
        
        // Part 1
        int path_length1 = part1(data);
        cout << "Part 1 -> " << path_length1 << endl;

        // reset file to beginning by clearing out eof and fail flags, then seeking to the beginning of the file
        data.clear(); data.seekg(0);

        // Part 2
        int path_length2 = part2(data);
        cout << "Part 2 -> " << path_length2 << endl;

    }

    data.close();

    system("pause");
    return 0;
}
