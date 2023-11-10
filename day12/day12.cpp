#include <iostream>
#include <fstream>
#include "json.hpp"

int recursiveSum(const nlohmann::json& data) {
        int sum = 0;

        for (const auto& element : data) {

            if (element.is_number()) {
                sum += element.get<int>();
            } else if (element.is_object() || element.is_array()) {
                sum += recursiveSum(element);
            }

        }

        return sum;
    };


// Function to recursively sum all numbers while ignoring objects with "red" properties
int sumNumbersWithoutRed(const nlohmann::json& j) {
    int sum = 0;

    if (j.is_number()) {
        sum += j.get<int>();
    } else if (j.is_object()) { // we need to check for the property being "red" here
        bool hasRedProperty = false;
        for (auto it = j.begin(); it != j.end(); ++it) { // go through every element and check if it has value "red"
            if (it.value() == "red") {
                hasRedProperty = true;
                break;
            }
        }

        if (!hasRedProperty) {
            for (auto it = j.begin(); it != j.end(); ++it) {
                sum += sumNumbersWithoutRed(it.value());
            }
        }
    } else if (j.is_array()) { // go through all the elements of an array, the "red" property does not apply to arrays
        for (const auto& element : j) {
            sum += sumNumbersWithoutRed(element);
        }
    }

    return sum;
}



int main() {

    std::ifstream json_file ("../data.json");

    if (!json_file.is_open()) {
        std::cerr << "Error opening JSON file." << std::endl;
        return 1;
    }

    // Use nlohmann::json to parse out the JSON file
    nlohmann::json json_data;
    json_file >> json_data;

    // close the file because good habits :)
    json_file.close(); 


    // Part 1
    int total = recursiveSum(json_data);
    std::cout << "The sum of all the numbers in the JSON file is " << total << "." << std::endl;


    // Part 2
    int total_without_red = sumNumbersWithoutRed(json_data);
    std::cout << "The sum of all the numbers in the JSON file without objects containing 'red' is " << total_without_red << "." << std::endl;


    system("read -p \"Press enter to continue . . . \"");
    return 0;

}


/* 

    while( getline(data, line) ) {

        numbers.clear();

        // Find all the matches of the regular expression in the string.
        sregex_iterator iter(line.begin(), line.end(), pattern);
        sregex_iterator end;

        while (iter != end) {
            numbers.push_back(iter->str());
            ++iter;
        }

    }

    // Print the matched numbers.
    cout << "Here are all the numbers:" << '\n';
    for (string number : numbers) {
        cout << number << endl;
    }

 */