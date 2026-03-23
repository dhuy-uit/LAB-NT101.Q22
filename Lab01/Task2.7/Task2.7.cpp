#include <iostream>
#include <string>
#include <vector>

using namespace std;

string encryptRailFence(string text, int key) {
    if (key <= 1) return text;
    vector<string> rail(key, "");
    int row = 0;
    bool down = false;

    for (char c : text) {
        rail[row] += c;
        if (row == 0 || row == key - 1) down = !down;
        row += down ? 1 : -1;
    }

    string result = "";
    for (string str : rail) result += str;
    return result;
}

string decryptRailFence(string cipher, int key) {
    if (key <= 1) return cipher;

    vector<vector<char>> railMatrix(key, vector<char>(cipher.length(), '\n'));

    bool down = false;
    int row = 0, col = 0;

    for (int i = 0; i < cipher.length(); i++) {
        if (row == 0) down = true;
        if (row == key - 1) down = false;

        railMatrix[row][col++] = '*';
        row += down ? 1 : -1;
    }

    int index = 0;
    for (int i = 0; i < key; i++) {
        for (int j = 0; j < cipher.length(); j++) {
            if (railMatrix[i][j] == '*' && index < cipher.length()) {
                railMatrix[i][j] = cipher[index++];
            }
        }
    }

    string result = "";
    row = 0; col = 0;
    for (int i = 0; i < cipher.length(); i++) {
        if (row == 0) down = true;
        if (row == key - 1) down = false;

        if (railMatrix[row][col] != '\n') {
            result += railMatrix[row][col++];
        }
        row += down ? 1 : -1;
    }

    return result;
}

int main() {
    cout << "========== TASK 2.7 (MO RONG): RAIL FENCE CIPHER ==========\n\n";

    // ---------------------------------------------------------
    // PHAN 1: NGUOI DUNG TU NHAP
    // ---------------------------------------------------------
    cout << "--- PHAN 1: MA HOA / GIAI MA TUY CHON ---\n";
    int choice;
    cout << "Chon thao tac (1 - Ma hoa | 2 - Giai ma): ";
    cin >> choice;
    cin.ignore();

    string text;
    int key;

    if (choice == 1) {
        cout << "Nhap ban ro (Plaintext): ";
        getline(cin, text);
        cout << "Nhap khoa (so hang/rails): ";
        cin >> key;
        cout << "[+] Ket qua MA HOA: " << encryptRailFence(text, key) << "\n\n";
    }
    else if (choice == 2) {
        cout << "Nhap ban ma (Ciphertext): ";
        getline(cin, text);
        cout << "Nhap khoa (so hang/rails): ";
        cin >> key;
        cout << "[+] Ket qua GIAI MA: " << decryptRailFence(text, key) << "\n\n";
    }
    else {
        cout << "[!] Lua chon khong hop le.\n\n";
    }

    // ---------------------------------------------------------
    // PHAN 2: TEST CASE MINH HOA (Theo yeu cau viet bao cao)
    // ---------------------------------------------------------
    cout << "--- PHAN 2: TEST CASE MINH HOA ---\n";
    string samplePlaintext = "DAI HOC CONG NGHE THONG TIN";
    int sampleKey = 3; 

    cout << "[+] Ban ro mau: " << samplePlaintext << "\n";
    cout << "[+] Khoa (So hang): " << sampleKey << "\n";

    string encrypted = encryptRailFence(samplePlaintext, sampleKey);
    cout << "[+] Ket qua Ma hoa: " << encrypted << "\n";

    string decrypted = decryptRailFence(encrypted, sampleKey);
    cout << "[+] Ket qua Giai ma lai: " << decrypted << "\n";

    return 0;
}