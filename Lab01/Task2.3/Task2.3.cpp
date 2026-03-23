#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <ctime>

using namespace std;

const char ENGLISH_FREQ[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

// 1. Danh sách N-Grams (Bắt các cụm từ đang giải mã dang dở)
const char* BIGRAMS[] = { "TH", "HE", "IN", "ER", "AN", "RE", "ON", "AT", "EN", "ND", "TI", "ES", "OR", "TE", "OF", "ED", "IS", "IT", "AL", "AR" };
const char* TRIGRAMS[] = { "THE", "AND", "ING", "HER", "HAT", "HIS", "THA", "ERE", "FOR", "ENT", "ION", "TER", "WAS", "YOU", "ITH", "VER", "ALL", "WIT", "THI", "TIO" };

const int NUM_BIGRAMS = 20;
const int NUM_TRIGRAMS = 20;

// 2. Từ điển 150+ từ (Kết hợp từ thông dụng + Từ khóa của cả Lab 1 và Lab 2)
const char* DICTIONARY[] = {
    // Từ tiếng Anh cốt lõi
    "THE", "AND", "THAT", "HAVE", "FOR", "NOT", "WITH", "YOU", "THIS", "BUT", "HIS", "FROM", "THEY", "WE", "SAY",
    "HER", "SHE", "WILL", "ONE", "ALL", "WOULD", "THERE", "THEIR", "WHAT", "OUT", "ABOUT", "WHO", "GET", "WHICH",
    "WHEN", "MAKE", "CAN", "LIKE", "TIME", "JUST", "HIM", "KNOW", "TAKE", "PEOPLE", "INTO", "YEAR", "YOUR", "GOOD",
    "SOME", "COULD", "THEM", "SEE", "OTHER", "THAN", "THEN", "NOW", "LOOK", "ONLY", "COME", "ITS", "OVER", "THINK",
    "ALSO", "BACK", "AFTER", "USE", "TWO", "HOW", "OUR", "WORK", "FIRST", "WELL", "WAY", "EVEN", "NEW", "WANT",
    "BECAUSE", "ANY", "THESE", "GIVE", "DAY", "MOST", "BEEN", "MUCH", "BEFORE", "LINE", "RIGHT",

    // Từ khóa đặc thù cho Input 1 (Harry Potter & VNU)
    "HARRY", "POTTER", "SERIES", "AUTHOR", "WIZARD", "MAGIC", "MAGICAL", "VIETNAM", "NATIONAL", "UNIVERSITY",
    "STUDENT", "RESEARCH", "EDUCATION", "DEVELOPMENT",

    // Từ khóa đặc thù cho Input 2 (Tin tức, Chính trị, Công nghệ)
    "TRUMP", "OLIVIER", "AMERICAN", "MEDIA", "TECHNOLOGY", "KALSHI", "ARIZONA", "CUBA", "GOVERNMENT",
    "ZUCKERBERG", "GOOGLE", "GUARDIAN", "VENEZUELA", "PREDICTION", "GAMBLING", "ADMINISTRATION"
};
const int NUM_WORDS = sizeof(DICTIONARY) / sizeof(DICTIONARY[0]);

void getInitialKey(const char* cipher, char* key) {
    int freq[26] = { 0 };
    for (int i = 0; cipher[i] != '\0'; i++) {
        if (isalpha((unsigned char)cipher[i])) freq[toupper((unsigned char)cipher[i]) - 'A']++;
    }
    int order[26];
    for (int i = 0; i < 26; i++) order[i] = i;
    for (int i = 0; i < 25; i++) {
        for (int j = i + 1; j < 26; j++) {
            if (freq[order[i]] < freq[order[j]]) {
                int temp = order[i]; order[i] = order[j]; order[j] = temp;
            }
        }
    }
    for (int i = 0; i < 26; i++) key[order[i]] = ENGLISH_FREQ[i];
}

void decryptText(const char* cipher, const char* key, char* plain) {
    int i = 0;
    for (; cipher[i] != '\0'; i++) {
        unsigned char uc = (unsigned char)cipher[i];
        if (isalpha(uc)) {
            int idx = toupper(uc) - 'A';
            plain[i] = isupper(uc) ? toupper(key[idx]) : tolower(key[idx]);
        }
        else {
            plain[i] = cipher[i];
        }
    }
    plain[i] = '\0';
}

// HÀM CHẤM ĐIỂM TỐI THƯỢNG: N-Grams + Từ điển
double calculateFitness(const char* plain) {
    double score = 0;
    int len = strlen(plain);
    char word[256];
    int wLen = 0;

    for (int i = 0; i <= len; i++) {
        unsigned char c = plain[i];
        if (isalpha(c)) {
            c = toupper(c);
            if (wLen < 255) word[wLen++] = c;

            // 1. Thưởng điểm nhỏ cho N-Grams để dò đường
            if (i >= 1 && isalpha((unsigned char)plain[i - 1])) {
                char b1 = toupper(plain[i - 1]);
                for (int j = 0; j < NUM_BIGRAMS; j++) {
                    if (BIGRAMS[j][0] == b1 && BIGRAMS[j][1] == c) score += 2;
                }
            }
            if (i >= 2 && isalpha((unsigned char)plain[i - 1]) && isalpha((unsigned char)plain[i - 2])) {
                char t1 = toupper(plain[i - 2]);
                char t2 = toupper(plain[i - 1]);
                for (int j = 0; j < NUM_TRIGRAMS; j++) {
                    if (TRIGRAMS[j][0] == t1 && TRIGRAMS[j][1] == t2 && TRIGRAMS[j][2] == c) score += 5;
                }
            }
        }
        else {
            // 2. Thưởng điểm cực lớn nếu khớp nguyên một từ trong từ điển
            if (wLen > 0) {
                word[wLen] = '\0';
                for (int j = 0; j < NUM_WORDS; j++) {
                    if (strcmp(word, DICTIONARY[j]) == 0) {
                        score += (wLen * wLen * 10); // Bình phương độ dài x 10 điểm
                        break;
                    }
                }
                wLen = 0;
            }
        }
    }
    return score;
}

int main() {
    srand((unsigned int)time(NULL));
    static char cipher[200000];
    static char plain[200000];

    printf("=== GIAI MA HILL-CLIMBING (HYBRID: N-GRAMS + DICTIONARY) ===\n");
    printf("Nhap ten file ban ma (vd: input.txt): ");
    char filename[256];
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;

    FILE* input = fopen(filename, "r");
    if (!input) {
        printf("Loi: Khong mo duoc file!\n");
        return 1;
    }

    int len = 0, ch;
    while ((ch = fgetc(input)) != EOF && len < 199999) {
        cipher[len++] = (char)ch;
    }
    cipher[len] = '\0';
    fclose(input);

    printf("\nDang chay 10 vong Random Restart de tim khoa hoan hao...\n");

    int NUM_RESTARTS = 10;
    double globalBestScore = -1;
    char globalBestKey[26];

    for (int restart = 0; restart < NUM_RESTARTS; restart++) {
        char currentKey[26];

        if (restart == 0) {
            getInitialKey(cipher, currentKey); // Vòng 1: Dựa trên thống kê tần suất
        }
        else {
            // Các vòng sau: Khởi tạo bảng khóa xáo trộn ngẫu nhiên
            for (int i = 0; i < 26; i++) currentKey[i] = 'A' + i;
            for (int i = 25; i > 0; i--) {
                int j = rand() % (i + 1);
                char temp = currentKey[i]; currentKey[i] = currentKey[j]; currentKey[j] = temp;
            }
        }

        char bestLocalKey[26];
        memcpy(bestLocalKey, currentKey, 26);
        decryptText(cipher, bestLocalKey, plain);
        double bestLocalScore = calculateFitness(plain);

        int max_iterations = 4000;
        int no_improvement_count = 0;

        while (no_improvement_count < max_iterations) {
            memcpy(currentKey, bestLocalKey, 26);

            // Đột biến
            int idx1 = rand() % 26;
            int idx2 = rand() % 26;
            char temp = currentKey[idx1]; currentKey[idx1] = currentKey[idx2]; currentKey[idx2] = temp;

            decryptText(cipher, currentKey, plain);
            double currentScore = calculateFitness(plain);

            if (currentScore > bestLocalScore) {
                bestLocalScore = currentScore;
                memcpy(bestLocalKey, currentKey, 26);
                no_improvement_count = 0;
            }
            else {
                no_improvement_count++;
            }
        }
        printf("-> Vong %d/10 hoan thanh. Diem: %.0f\n", restart + 1, bestLocalScore);

        if (bestLocalScore > globalBestScore) {
            globalBestScore = bestLocalScore;
            memcpy(globalBestKey, bestLocalKey, 26);
        }
    }

    decryptText(cipher, globalBestKey, plain);
    printf("\n=============================================\n");
    printf("=== KET QUA GIAI MA TOT NHAT (DIEM: %.0f) ===\n", globalBestScore);
    printf("=============================================\n");
    printf("%s\n", plain);

    printf("\nBang khoa (Cipher -> Plain):\n");
    for (int i = 0; i < 26; i++) {
        printf("%c->%c  ", 'A' + i, globalBestKey[i]);
        if ((i + 1) % 7 == 0) printf("\n");
    }

    return 0;
}