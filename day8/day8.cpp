#include <iostream>
#include <fstream>
#include <regex>
#include <cstring>

using namespace std;

int part1(ifstream& data) {

    string line;
    int code_chars = 0;
    int memory_chars = 0;

    while(getline(data, line)) {
        code_chars += line.length();

        string memory_line;
        if (line.length() > 0) {
            memory_line = line.substr(1, line.length()-2);
        } else {
            memory_line = line;
        }

        // cout << line << "\t";

        // Replace \\ with "\"
        std::string pattern1 = R"(\\\\)";
        std::string replacement1 = R"(\)";
        memory_line = regex_replace(memory_line, std::regex(pattern1), replacement1);
        
        // Replace \" with "
        std::string pattern2 = R"(\\")";
        std::string replacement2 = R"(")";
        memory_line = regex_replace(memory_line, std::regex(pattern2), replacement2);
        
        // Replace \x\d\d with ~
        std::string pattern3 = R"(\\x[0-9A-Fa-f]{2})";
        std::string replacement3 = R"(~)";
        memory_line = regex_replace(memory_line, std::regex(pattern3), replacement3);

        // cout << memory_line << endl;

        // cout << line.length() << "\t" << memory_line.length() << endl;

        memory_chars += memory_line.length();

    }

    // cout << "Code: " << code_chars << ", Memory: " << memory_chars << endl; 
    return code_chars - memory_chars;

}

int part2(ifstream& data) {

    string line, encoded_line;;
    int code_chars = 0;
    int encoded_chars = 0;

    while(getline(data, line)) {
        code_chars += line.length();
        encoded_line = line;

        // Replace \\ with "\"
        std::string pattern1 = R"(\\)";
        std::string replacement1 = R"(\\)";
        encoded_line = regex_replace(encoded_line, std::regex(pattern1), replacement1);
        
        // Replace \" with "
        std::string pattern2 = R"(")";
        std::string replacement2 = R"(\")";
        encoded_line = regex_replace(encoded_line, std::regex(pattern2), replacement2);
        
        encoded_chars += encoded_line.length() + 2;

    }

    // cout << "Code: " << code_chars << ", Encoded: " << encoded_chars << endl; 
    return encoded_chars - code_chars;

}


int main() {
    ifstream data ("day8.txt");

    if (data.is_open()) {
        
        // Part 1
        int char_diff1 = part1(data);
        cout << "Part 1 -> The difference between code characters and memory characters is " << char_diff1 << endl;

        // reset file to beginning by clearing out eof and fail flags, then seeking to the beginning of the file
        data.clear(); data.seekg(0);

        // Part 2
        int char_diff2 = part2(data);
        cout << "Part 2 -> The difference between re-encoded characters and code characters is " << char_diff2 << endl;

    }

    data.close();

    system("pause");
    return 0;
}
