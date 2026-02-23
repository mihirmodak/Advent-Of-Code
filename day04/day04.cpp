#include <fstream>
#include <iostream>
#include <string>
#include <openssl/evp.h>
#include <sstream>

std::string md5(const std::string & input) {
    unsigned char digest[EVP_MAX_MD_SIZE];
    size_t digest_len = 0;

    EVP_Q_digest(
        NULL,               // libctx: library context, or NULL for the default
        "MD5",                // name: name of the digest algorithm
        NULL,                // propq: algorithm properties
        input.c_str(),        // data: pointer to the data to be hashed
        input.size(),      // data_len: length of the data to be hashed
        digest,                 // digest: buffer to store the resulting digest
        &digest_len          // digest_lenpointer to the length of the resulting digest
    );

    // Convert the raw binary digest into a hex string.
    // Each byte is formatted as a 2-character zero-padded hex value (e.g., 0x0A -> "0a").
    std::ostringstream out;
    out << std::hex << std::setfill('0');
    for (size_t i = 0; i < digest_len; ++i)
        out << std::setw(2) << (int)digest[i]; // Cast to int so the stream formats it as a number
    return out.str();

}

int find_numeric_key(const std::string & letter_key, const int num_zeroes) {
    int numeric_key = 0;
    std::string zeroes(num_zeroes, '0');

    while (true) {
        std::string key = letter_key + std::to_string(numeric_key);
        std::string hash = md5(key);
        if (hash.substr(0, num_zeroes) == zeroes) {
            return numeric_key;
        }
        numeric_key++;
    }
}

void part1() {
    std::ifstream file("day04.txt");

    if (!file.good()) {
        throw std::runtime_error("Could not open file");
    }

    std::string letter_key;
    std::getline(file, letter_key);
    int numeric_key = find_numeric_key(letter_key, 5);
    
    std::cout << "Part 1: " << numeric_key << std::endl;
    file.close();
}

void part2() {
    std::ifstream file("day04.txt");

    if (!file.good()) {
        throw std::runtime_error("Could not open file");
    }

    std::string letter_key;
    std::getline(file, letter_key);

    int numeric_key = find_numeric_key(letter_key, 6);
    std::cout << "Part 2: " << numeric_key << std::endl;

    file.close();
}

int main() {
    part1();
    part2();
    return 0;
}