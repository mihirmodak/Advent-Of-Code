//
// Created by Mihir Modak on 11/27/24.
//
#include <fstream>
#include <iostream>
#include <format>
#include <vector>
#include <tuple>
#include <string>

int find_combinations_recursive(std::vector<int> capacities, int running_sum, int target,
                                std::vector<int> current_combination, int current_index) {
    if (running_sum == target) {
        return 1;
    }

    if (running_sum > target || current_index >= capacities.size()) {
        return 0;
    }

    int combinations = 0;

    // check if not including the current container works
    combinations += find_combinations_recursive(
        capacities,
        running_sum,
        target,
        current_combination,
        current_index + 1
    );


    // test if including the container at current_index is equal to the target
    current_combination.push_back(capacities[current_index]);
    combinations += find_combinations_recursive(
        capacities,
        running_sum + capacities[current_index],
        target,
        current_combination,
        current_index + 1
    );

    return combinations;
}

int part1(std::ifstream &data) {
    std::string line;
    std::vector<int> capacities;
    while (std::getline(data, line)) {
        capacities.push_back(std::stoi(line));
    }

    std::vector<int> current_combination;
    return find_combinations_recursive(capacities, 0, 150, current_combination, 0);
}

std::string to_string(std::vector<int> v) {
    std::string repr = "[" + std::to_string(v[0]);
    std::vector<int> remaining(v.begin() + 1, v.end());
    for (int elem: remaining) {
        repr += ", " + std::to_string(elem);
    }
    repr += "]";

    return repr;
}

std::tuple<int, int, std::vector<std::string> > find_smallest_combinations_recursive(
    std::vector<int> capacities,
    int running_sum,
    std::vector<int> current_combination,
    int current_index,
    int smallest_combination_length,
    int smallest_combination_count,
    std::vector<std::string> smallest_combinations
) {
    if (running_sum == 150) { // if we found a combination that totals 150 liters

        // check that the combination has not already been accounted for
        std::string current_combination_string = to_string(current_combination);
        if (std::count(smallest_combinations.begin(), smallest_combinations.end(), current_combination_string) == 0) {

            // if we already have this combination length as the smallest
            if (current_combination.size() == smallest_combination_length) {
                smallest_combination_count++;
                smallest_combinations.push_back(current_combination_string);
            }

            // if the combination is shorter (fewer containers) than the current shortest
            else if (current_combination.size() < smallest_combination_length) {
                smallest_combination_length = current_combination.size();
                smallest_combination_count = 1;
                smallest_combinations.push_back(current_combination_string);
            }

            // the combination is longer than the current shortest, so we ignore it
            else {
                return {smallest_combination_length, smallest_combination_count, smallest_combinations};
            }
        }
    }

    // we went too far (past 150 liters) so we return
    if (running_sum > 150 || current_index >= capacities.size()) {
        return {smallest_combination_length, smallest_combination_count, smallest_combinations};
    }

    // check if not including the current container works
    std::tuple<int, int, std::vector<std::string> > new_combinations = find_smallest_combinations_recursive(
        capacities,
        running_sum,
        current_combination,
        current_index + 1,
        smallest_combination_length,
        smallest_combination_count,
        smallest_combinations
    );
    smallest_combination_length = std::get<0>(new_combinations);
    smallest_combination_count = std::get<1>(new_combinations);


    // test if including the container at current_index is equal to the target
    current_combination.push_back(capacities[current_index]);
    new_combinations = find_smallest_combinations_recursive(
        capacities,
        running_sum + capacities[current_index],
        current_combination,
        current_index + 1,
        smallest_combination_length,
        smallest_combination_count,
        smallest_combinations
    );
    smallest_combination_length = std::get<0>(new_combinations);
    smallest_combination_count = std::get<1>(new_combinations);

    return {smallest_combination_length, smallest_combination_count, smallest_combinations};
}

std::pair<int, int> part2(std::ifstream &data) {
    std::string line;
    std::vector<int> capacities;
    while (std::getline(data, line)) {
        capacities.push_back(std::stoi(line));
    }

    std::vector<int> current_combination;
    std::vector<std::string> smallest_combinations;
    std::tuple<int, int, std::vector<std::string> > smallest_combination_tuple = find_smallest_combinations_recursive(
        capacities,
        0,
        current_combination,
        0,
        999999,
        0,
        smallest_combinations
    );

    return {
        std::get<0>(smallest_combination_tuple),
        std::get<1>(smallest_combination_tuple)
    };
}

int main() {
    std::ifstream data("day17.txt");

    if (data.is_open()) {
        int combinations = part1(data);
        std::cout << std::format("Part 1: There are {} combinations.", combinations) << std::endl;

        // reset file to beginning by clearing out eof and fail flags, then seeking to the beginning of the file
        data.clear();
        data.seekg(0);

        std::pair<int, int> new_combinations = part2(data);
        std::cout << std::format(
            "Part 2: The smallest combination has {} containers. There are {} such combinations.",
            new_combinations.first,
            new_combinations.second
        ) << std::endl;
    }
}
