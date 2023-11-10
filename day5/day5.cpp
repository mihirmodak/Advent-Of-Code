#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

using namespace std;

int part1(ifstream & data) {
    string line;
    const string vowels = "aeiou";
    int nice_counter = 0;
    while (getline(data, line)) {

        bool repeated_chars = false;
        int vowel_count = 0;    // set up the vowel count for the final condition
                                // reset to 0 for every line

        // eliminate the strings that have these substrings in them
        // if the substrings do not exist, find() returns the value of string::npos
        // if all the find()s return no matches (i.e. string::npos), then the sum will be 5*string::npos
        if (line.find("ab") + line.find("cd") + line.find("pq") + line.find("xy") == 4*string::npos) {

            for (int i = 0; i < line.length()-1; i++) { // for each char in the string
                if (line[i] == line[i+1]) { // if there is a pair of identical consecutive characters
                    repeated_chars = true;
                    break;
                }

            }

            for (char c : line) {
                if (vowels.find(c) != string::npos) { // if find() does not return 'no match' i.e. if c is a vowel
                    vowel_count++;
                }
            }

            if ((repeated_chars) && (vowel_count >= 3)) {
                nice_counter++;
            }

        }
    }
    return nice_counter;
}

int part2(ifstream & data) {
    string line;
    int nice_counter = 0;

    while (getline(data, line)) {

        // condition 1
        bool repeated_pairs = false;
        for (int i=0; i<line.length()-1; i++) {
            string pair = string() + line[i] + line[i+1];
            if ( line.find(pair) != string::npos ) {
                if ( line.find(pair, line.find(pair)+2) != string::npos ) {
                    // cout << line << " -> " << pair << endl;
                    repeated_pairs = true;
                    break;
                }
            }
        }

        // condition 2
        bool aba_pattern = false;
        for (int i = 0; i < line.length(); i++) {
            // convert char c to a string
            char c = line[i];
            string letter (1,c);

            // build the regex pattern using the current char
            string pattern_string = letter + "[a-zA-Z]" + letter;
            regex pattern (pattern_string);

            // regex match
            smatch match;
            regex_search(line, match, pattern);

            // cout << line << ", " << letter << " -> " << match.length() << endl;

            if (match.length() > 0) {
                aba_pattern = true;
                break;
            }
        }

        // Decision time
        if (repeated_pairs && aba_pattern) {
            nice_counter++;
        }
    }

    return nice_counter;
}

int main() {
    ifstream data ("day5.txt");
    if (data.is_open()) {
        // Part 1
        int num_nice1 = part1(data);
        cout << "Part 1 -> There are " << num_nice1 << " nice words." << endl;

        // reset file to beginning by clearing out eof and fail flags, then seeking to the beginning of the file
        data.clear(); data.seekg(0);

        // Part 2
        int num_nice2 = part2(data);
        cout << "Part 2 -> There are " << num_nice2 << " nice words." << endl;
    }

    data.close();

    system("pause");
    return 0;
}