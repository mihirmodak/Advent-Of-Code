#include <iostream>
#include <string>

using namespace std;

bool isValidPassword(const string& password) {
    // Check for increasing straight of at least three letters
    bool triplet_found = false;
    for (size_t i = 0; i < password.length() - 2; ++i) {
        if (password[i] + 1 == password[i + 1] && password[i] + 2 == password[i + 2]) {
            triplet_found = true;
            break; // Found a valid increasing straight
        }
    }
    if (!triplet_found) {
        return false;
    }

    // Check for forbidden letters 'i', 'o', and 'l'
    if (password.find_first_of("iol") != string::npos) {
        return false;
    }

    // Check for at least two different, non-overlapping pairs of letters
    char firstPair = '\0';
    bool foundPair = false;
    for (size_t i = 0; i < password.length() - 1; ++i) {
        if (password[i] == password[i + 1]) {
            if (foundPair && password[i] != firstPair) {
                return true; // Valid password
            }
            if (!foundPair) {
                foundPair = true;
                firstPair = password[i];
            }
            ++i; // Skip the overlapping pair
        }
    }

    return false;
}

string getNextPassword(const string& currentPassword) {
    string nextPassword = currentPassword;

    while (true) {
        // Increment the password string
        for (int i = nextPassword.length() - 1; i >= 0; --i) {
            if (nextPassword[i] == 'z') {
                nextPassword[i] = 'a';
            } else {
                ++nextPassword[i];
                break;
            }
        }

        if (isValidPassword(nextPassword)) {
            return nextPassword;
        }
    }
}

int main() {
    string currentPassword;
    cout << "Enter Santa's current password: ";
    cin >> currentPassword;

    string newPassword = getNextPassword(currentPassword);
    cout << "Santa's new password should be: " << newPassword << endl;

    return 0;
}
