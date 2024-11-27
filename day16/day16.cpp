#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <format>
#include <vector>
#include <sstream>
#include <array>

// Utility function to trim whitespace
std::string trim(const std::string &str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

class Aunt {
    public:
        int id = 0;
        int children = -1;
        int cats = -1;
        int samoyeds = -1;
        int pomeranians = -1;
        int akitas = -1;
        int vizslas = -1;
        int goldfish = -1;
        int trees = -1;
        int cars = -1;
        int perfumes = -1;


        // Default constructor
        Aunt() {
            initProperties();
        }

        // Copy constructor
        Aunt(const Aunt &other) : id(other.id),
                                  children(other.children),
                                  cats(other.cats),
                                  samoyeds(other.samoyeds),
                                  pomeranians(other.pomeranians),
                                  akitas(other.akitas),
                                  vizslas(other.vizslas),
                                  goldfish(other.goldfish),
                                  trees(other.trees),
                                  cars(other.cars),
                                  perfumes(other.perfumes) {
            initProperties();
        }

        // Assignment operator
        Aunt &operator=(const Aunt &other) {
            if (this != &other) {
                id = other.id;
                children = other.children;
                cats = other.cats;
                samoyeds = other.samoyeds;
                pomeranians = other.pomeranians;
                akitas = other.akitas;
                vizslas = other.vizslas;
                goldfish = other.goldfish;
                trees = other.trees;
                cars = other.cars;
                perfumes = other.perfumes;
                initProperties();
            }
            return *this;
        }

        void set(std::string name, int value) {
            name = trim(name);
            auto it = properties.find(name);
            if (it != properties.end()) {
                *(it->second) = value;
            }
        }

        int get(const std::string &name) {
            auto it = properties.find(trim(name));
            if (it == properties.end()) {
                throw std::runtime_error("No such property");
            }
            return *(it->second);
        }

        std::string repr() const {
            std::string output = std::format("Aunt {} with properties:\n", id);
            for (const auto &[key, value_ptr]: properties) {
                if (*value_ptr != 0) {
                    // Only show non-zero properties
                    output.append(std::format("\t| {}: {}\n", key, *value_ptr));
                }
            }
            return output;
        }

        std::map<std::string, int *> properties;

        void initProperties() {
            properties = {
                {"children", &children},
                {"cats", &cats},
                {"samoyeds", &samoyeds},
                {"pomeranians", &pomeranians},
                {"akitas", &akitas},
                {"vizslas", &vizslas},
                {"goldfish", &goldfish},
                {"trees", &trees},
                {"cars", &cars},
                {"perfumes", &perfumes}
            };
        }
};

std::vector<std::string> split_string(const std::string &s, char delim, const int max_splits = -1) {
    // if max_splits is 0, return the same string in a vector
    if (max_splits == 0) {
        return std::vector{s};
    }

    std::vector<std::string> tokens;

    std::stringstream ss(s);
    std::string token;
    while (std::getline(ss, token, delim)) {
        tokens.push_back(token);

        // If the max_splits threshold is reached
        if (max_splits > 0 && tokens.size() == max_splits) {
            // Read the rest of the stream into a string
            std::string remainder;
            std::getline(ss, remainder); // Read the rest of the stringstream

            // If there was more content, add it to the vector
            // (including the delimiter that was consumed by getline)
            if (!remainder.empty()) {
                tokens.push_back(remainder);
            }
            break;
        }
    }

    return tokens;
}

std::array<Aunt, 501> createAunts(std::ifstream & data) {
    std::array<Aunt, 501> aunts; // 0-500 inclusive

    std::string line;
    while (getline(data, line)) {
        // Get the Aunt ID
        std::vector<std::string> tokens = split_string(line, ':', 1);
        int id = std::stoi(tokens[0].substr(4, tokens[0].size() - 4));

        // Set the ID in the Aunt object
        aunts[id].id = id;

        // Get the properties
        std::vector<std::string> property_tokens = split_string(tokens[1], ',');

        for (const auto &property_token: property_tokens) {
            std::vector<std::string> parsed_property_token = split_string(property_token, ':');
            aunts[id].set(
                trim(parsed_property_token[0]),
                std::stoi(trim(parsed_property_token[1]))
            );
        }

        // std::cout << aunts[id].repr() << std::endl;
    }

    return aunts;
}

Aunt MFCSAM() {
    // Create the reference Aunt with the MFCSAM readings
    Aunt mfcsam_aunt;
    mfcsam_aunt.set("children", 3);
    mfcsam_aunt.set("cats", 7);
    mfcsam_aunt.set("samoyeds", 2);
    mfcsam_aunt.set("pomeranians", 3);
    mfcsam_aunt.set("akitas", 0);
    mfcsam_aunt.set("vizslas", 0);
    mfcsam_aunt.set("goldfish", 5);
    mfcsam_aunt.set("trees", 3);
    mfcsam_aunt.set("cars", 2);
    mfcsam_aunt.set("perfumes", 1);

    return mfcsam_aunt;
}

bool part1_compare(const Aunt & left, const Aunt & right) {
    // Loop through the properties of the other object
    for (const auto &[right_name, right_value_ptr]: right.properties) {
        auto left_itr = left.properties.find(right_name);

        // If the property exists in both objects
        if (left_itr != left.properties.end()) {
            int left_value = *(left_itr->second);
            int right_value = *(right_value_ptr);

            // Only compare if both values are set (not -1)
            if (left_value != -1 && right_value != -1) {
                if (left_value != right_value) {
                    return false;
                }
            }
        }
    }
    return true;
}

int part1(std::ifstream & data) {

    std::array<Aunt, 501> aunts = createAunts(data);

    Aunt mfcsam_aunt = MFCSAM();

    // Find the matching Aunt
    for (size_t i = 1; i <= 500; ++i) {
        if (part1_compare(aunts[i], mfcsam_aunt)) {
            return i;
        }
    }

    return -1;
}

bool part2_compare(const Aunt & self) {

    Aunt mfcsam_aunt = MFCSAM();

    // iterate over the right side object
    for (const auto &[mfcsam_name, mfcsam_value_ptr]: mfcsam_aunt.properties) {

        // check if the right side key exists in the self
        auto self_itr = self.properties.find(mfcsam_name);
        if (self_itr != self.properties.end()) {

            // dereference the pointers to the values
            int self_value = *(self_itr->second);
            int mfcsam_value = *(mfcsam_value_ptr);

            // check that the values have been set and compare
            if (self_value != -1 && mfcsam_value != -1) {

                if (mfcsam_name == "trees" || mfcsam_name == "cats") {
                    if (self_value <= mfcsam_value) { return false; }
                } else if (mfcsam_name == "pomeranians" || mfcsam_name == "goldfish") {
                    if (self_value >= mfcsam_value) { return false; }
                } else {
                    if (self_value != mfcsam_value) { return false; }
                }

                // if (self_value != mfcsam_value) { return false; }

            }

        }
    }
    return true;
}

int part2(std::ifstream & data) {

    std::array<Aunt, 501> aunts = createAunts(data);

    // Find the matching Aunt
    for (size_t i = 1; i <= 500; ++i) {
        if (part2_compare(aunts[i])) {
            return i;
        }
    }

    return -1;
}

int main() {
    std::ifstream data("day16.txt");

    if (data.is_open()) {
        int aunt_id1 = part1(data);
        if (aunt_id1 == -1) {
            std::cout << "No matching Aunt found." << std::endl;
        } else {
            std::cout << std::format("Part 1: Aunt {} got the gift.", std::to_string(aunt_id1)) << std::endl;
        }

        // reset file to beginning by clearing out eof and fail flags, then seeking to the beginning of the file
        data.clear(); data.seekg(0);

        int aunt_id2 = part2(data);
        if (aunt_id2 == -1) {
            std::cout << "No matching Aunt found." << std::endl;
        } else {
            std::cout << std::format("Part 2: Aunt {} actually got the gift.", std::to_string(aunt_id2)) << std::endl;
        }
    }


    return 0;
}
