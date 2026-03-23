#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

class Playfair {
private:
    char mat[5][5];
    string key;

    void generateMatrix() {
        bool used[26] = { false };
        used['J' - 'A'] = true;

        string filteredKey = "";
        for (char c : key) {
            if (isalpha(c)) {
                c = toupper(c);
                if (c == 'J') c = 'I';
                if (!used[c - 'A']) {
                    filteredKey += c;
                    used[c - 'A'] = true;
                }
            }
        }

        // Dien cac chu cai con lai vao ma tran
        for (char c = 'A'; c <= 'Z'; ++c) {
            if (!used[c - 'A']) filteredKey += c;
        }

        int k = 0;
        cout << "\n--- Ma Tran Playfair 5x5 ---\n";
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                mat[i][j] = filteredKey[k++];
                cout << mat[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "----------------------------\n";
    }

    // Tim toa do cua ky tu trong ma tran
    void findPosition(char c, int& row, int& col) {
        if (c == 'J') c = 'I';
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (mat[i][j] == toupper(c)) {
                    row = i; col = j; return;
                }
            }
        }
    }

    // Chuan hoa ban ro truoc khi ma hoa (chi lay chu cai, in hoa, chen X)
    string formatPlaintext(string text) {
        string res = "";
        for (char c : text) {
            if (isalpha(c)) {
                res += toupper(c == 'j' || c == 'J' ? 'I' : c);
            }
        }
        string finalRes = "";
        for (size_t i = 0; i < res.length(); i++) {
            finalRes += res[i];
            // Neu 2 chu cai giong nhau cung 1 cap -> chen X vao giua
            if (i + 1 < res.length() && res[i] == res[i + 1] && finalRes.length() % 2 != 0) {
                finalRes += 'X';
            }
        }
        // Neu do dai le thi them X vao cuoi
        if (finalRes.length() % 2 != 0) finalRes += 'X';
        return finalRes;
    }

public:
    Playfair(string k) {
        key = k;
        generateMatrix();
    }

    // Thuc hien ma hoa
    string encrypt(string text) {
        text = formatPlaintext(text);
        string result = "";
        for (size_t i = 0; i < text.length(); i += 2) {
            int r1, c1, r2, c2;
            findPosition(text[i], r1, c1);
            findPosition(text[i + 1], r2, c2);

            if (r1 == r2) { // Cung hang -> Dich phai
                result += mat[r1][(c1 + 1) % 5];
                result += mat[r2][(c2 + 1) % 5];
            }
            else if (c1 == c2) { // Cung cot -> Dich xuong
                result += mat[(r1 + 1) % 5][c1];
                result += mat[(r2 + 1) % 5][c2];
            }
            else { // Khac hang khac cot -> Doi cot
                result += mat[r1][c2];
                result += mat[r2][c1];
            }
        }
        return result;
    }

    // Thuc hien giai ma
    string decrypt(string text) {
        // Chuan hoa ban ma (loai bo khoang trang)
        string cleanText = "";
        for (char c : text) if (isalpha(c)) cleanText += toupper(c);

        string result = "";
        for (size_t i = 0; i < cleanText.length(); i += 2) {
            int r1, c1, r2, c2;
            findPosition(cleanText[i], r1, c1);
            findPosition(cleanText[i + 1], r2, c2);

            if (r1 == r2) { // Cung hang -> Dich trai (+4 de chong so am)
                result += mat[r1][(c1 + 4) % 5];
                result += mat[r2][(c2 + 4) % 5];
            }
            else if (c1 == c2) { // Cung cot -> Dich len
                result += mat[(r1 + 4) % 5][c1];
                result += mat[(r2 + 4) % 5][c2];
            }
            else { // Khac hang khac cot -> Doi cot
                result += mat[r1][c2];
                result += mat[r2][c1];
            }
        }
        return result;
    }
};

int main() {
    cout << "========== TASK 2.4: PLAYFAIR CIPHER ==========\n\n";

    // ---------------------------------------------------------
    // PHAN 1: NGUOI DUNG TU NHAP
    // ---------------------------------------------------------
    cout << "--- PHAN 1: MA HOA / GIAI MA TUY CHON ---\n";
    string userKey;
    cout << "Nhap khoa (Key): ";
    getline(cin, userKey);

    Playfair userPf(userKey);

    int choice;
    cout << "Chon thao tac (1 - Ma hoa | 2 - Giai ma): ";
    cin >> choice;
    cin.ignore();

    string userText;
    if (choice == 1) {
        cout << "Nhap ban ro (Plaintext): ";
        getline(cin, userText);
        cout << "Ket qua MA HOA: " << userPf.encrypt(userText) << "\n\n";
    }
    else if (choice == 2) {
        cout << "Nhap ban ma (Ciphertext): ";
        getline(cin, userText);
        cout << "Ket qua GIAI MA: " << userPf.decrypt(userText) << "\n\n";
    }
    else {
        cout << "Lua chon khong hop le.\n\n";
    }

    // ---------------------------------------------------------
    // PHAN 2: TEST CASE CUA BAI LAB
    // ---------------------------------------------------------
    cout << "--- PHAN 2: GIAI MA DOAN TEXT CUA LAB ---\n";
    string labKey = "Harry Potter";
    cout << "Khoa su dung: " << labKey << "\n";
    Playfair labPf(labKey);

    string labCiphertext = "ARYWYPHCBVEBYGMPNCYGCNTDNCWTMGRMFTQPLEWTMLREFBEBQEBIYGBFLPHVOAEHKDHEUNGQFEROLEWTMLOPHEQGOSBEROQDWTLCMTHBWLNRKXRYLORYYPHCBVEBYRLGYDMKYGGWKLROANDBWGNERMNGYRLGHEWRTRLMBRHMUDGVODVTEGMCHLGWCMTFODNRRYCMZKODDUTDXGEOPOYRMFRMGUKXRYGHABROVTGQMCEHPRPEOTSEGEQLARYWYPOTMGQDOEXGOAUDHGUTULTNEHFTFHPGXGVPHGURBDMEGWKLETCBOTNTFQLTAEHMTUGEOAHEVEROXGVPHGDEWTEWGQIEDLPILERWPMOATNGQKQEAHBMVRFKBRMKLXODXFREBHMNUKXRYKLRMFLWDDNCN";

    cout << "[BAN RO CHINH XAC]:\n" << labPf.decrypt(labCiphertext) << "\n";

    return 0;
}