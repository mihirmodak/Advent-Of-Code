#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <regex>

using namespace std;

// ---------- OBJECTS ----------
struct Person {
    string name;
    map<string, int> happiness;

    Person(string name) : name(name), happiness() {} // Allow initializing Person with an empty happiness map
    Person(string name, map<string, int> happiness) : name(name), happiness(happiness) {}

    // Overloaded operator< for comparing Person objects based on name
    bool operator<(const Person& other) const {
        return name < other.name;
    }
};

// ---------- UTILITY FUNCTIONS ----------

template <typename T>
void print(T t) {
    cout << t << endl;
}

template <typename T>
void print(vector<T> v) {

    if (v.size() == 0) {
        cout << "[]" << endl;
    } else {
        cout << "[" << v[0];
        for (size_t i = 1; i < v.size(); i++) {
            cout << ", " << v[i];
        }
        cout << "]" << endl;
    }
}
void print(vector<Person> v) {

    if (v.size() == 0) {
        cout << "[]" << endl;
    } else {
        cout << "[" << v[0].name;
        for (size_t i = 1; i < v.size(); i++) {
            cout << ", " << v[i].name;
        }
        cout << "]" << endl;
    }
}

template <typename T1, typename T2>
void print(map<T1, T2> m, bool separate_variables = false) {

    if (m.size() == 0) {
        cout << "{}" << endl;
    } else {
        if (separate_variables) {
            cout << "{"
                << "\n  ";
        } else {
            cout << "{"
                << "";
        }

        bool first_elem = true;

        for (const std::pair<T1, T2>& p : m) {

            if (separate_variables) {
                cout << (first_elem ? "" : ",\n  ");
                cout << p.first << ": " << p.second;
            } else {
                cout << (first_elem ? "" : ", ");
                cout << p.first << ": " << p.second;
            }

            first_elem = false;
        }

        if (separate_variables) {
            cout << "\n}" << endl;
        } else {
            cout << "}" << endl;
        }
    }
}

// ---------- HELPER FUNCTIONS ----------

/*
 * Finds a Person with name person_name in a vector of Person objects
 * If the person exists, retuns an iterator to that specific Person object
 * If the person does not exist, returns an iterator to the end of the vector
 */
vector<Person>::iterator contains_person(vector<Person>& people, string& person_name) {
    for (auto it = people.begin(); it != people.end(); ++it) {
        if (it->name == person_name) {
            return it;
        }
    }
    return people.end();
}

/*
 * Reads in the data file and generates a vector of Person objects
 * Each person object contains a name and a map of the relative happinesses with every other person
 */
vector<Person> parse_data(ifstream& inputFile) {

    vector<Person> people;

    regex line_pattern("(\\w+) would (gain|lose) (\\d+) happiness units by sitting next to (\\w+)");

    // Read each line of the text file
    string line;
    while (getline(inputFile, line)) {

        // Extract out all the fields
        smatch match;
        string name1, name2;
        int happiness;
        if (regex_search(line, match, line_pattern)) {
            // Extract the name of the person, the happiness units they gain or lose, and the name of the person they sit next to
            name1 = match[1];
            name2 = match[4];

            if (match[2] == "gain") { // match[2] is "gain" or "lose"
                happiness = stoi(match[3]);
            } else {
                happiness = -stoi(match[3]);
            }
        }

        auto it = contains_person(people, name1);

        if (it == people.end()) { // if name1 is not found in `people`
            map<string, int> happinessAssociation = { {name2, happiness} };
            people.push_back(Person{ name1, happinessAssociation });
            it = people.end() - 1;
        } else {
            it->happiness.insert({ name2, happiness });
        }
    }

    return people;
}

/*
 * Takes a permutation, and returns the total happiness in that permutation
 */
int calculate_happiness(vector<Person> permutation) {
    int totalHappiness = 0;
    for (size_t i = 0; i < permutation.size(); i++) // f
    {
        int leftHappiness = 0;
        if (i > 0) {
            leftHappiness = permutation[i].happiness[permutation[i - 1].name];
        } else {
            leftHappiness = permutation[i].happiness[permutation[permutation.size() - 1].name];
        }

        int rightHappiness = 0;
        if (i < permutation.size() - 1) {
            rightHappiness = permutation[i].happiness[permutation[i + 1].name];
        } else {
            rightHappiness = permutation[i].happiness[permutation[0].name];
        }

        totalHappiness += leftHappiness + rightHappiness;
    }
    return totalHappiness;
}

/*
 * Takes the vector of people and goes through all permutations one by one
 * Calculates the Happiness change for each permutation
 * Returns the one with the maximum happiness change
 */
vector<Person> get_best_permutation(vector<Person> people) {
    int maxHappiness = -1e9;
    std::vector<Person> optimalPermutation;

    // Generate all permutations
    next_permutation(people.begin(), people.end());

    // Evaluate each permutation and keep track of the best one
    do {
        int currentHappiness = calculate_happiness(people);
        if (currentHappiness > maxHappiness) {
            maxHappiness = currentHappiness;
            optimalPermutation = people;
        }
    } while (next_permutation(people.begin(), people.end()));

    cout << "The optimal happiness is " << to_string(maxHappiness) << endl;

    return optimalPermutation;
}

int main() {

    ifstream inputFile("/Users/mihir/Library/CloudStorage/OneDrive-Personal/Programs/Advent of Code/Advent of Code 2015/day13/data.txt");

    if (!inputFile.is_open()) {
        cout << "Error: Could not open the input file" << endl;
        return 1;
    }

    vector<Person> people = parse_data(inputFile);
    vector<Person> best = get_best_permutation(people);

    print(best);

    return 0;
}