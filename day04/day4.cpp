#include <iostream>
#include <fstream>
#include <iomanip>
#include <openssl/md5.h>
#include <cmath>

using namespace std;

string hash_md5(const string & msg) {
    unsigned char hashed[MD5_DIGEST_LENGTH];
    MD5((const unsigned char*)msg.c_str(), msg.size(), hashed);

    string result;
    result.reserve(32);

    for (std::size_t i = 0; i != 16; ++i) {
    result += "0123456789abcdef"[hashed[i] / 16];
    result += "0123456789abcdef"[hashed[i] % 16];
    }

    return result;
}

int part1(ifstream & data){
    string line, hashed_val;
    int num = 0;
    getline(data, line);

    for (num; num < pow(10,6); num++) {
        hashed_val = hash_md5(line + to_string(num));
        if (hashed_val.substr(0,5) == "00000") {
            break;
        }
    }

    return num;
}

int part2(ifstream & data){
    string line, hashed_val;
    int num = 0;
    getline(data, line);

    for (num; num < pow(10,7); num++) {
        hashed_val = hash_md5(line + to_string(num));
        if (hashed_val.substr(0,6) == "000000") {
            break;
        }
    }

    return num;
}

int main() {
    ifstream data ("day4.txt");

    if (data.is_open()) {
        // Part 1
        int num1 = part1(data);
        cout << "Part 1 -> The smallest number that results in the hash starting with 5 zeroes is " << num1 << endl;

        // reset file to beginning by clearing out eof and fail flags, then seeking to the beginning of the file
        data.clear(); data.seekg(0);

        // Part 2
        int num2 = part2(data);
        cout << "Part 2 -> The smallest number that results in the hash starting with 6 zeroes is " << num2 << endl;
    }

    data.close();

    return 0;
}