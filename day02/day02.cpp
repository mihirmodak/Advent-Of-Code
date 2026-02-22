#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

/**
 *      _          _
 *     | |__   ___| |_ __   ___ _ __ ___
 *     | '_ \ / _ \ | '_ \ / _ \ '__/ __|
 *     | | | |  __/ | |_) |  __/ |  \__ \
 *     |_| |_|\___|_| .__/ \___|_|  |___/
 *                  |_|
 */

std::vector<std::string> split_string(const std::string &str, std::string delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    size_t position = 0;
    std::string str_copy = str; // essentially a copy constructor using the reference to the original string

    while ((position = str_copy.find(delimiter)) != std::string::npos) {
        token = str_copy.substr(0, position);
        tokens.push_back(token);
        str_copy.erase(0, position + delimiter.length());
    }
    tokens.push_back(str_copy);
    return tokens;
}

std::tuple<int, int, int> get_next_dimensions(std::ifstream &file) {
    int l, w, h;
    std::string line;

    if (!file.is_open()) {
        throw std::runtime_error("File not open");
    }

    // keep trying to get the next non-empty line until we find one or reach the end of the file
    while (line.empty()) {
        if (!std::getline(file, line)) {
            return std::make_tuple(-1, -1, -1); // sentinel value to indicate end of file
        }
    }

    std::vector<std::string> dimensions = split_string(line, "x");
    if (dimensions.size() != 3) {
        throw std::runtime_error("Invalid line format: " + line);
    }

    try {
        l = std::stoi(dimensions[0]);
        w = std::stoi(dimensions[1]);
        h = std::stoi(dimensions[2]);
        return std::make_tuple(l, w, h);
    } catch (const std::invalid_argument &e) {
        throw std::runtime_error("Invalid number format in line: " + line);
    }
}

/**
 *                       _     _
 *      _ __   __ _ _ __| |_  / |
 *     | '_ \ / _` | '__| __| | |
 *     | |_) | (_| | |  | |_  | |
 *     | .__/ \__,_|_|   \__| |_|
 *     |_|
 */

int surface_area(int l, int w, int h) {
    return 2 * l * w + 2 * w * h + 2 * l * h;
}

int smallest_side_area(int l, int w, int h) {
    int lw = l * w;
    int lh = l * h;
    int wh = w * h;

    return std::min(lw, std::min(lh, wh));
}

int wrapping_paper_needed(int l, int w, int h) {
    return surface_area(l, w, h) + smallest_side_area(l, w, h);
}

void part1() {
    std::ifstream file("day02.txt");

    if (!file) {
        throw std::runtime_error("Could not open file");
    }

    std::tuple<int, int, int> dimensions;
    int l, w, h;
    int total_wrapping_paper_needed = 0;

    while (file) {
        dimensions = get_next_dimensions(file);

        // handle EOF sentinel value
        if (std::get<0>(dimensions) == -1) {
            break;
        }

        l = std::get<0>(dimensions);
        w = std::get<1>(dimensions);
        h = std::get<2>(dimensions);

        total_wrapping_paper_needed += wrapping_paper_needed(l, w, h);
    }

    file.close();

    std::string total_wrapping_paper_needed_str = std::to_string(total_wrapping_paper_needed);
    std::cout << "Part 1: Total wrapping paper needed: " << total_wrapping_paper_needed_str << std::endl;
    return;
}

/**
 *                       _     ____
 *      _ __   __ _ _ __| |_  |___ \
 *     | '_ \ / _` | '__| __|   __) |
 *     | |_) | (_| | |  | |_   / __/
 *     | .__/ \__,_|_|   \__| |_____|
 *     |_|
 */

int smallest_perimeter(int l, int w, int h) {
    int lw = 2 * (l + w);
    int lh = 2 * (l + h);
    int hw = 2 * (h + w);

    return std::min(lw, std::min(lh, hw));
}

int volume(int l, int w, int h) {
    return l * w * h;
}

int ribbon_needed(int l, int w, int h) {
    return smallest_perimeter(l, w, h) + volume(l, w, h);
}

void part2() {
    std::ifstream file("day02.txt");

    if (!file) {
        throw std::runtime_error("Could not open file");
    }

    std::tuple<int, int, int> dimensions;
    int l, w, h;
    int total_ribbon_needed = 0;

    while (file) {
        dimensions = get_next_dimensions(file);

        // handle EOF sentinel value
        if (std::get<0>(dimensions) == -1) {
            break;
        }

        l = std::get<0>(dimensions);
        w = std::get<1>(dimensions);
        h = std::get<2>(dimensions);

        total_ribbon_needed += ribbon_needed(l, w, h);
    }

    file.close();
    
    std::string total_ribbon_needed_str = std::to_string(total_ribbon_needed);
    std::cout << "Part 2: Total ribbon needed: " << total_ribbon_needed_str << std::endl;
    return;
}

int main() {
    part1();
    part2();
    return 0;
}