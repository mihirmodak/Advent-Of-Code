/*
 * Code generated using Google Bard
 * For Advent of Code Day 13
 * Available at
 * https://g.co/bard/share/502076908afa
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>

using namespace std;

struct Person {
  string name;
  vector<int> happiness_units;
};

bool compare_persons_by_happiness(Person p1, Person p2) {
  return p1.happiness_units.size() > p2.happiness_units.size();
}

vector<Person> parse_data(ifstream& input_file) {

    vector<Person> people;

    regex line_pattern("(\\w+) would (gain|lose) (\\d+) happiness units by sitting next to (\\w+)");

    // Read each line of the text file
    string line;
    while (getline(input_file, line)) {

        smatch match;
        string name1, name2, gain;
        int happiness;
        if (regex_match(line, match, line_pattern)) {
            // Extract the name of the person, the happiness units they gain or lose, and the name of the person they sit next to
            name1 = match[1];
            gain= match[2];
            happiness = stoi(match[3]);
            name2 = match[4];
        }

        // Find the people in the vector
        Person* person1 = nullptr;
        Person* person2 = nullptr;
        for (Person& person : people) {
            if (person.name == name1) {
                person1 = &person;
            } else if (person.name == name2) {
                person2 = &person;
            }
        }

        // If the people are not in the vector, create them
        if (person1 == nullptr) {
        people.push_back(Person{name1, vector<int>()});
        person1 = &people.back();
        }
        if (person2 == nullptr) {
        people.push_back(Person{name2, vector<int>()});
        person2 = &people.back();
        }

        // Add the happiness units to the vectors
        person1->happiness_units.push_back(happiness);
        person2->happiness_units.push_back(-happiness);
    }

    return people;

}

int main() {
    // Read the data from the text file
    ifstream input_file("/Users/mihir/Library/CloudStorage/OneDrive-Personal/Programs/Advent of Code/Advent of Code 2015/day13/data.txt");

    if (!input_file.is_open()) {
        cout << "Error: Could not open the input file" << endl;
        return 1;
    }

    vector<Person> people = parse_data(input_file);

    // Sort the people by the number of happiness units they can gain
    sort(people.begin(), people.end(), compare_persons_by_happiness);

    // Find the optimal arrangement of people
    vector<Person> arrangement;
    int max_happiness = 0;
    while (people.size() > 0) {
        // Get the person with the most happiness units
        Person person = people.back();
        people.pop_back();

        // Find the best place to seat the person
        int best_happiness = 0;
        int best_index = -1;
        for (size_t i = 0; i < people.size(); i++) {
            int happiness = person.happiness_units[i];
            if (happiness > best_happiness) {
                best_happiness = happiness;
                best_index = i;
            }
        }

        // Seat the person
        arrangement.insert(arrangement.begin() + best_index + 1, person);

        // Update the max happiness
        max_happiness += best_happiness;
    }

    // Print the optimal arrangement of people and the total gain of happiness units
    cout << "Optimal arrangement of people:" << endl;
    for (Person person : arrangement) {
    cout << person.name << endl;
    }
    cout << "Total gain of happiness units: " << max_happiness << endl;

    return 0;
}