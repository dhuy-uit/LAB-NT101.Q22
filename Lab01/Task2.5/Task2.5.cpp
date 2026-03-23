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

    cout << "--- CHUONG TRINH MA HOA / GIAI MA VIGENERE ---\n";
    cout << "Chon thao tac (1 - Ma hoa | 2 - Giai ma): ";
    cin >> choice;
    cin.ignore();

    cout << "Nhap khoa (Key): ";
    getline(cin, key);

    cout << "Nhap van ban (Text): ";
    getline(cin, text);

    cout << "\n--- KET QUA ---\n";
    if (choice == 1) {
        cout << "Ciphertext: " << processVigenere(text, key, true) << "\n";
    }
    else if (choice == 2) {
        cout << "Plaintext: " << processVigenere(text, key, false) << "\n";
    }

    return 0;
}