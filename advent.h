#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

vector<string> split(string str, char delim) {
    stringstream ss (str);
    string part;
    vector<string> result;

    while (getline(ss, part, delim)) {
        result.push_back(part);
    }

    return result;
}

vector<string> slice(vector<string> arr, int X, int Y) {

    // Starting and Ending iterators
    auto start = arr.begin() + X;
    auto end = arr.begin() + Y + 1;

    // To store the sliced vector
    vector<string> result(Y - X + 1);

    // Copy vector using copy function()
    copy(start, end, result.begin());

    // Return the final sliced vector
    return result;
}