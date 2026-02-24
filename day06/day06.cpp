#include <fstream>
#include <numeric>
#include <stdexcept>
#include <string>
#include <tuple>
#include <regex>
#include <array>
#include <iostream>

/**
 *                       _     _ 
 *      _ __   __ _ _ __| |_  / |
 *     | '_ \ / _` | '__| __| | |
 *     | |_) | (_| | |  | |_  | |
 *     | .__/ \__,_|_|   \__| |_|
 *     |_|                       
 */

using FunctionPtr1 = void (*)(bool &);

void _turnOn1(bool & light) {
    light = true;
}

void _turnOff1(bool & light) {
    light = false;
}

void _toggle1(bool & light) {
    light = !light;
}

// tuple( instruction_function, origin_coordinates, destination_coordinates )
using InstructionSet1 = std::tuple<FunctionPtr1, int, int, int, int>;
InstructionSet1 get_next_instruction1(std::ifstream & file) {
    std::string line;
    std::getline(file, line);

    std::regex pattern (R"(([\w\s]+) (\d{1,3}),(\d{1,3}) through (\d{1,3}),(\d{1,3}))");
    std::smatch matches;

    FunctionPtr1 instruction;
    int x1, y1, x2, y2;

    if (std::regex_match(line, matches, pattern)) {

        if (matches[1] == "turn on") {
            instruction = &_turnOn1;
        } else if (matches[1] == "turn off") {
            instruction = &_turnOff1;
        } else if (matches[1] == "toggle") {
            instruction = &_toggle1;
        } else {
            throw std::runtime_error("Unexpected instruction " + matches[1].str() + " in line `" + line + "`");
        }

        x1 = std::stoi(matches[2]);
        y1 = std::stoi(matches[3]);
        x2 = std::stoi(matches[4]);
        y2 = std::stoi(matches[5]);
    }

    std::pair<int, int> origin = std::make_pair(x1, y1);
    std::pair<int, int> destination = std::make_pair(x2, y2);

    return std::make_tuple(instruction, x1, y1, x2, y2);
}

template<typename T>
using Grid = std::array< std::array<T, 1000>, 1000 >;
void part1() {
    std::ifstream file ("day06.txt");

    Grid<bool> grid {};

    while (file && !file.eof()) {
        auto [operation, x1, y1, x2, y2] = get_next_instruction1(file);
        for (int row = x1; row <= x2; row++) {
            for (int col = y1; col <= y2; col++) {
                operation(grid[row][col]);
            }
        }
    }

    int total_lights_on = 0;
    for (std::array<bool, 1000> row: grid) {
        total_lights_on += std::accumulate(row.begin(), row.end(), 0);
    }

    file.close();

    std::cout << "Part 1: Total lights on = " << total_lights_on << std::endl;
}

/**
 *                       _     ____  
 *      _ __   __ _ _ __| |_  |___ \ 
 *     | '_ \ / _` | '__| __|   __) |
 *     | |_) | (_| | |  | |_   / __/ 
 *     | .__/ \__,_|_|   \__| |_____|
 *     |_|                           
 */

using FunctionPtr2 = void (*)(int &);

void _turnOn2(int & light) {
    light++;
}

void _turnOff2(int & light) {
    light = std::max({0, light-1});
}

void _toggle2(int & light) {
    light += 2;
}

using InstructionSet2 = std::tuple<FunctionPtr2, int, int, int, int>;
InstructionSet2 get_next_instruction2(std::ifstream & file) {
    std::string line;
    std::getline(file, line);

    std::regex pattern (R"(([\w\s]+) (\d{1,3}),(\d{1,3}) through (\d{1,3}),(\d{1,3}))");
    std::smatch matches;

    FunctionPtr2 instruction;
    int x1, y1, x2, y2;

    if (std::regex_match(line, matches, pattern)) {

        if (matches[1] == "turn on") {
            instruction = &_turnOn2;
        } else if (matches[1] == "turn off") {
            instruction = &_turnOff2;
        } else if (matches[1] == "toggle") {
            instruction = &_toggle2;
        } else {
            throw std::runtime_error("Unexpected instruction " + matches[1].str() + " in line `" + line + "`");
        }

        x1 = std::stoi(matches[2]);
        y1 = std::stoi(matches[3]);
        x2 = std::stoi(matches[4]);
        y2 = std::stoi(matches[5]);
    }

    std::pair<int, int> origin = std::make_pair(x1, y1);
    std::pair<int, int> destination = std::make_pair(x2, y2);

    return std::make_tuple(instruction, x1, y1, x2, y2);
}

void part2() {
    std::ifstream file("day06.txt");

    Grid<int> grid {};

    while (file && !file.eof()) {
        auto [operation, x1, y1, x2, y2] = get_next_instruction2(file);
        for (int row = x1; row <= x2; row++) {
            for (int col = y1; col <= y2; col++) {
                operation(grid[row][col]);
            }
        }
    }

    int total_brightess = 0;
    for (std::array<int, 1000> row: grid) {
        total_brightess += std::accumulate(row.begin(), row.end(), 0);
    }

    file.close();

    std::cout << "Part 2: Total brightness = " << total_brightess << std::endl;
}

int main() {
    part1();
    part2();
    return 0;
}