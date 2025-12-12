#include "utility.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <sstream>
#include <string>

using namespace std;

bool isNumber(const string& s) {
    for (char c : s)
        if (!isdigit(c)) return false;
    return true;
}

string toLower(string s) {
    for (char &c : s) c = tolower(c);
    return s;
}

bool ignoreCase(string text, string key) {
    text = toLower(text);
    key  = toLower(key);
    return text.find(key) != string::npos;
}

int produkTermurah(string data[100][3], int i, int jumlahProduk, int termurah) {
    if (i >= jumlahProduk) return termurah;

    // pastikan harga tidak kosong
    if (!data[i][2].empty() && !data[termurah][2].empty()) {
        int hargaNow = stoi(data[i][2]);
        int hargaMin = stoi(data[termurah][2]);

        if (hargaNow < hargaMin) {
            termurah = i;
        }
    }

    return produkTermurah(data, i + 1, jumlahProduk, termurah);
}

int produkTermahal(string data[100][3], int i, int jumlahProduk, int termahal) {
    if (i >= jumlahProduk) return termahal;

    if (!data[i][2].empty() && !data[termahal][2].empty()) {
        int hargaNow = stoi(data[i][2]);
        int hargaMax = stoi(data[termahal][2]);

        if (hargaNow > hargaMax) {
            termahal = i;
        }
    }

    return produkTermahal(data, i + 1, jumlahProduk, termahal);
}
