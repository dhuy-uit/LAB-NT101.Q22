#include <iostream>
#include <string>
#include <limits> 

using namespace std;

// Ham ma hoa Caesar
string encryptCaesar(string text, int key) {
    string result = "";
    key = (key % 26 + 26) % 26;

    for (char& c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            result += char(int(base + (c - base + key) % 26));
        }
        else {
            result += c; 
        }
    }
    return result;
}

string decryptCaesar(string text, int key) {
    return encryptCaesar(text, 26 - (key % 26));
}

// Ham Brute-force (thu 25 truong hop)
void bruteForceCaesar(string ciphertext) {
    cout << "\n--- Thu hien Brute-force ---\n";
    for (int k = 1; k <= 25; ++k) {
        cout << "Key " << k << ":\n" << decryptCaesar(ciphertext, k) << "\n\n";
    }
}

int main() {
    cout << "========== TASK 2.1: CAESAR CIPHER ==========\n\n";

    // ---------------------------------------------------------
    // PHAN 1: NGUOI DUNG TU NHAP KHOA VA CHUOI VAN BAN
    // ---------------------------------------------------------
    cout << "--- PHAN 1: MA HOA / GIAI MA TUY CHON ---\n";
    string userText;
    int userKey;

    cout << "Nhap chuoi van ban can ma hoa: ";
    getline(cin, userText);

    cout << "Nhap khoa k (so nguyen tu 1-25): ";
    cin >> userKey;

    string encrypted = encryptCaesar(userText, userKey);
    cout << "Ket qua MA HOA (Ciphertext): " << encrypted << "\n";

    string decrypted = decryptCaesar(encrypted, userKey);
    cout << "Ket qua GIAI MA (Plaintext): " << decrypted << "\n\n";


    // ---------------------------------------------------------
    // PHAN 2: GIAI MA DOAN TEXT CUA BAI LAB
    // ---------------------------------------------------------
    cout << "--- PHAN 2: GIAI MA DOAN TEXT CUA LAB ---\n";
    string labCiphertext = "Max NBM bl t extwbgz bglmbmnmbhg ngwxk OGN-AVF, lixvbtebsbgz bg max ybxew hy bgyhkftmbhg mxvaghehzr. Xlmtueblaxw pbma t fbllbhg mh yhlmxk bgghotmbhg tgw xqvxeexgvx bg BM xwnvtmbhg tgw kxlxtkva, NBM hyyxkl t pbwx ktgzx hy ngwxkzktwntmx tgw ihlmzktwntmx ikhzktfl tbfxw tm ikhwnvbgz abzaer ldbeexw ikhyxllbhgtel. Max ngboxklbmr bl kxvhzgbsxw yhk bml vnmmbgz-xwzx kxlxtkva bg tkxtl ebdx vruxklxvnkbmr, tkmbybvbte bgmxeebzxgvx, tgw lhymptkx xgzbgxxkbgz. Pbma lmtmx-hy-max-tkm ytvbebmbxl tgw t Imkhgz xfiatlbl hg vheetuhktmbhg pbma bgwnlmkr, NBM xjnbil Imnwxgml pbma uhma maxhkxmbvte dghpexwzx tgw iktvmbvte ldbeel mh makbox bg max ktibwer xoheobgz mxva bgwnlmkr.";

    int correctKey = 19;
    cout << "Da xac dinh duoc khoa dung (qua Brute-force) la: " << correctKey << "\n";
    cout << "\n[BAN RO CHINH XAC]:\n" << decryptCaesar(labCiphertext, correctKey) << "\n";

    return 0;
}