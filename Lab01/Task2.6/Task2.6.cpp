#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cmath>

using namespace std;

const double ENGLISH_FREQ[26] = { 0.08167, 0.01492, 0.02782, 0.04253, 0.12702,
                                 0.02228, 0.02015, 0.06094, 0.06966, 0.00015,
                                 0.00772, 0.04025, 0.02406, 0.06749, 0.07507,
                                 0.01929, 0.00095, 0.05987, 0.06327, 0.09056,
                                 0.02758, 0.00978, 0.02360, 0.00150, 0.01974,
                                 0.00074 };

string getLettersOnly(const string& text) {
    string res = "";
    for (char c : text) {
        if (isalpha(c)) res += tolower(c);
    }
    return res;
}

double calculateIC(const string& text) {
    int counts[26] = { 0 };
    int n = text.length();
    if (n <= 1) return 0.0;

    for (char c : text) counts[c - 'a']++;

    double ic = 0.0;
    for (int i = 0; i < 26; i++) {
        ic += counts[i] * (counts[i] - 1);
    }
    return ic / (n * (n - 1));
}

int findKeyLength(const string& text) {
    int bestLen = 1;
    double bestDiff = 1.0;

    for (int len = 1; len <= 20; ++len) {
        double avgIC = 0.0;
        for (int i = 0; i < len; ++i) {
            string col = "";
            for (size_t j = i; j < text.length(); j += len) {
                col += text[j];
            }
            avgIC += calculateIC(col);
        }
        avgIC /= len;

        double diff = abs(avgIC - 0.068);
        if (diff < bestDiff) {
            bestDiff = diff;
            bestLen = len;
        }
    }
    return bestLen;
}

string findKey(const string& text, int keyLen) {
    string key = "";

    for (int i = 0; i < keyLen; ++i) {
        string col = "";
        for (size_t j = i; j < text.length(); j += keyLen) {
            col += text[j];
        }

        int colLen = col.length();
        double minChiSq = 1e9;
        int bestShift = 0;

        for (int shift = 0; shift < 26; ++shift) {
            int counts[26] = { 0 };
            for (char c : col) {
                counts[(c - 'a' - shift + 26) % 26]++;
            }

            double chiSq = 0.0;
            for (int k = 0; k < 26; ++k) {
                double expected = colLen * ENGLISH_FREQ[k];
                double diff = counts[k] - expected;
                chiSq += (diff * diff) / expected;
            }

            if (chiSq < minChiSq) {
                minChiSq = chiSq;
                bestShift = shift;
            }
        }
        key += (char)(bestShift + 'a');
    }
    return key;
}

string decryptVigenere(const string& text, const string& key) {
    string result = "";
    int keyIndex = 0;
    int keyLength = key.length();

    for (char c : text) {
        if (isalpha(c)) {
            bool isUpper = isupper(c);
            char base = isUpper ? 'A' : 'a';
            char keyChar = tolower(key[keyIndex % keyLength]) - 'a';
            result += (char)((c - base - keyChar + 26) % 26 + base);
            keyIndex++;
        }
        else {
            result += c;
        }
    }
    return result;
}

int main() {
    string ciphertext;

    cout << "--- CHUONG TRINH PHA MA VIGENERE ---\n";
    cout << "Nhap hoac dan Ciphertext vao day: \n";
    getline(cin, ciphertext);

    string cleanText = getLettersOnly(ciphertext);
    if (cleanText.empty()) {
        cout << "Khong tim thay ky tu hop le de phan tich.\n";
        return 0;
    }

    int keyLen = findKeyLength(cleanText);
    string key = findKey(cleanText, keyLen);
    string plaintext = decryptVigenere(ciphertext, key);

    cout << "\n--- KET QUA PHAN TICH ---\n";
    cout << "[+] Chieu dai khoa tim duoc: " << keyLen << "\n";
    cout << "[+] Khoa (Key) du doan: " << key << "\n";
    cout << "[+] Ban ro (Plaintext) khoi phuc:\n" << plaintext << "\n";

    return 0;
}