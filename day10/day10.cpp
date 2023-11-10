#include <iostream>

using namespace std;

string LookAndSay(string input_string) {
    int current_number_count = 0;
    int previous_number = input_string[0] - '0';
    string translated_sequence = "";

    for (char current_number : input_string) {
        current_number = current_number - '0';// normalize the current number from a char to an int by subtracting the ascii code of the char 0
        if (current_number == previous_number) {
            current_number_count++;
        } else {
            translated_sequence += to_string(current_number_count);
            translated_sequence += to_string( previous_number == -1 ? current_number : previous_number );
            current_number_count = 1;
        }

        previous_number = current_number; 
    }
    translated_sequence += to_string(current_number_count);
    translated_sequence += to_string( previous_number == -1 ? input_string[input_string.length()-1] : previous_number );

    return translated_sequence;
}

int part1() {
    string sequence;
    cout << "Enter the look-and-say string:" << endl;
    getline(cin, sequence);

    for (int iteration_counter = 0; iteration_counter < 40; iteration_counter++) {
        sequence = LookAndSay(sequence);
    }

    return sequence.length();
}

int part2() {
    string sequence;
    cout << "Enter the look-and-say string:" << endl;
    getline(cin, sequence);

    for (int iteration_counter = 0; iteration_counter < 50; iteration_counter++) {
        sequence = LookAndSay(sequence);
    }

    return sequence.length();
}

int main() {

    cout << '\n';

    // Part 1
    int length1 = part1();
    cout << "Part 1 -> " << length1 << endl;

    // Part 2
    int length2 = part2();
    cout << "Part 2 -> " << length2 << endl;

    return 0;
}