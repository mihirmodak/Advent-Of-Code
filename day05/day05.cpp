#include <fstream>
#include <string>
#include <iostream>

/**
 *                       _     _ 
 *      _ __   __ _ _ __| |_  / |
 *     | '_ \ / _` | '__| __| | |
 *     | |_) | (_| | |  | |_  | |
 *     | .__/ \__,_|_|   \__| |_|
 *     |_|                       
 */

bool isNice1(const std::string & str) {

    // 1. contains at least 3 vowels (aeiou)
    int vowel_count = 0;
    for (char c: str) {
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            vowel_count++;
        }
    }
    if (vowel_count < 3) {
        return false;
    }

    // 2. contains at least one letter that appears twice in a row
    bool has_double_letter = false;
    for (size_t i = 0; i < str.size() - 1; i++) {
        if (str[i] == str[i+1]) {
            has_double_letter = true;
            break;
        }
    }
    if (!has_double_letter) {
        return false;
    }

    // 3. does not contain the strings "ab", "cd", "pq", or "xy"
    if (str.find("ab") != std::string::npos ||
        str.find("cd") != std::string::npos ||
        str.find("pq") != std::string::npos ||
        str.find("xy") != std::string::npos) {
        return false;
    }

    // Otherwise
    return true;
}

void part1() {
    std::ifstream file("day05.txt");

    if (!file) {
        throw std::runtime_error("Could not open file");
    }

    std::string line;
    int nice_count = 0;
    while(std::getline(file, line)) {
        if (isNice1(line)) {
            nice_count++;
        }
    }

    file.close();

    std::cout << "Part 1: There are " << nice_count << " nice strings." << std::endl;
}

/**
 *                       _     ____  
 *      _ __   __ _ _ __| |_  |___ \ 
 *     | '_ \ / _` | '__| __|   __) |
 *     | |_) | (_| | |  | |_   / __/ 
 *     | .__/ \__,_|_|   \__| |_____|
 *     |_|                           
 */                        

bool isNice2(const std::string & str) {

    // std::cout << str << std::endl;                                                           // DEBUGGING

    // 1. contains a pair of any two letters that appears at least twice in the string without overlapping
    bool has_pair_of_two_letters = false;
    for (size_t i = 0; i < str.size() - 1; i++) {
        std::string letter_pair = str.substr(i, 2);

        // if it finds a second instance of the letter pair, move to the next check
        size_t found_index = str.find(letter_pair, i+2);
        if (found_index != std::string::npos) {
            // std::cout << "~~" << str.substr(i, found_index+2-i) << "~~" << std::endl;        // DEBUGGING
            has_pair_of_two_letters = true;
            break;
        }
    }
    if (!has_pair_of_two_letters) {
        return false;
    }

    // 2. contains at least one letter which repeats with exactly one letter between them
    for (size_t i = 0; i < str.size() - 2; i++) {
        // std::cout << str[i] << str[i+1] << str[i+2];                                         // DEBUGGING
        if (str[i] == str[i+2]) {
            // std::cout << "<--" << std::endl;                                                 // DEBUGGING
            return true;
        } else {
            // std::cout << std::endl;                                                          // DEBUGGING
        }
    }


    // Otherwise
    // has_pair_of_two_letters is true --> 1. is satisfied
    // but did not satisfy condition 2
    return false;
}

void part2() {
    std::ifstream file("day05.txt");

    if (!file) {
        throw std::runtime_error("Could not open file");
    }

    std::string line;
    int nice_count = 0;
    while (std::getline(file, line)) {
        // std::cout << "\n" << std::endl;                                                      // DEBUGGING
        if (isNice2(line)) {
            nice_count++;
        }
    }

    file.close();

    std::cout << "Part 2: There are " << nice_count << " nice strings." << std::endl;
}

int main() {
    part1();
    part2();
    return 0;
}