#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string processVigenere(const string& text, const string& key, bool encrypt) {
    string result = "";
    int keyIndex = 0;
    int keyLength = key.length();

    for (char c : text) {
        if (isalpha(c)) {
            bool isUpper = isupper(c);
            char base = isUpper ? 'A' : 'a';
            char keyChar = tolower(key[keyIndex % keyLength]) - 'a';

            if (encrypt) {
                result += (char)((c - base + keyChar) % 26 + base);
            }
            else {
                result += (char)((c - base - keyChar + 26) % 26 + base);
            }
            keyIndex++;
        }
        else {
            result += c;
        }
    }
    return result;
}

int main() {
    int choice;
    string text, key;

    cin >> choice;
    cin.ignore();
    getline(cin, key);
    getline(cin, text);

    if (choice == 1) {
        cout << processVigenere(text, key, true) << "\n";
    }
    else if (choice == 2) {
        cout << processVigenere(text, key, false) << "\n";
    }

    return 0;
}