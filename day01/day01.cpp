#include <fstream>
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

int part1() {
    std::ifstream file("day01.txt");
    int floor = 0;
    int char_count = 0;
    char ch;

    while (file.is_open() && !file.eof()) {

        ch = get_next_char(file);

        if (ch == '\0') {
            break; // End of file reached
        }

        char_count++;
        if (ch == '(') {
            floor++;
        } else if (ch == ')') {
            floor--;
        } else {
            throw std::runtime_error("Invalid character in input: " + std::string(1, ch) + " at character position " + std::to_string(char_count));
        }
    }

    file.close();

    return floor;
}

int part2() {
    std::ifstream file("day01.txt");
    char ch;
    int floor = 0;
    int char_count = 0;

    while (file.is_open() && !file.eof()) {

        ch = get_next_char(file);

        if (ch == '\0') {
            break; // End of file reached
        }

        char_count++;
        if (ch == '(') {
            floor++;
        } else if (ch == ')') {
            floor--;
        } else {
            throw std::runtime_error("Invalid character in input: " + std::string(1, ch) + " at character position " + std::to_string(char_count));
        }

        if (floor < 0) {
            break; // Santa has entered the basement
        }
    }

    file.close();

    return char_count;
}

int main() {
    int part1_result = part1();
    std::cout << "Part 1: Final floor is " << part1_result << std::endl;

    int part2_result = part2();
    std::cout << "Part 2: Position of first character that causes Santa to enter the basement is " << part2_result << std::endl;

    return 0;
}