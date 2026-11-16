#include <algorithm>
#include <cmath>
#include <cstdio>
#include <math.h>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <time.h>

const int n = 34;

char *letters[n - 1] = {"а", "б", "в", "г", "д", "е", "ж", "з", "и", "й", "к", "л", "м", "н", "о", "п", "р",
                        "с", "т", "у", "ф", "х", "ц", "ч", "ш", "щ", "ъ", "ы", "ь", "э", "ю", "я", "ё"};
void shenon();
bool read_text(const char *name);
void sorting_probability();
double p[n];
char *a[n];
int L[n];
int c[n][32];
int sum = 0;

int main(int argc, char *argv[]) {

    const char *name = "text.txt";
    for (int i = 1; i < n; i++) {
        a[i] = letters[i - 1];
        p[i] = 0;
    }
    if (!read_text(name))
        return 1;

    sorting_probability();

    double entropy = 0;
    for (int i = 1; i < n; i++) {
        p[i] /= (double)sum;
        if (p[i] > 0)
            entropy -= p[i] * log2(p[i]);
    }
    shenon();
    double kraft = 0;
    printf("| Символ | Вероятность  | Кодовое слово          | Длина |\n");

    double L_medium = 0;
    for (int i = 1; i < n; i++) {
        if (p[i] == 0)
            continue;
        char word[32 + 1];
        for (int j = 1; j <= L[i]; j++)
            word[j - 1] = (char)('0' + c[i][j]);
        kraft += 1 / (pow(2, L[i]));
        word[L[i]] = '\0';
        printf("|    %s   |  %9.6f   | %-22s |  %3d  |\n", a[i], p[i], word, L[i]);
        L_medium += p[i] * L[i];
    }
    printf("\n");
    printf("| энтропия | ср. длин. код. слова | избыточность |  Крафт |\n");
    printf("|  %5.5f |       %9.6f      |    %.5f   |%5.5f |", entropy, L_medium, L_medium - entropy, kraft);

    const char *text100 = "регулярный осмотр хранилищ выявляет проблемы вовремя и равномерный полив поддерживает развитие ростка";
    std::string encoded = "";
    int encodedLength = 0;

    for (size_t i = 0; i < strlen(text100); i++) {
        int idx = 0;
        for (int j = 1; j < n; j++) {
            if (text100[i] == a[j][0]) {
                idx = j;
                break;
            }
        }

        if (idx > 0 && L[idx] > 0) {
            for (int j = 1; j <= L[idx]; j++) {
                encoded += (char)('0' + c[idx][j]);
                encodedLength++;
            }
        }
    }

    printf("\nЗакодированный текст: %s\n", encoded.c_str());
    printf("Длина: %d бит \n Сжатие: %.2f\n", encodedLength, 800.0 / encodedLength);
    return 0;
}

bool read_text(const char *name) {
    FILE *f = fopen(name, "rb");
    if (!f) {
        printf("Нет файла %s\n", name);
        return false;
    }

    std::string text = "";
    char buf[1024];
    size_t h;
    while ((h = fread(buf, 1, sizeof(buf), f)) > 0) {
        text.append(buf, h);
    }
    fclose(f);

    for (int i = 1; i < n; i++) {
        std::string letter = letters[i - 1];
        size_t pos = 0;
        while ((pos = text.find(letter, pos)) != std::string::npos) {
            p[i] += 1;
            sum++;
            pos += letter.length();
        }
    }
    return true;
}

void sorting_probability() {
    bool b = true;
    while (b) {
        b = false;
        for (int i = 2; i < n; i++)
            if (p[i - 1] < p[i]) {
                double tp = p[i - 1];
                p[i - 1] = p[i];
                p[i] = tp;
                char *ta = a[i - 1];
                a[i - 1] = a[i];
                a[i] = ta;
                b = true;
            }
    }
}

void shenon() {
    double q[n];
    p[0] = 0;
    q[0] = 0;
    for (int i = 1; i < n; i++) {
        q[i] = q[i - 1] + p[i];
        L[i] = (int)ceil(-log2(p[i]));
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= L[i]; j++) {
            q[i - 1] = q[i - 1] * 2;
            c[i][j] = (int)floor(q[i - 1]);
            if (q[i - 1] > 1) {
                q[i - 1] = q[i - 1] - 1;
            }
        }
    }
}