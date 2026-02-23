#include <fstream>
#include <unordered_set>
#include <iostream>

char get_next_char(std::ifstream &file) {
    if (!file.is_open()) {
        throw std::runtime_error("File not open");
    }
    char ch;
    if (!file.get(ch)) {
        return '\0'; // Return null character to indicate end of file
    }
    return ch;
}

struct PairHash {
    size_t operator()(const std::pair<int, int>& p) const {
        return std::hash<int64_t>()((int64_t)p.first << 32 | (uint32_t)p.second);
    }
};

struct VisitedCoordinates {
    std::unordered_set<std::pair<int, int>, PairHash> coordinates;

    bool contains(int x, int y) {
        return coordinates.count(std::make_pair(x, y)) > 0;
    }

    bool contains(const std::pair<int, int> & coords) {
        return coordinates.count(coords) > 0;
    }

    void insert(const int x, const int y) {
        coordinates.insert(std::make_pair(x, y));
    }

    void insert(const std::pair<int, int> & coords) {
        coordinates.insert(coords);
    }

    VisitedCoordinates operator+(const VisitedCoordinates & other) {
        VisitedCoordinates result;
        result.coordinates.reserve(this->coordinates.size() + other.coordinates.size());
        result.coordinates.insert(this->coordinates.begin(), this->coordinates.end());
        result.coordinates.insert(other.coordinates.begin(), other.coordinates.end());
        return result;
    }
};

void part1() {
    std::ifstream file("day03.txt");

    char ch;
    VisitedCoordinates visited;
    int x = 0, y = 0;
    visited.insert(x, y); // Start position

    while (file) {

        ch = get_next_char(file);
        if (ch == '\0') {
            break; // End of file reached
        }

        switch (ch) {
            case '^':
                y++;
                break;
            case 'v':
                y--;
                break;
            case '<':
                x--;
                break;
            case '>':
                x++;
                break;
        }
        visited.insert(x, y);
    }

    file.close();

    size_t unique_positions = visited.coordinates.size();
    std::cout << "Unique positions visited: " << unique_positions << std::endl;
}

std::pair<int, int> move(const char ch, int x, int y) {
    switch (ch) {
        case '^':
            return {x, y + 1};
        case 'v':
            return {x, y - 1};
        case '<':
            return {x - 1, y};
        case '>':
            return {x + 1, y};
        default:
            return {x, y}; // No movement for unrecognized characters
    }
}

void part2() {
    std::ifstream file("day03.txt");

    char ch;
    VisitedCoordinates santa_visited;
    VisitedCoordinates robo_visited;
    int santa_x = 0, santa_y = 0;
    int robo_x = 0, robo_y = 0;

    bool is_santa_turn = true;

    while (file) {
        ch = get_next_char(file);
        if (ch == '\0') {
            break; // End of file reached
        }

        if (is_santa_turn) {
            std::pair<int, int> new_coords = move(ch, santa_x, santa_y);
            santa_visited.insert(new_coords);
            
            // unpack to update values in loop
            santa_x = new_coords.first;
            santa_y = new_coords.second;
        } else {
            std::pair<int, int> new_coords = move(ch, robo_x, robo_y);
            robo_visited.insert(new_coords);

            // unpack to update values in loop
            robo_x = new_coords.first;
            robo_y = new_coords.second;
        }

        is_santa_turn = !is_santa_turn; // Alternate turns
    
    }

    file.close();

    VisitedCoordinates all_visited = santa_visited + robo_visited;
    size_t unique_positions = all_visited.coordinates.size();
    std::cout << "Unique positions visited by Santa and Robo-Santa: " << unique_positions << std::endl;

}

int main() {
    part1();
    part2();
    return 0;
}