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


int produkTermurah(string data[][3], int i, int jumlahProduk, int termurah) {
    if (i == jumlahProduk) return termurah;

    int harga = stoi(data[i][2]);
    if (harga < stoi(data[termurah][2])) {
        termurah = i;
    }

    return produkTermurah(data, i + 1, jumlahProduk, termurah);
}

int produkTermahal(string data[][3], int i, int jumlahProduk, int termahal) {
    if (i == jumlahProduk) return termahal;

    int harga = stoi(data[i][2]);
    if (harga > stoi(data[termahal][2])) {
        termahal = i;
    }

    return produkTermahal(data, i + 1, jumlahProduk, termahal);
}

int totalStok(string data[100][3], int i, int jumlahProduk, int jumlahStok) {
    if (i == jumlahProduk) return jumlahStok;

    jumlahStok += stoi(data[i][1]);
    return totalStok(data, i + 1, jumlahProduk, jumlahStok);
}

int stokTerbanyak(string data[][3], int i, int jumlahProduk, int terbanyak) {
    if (i == jumlahProduk) return terbanyak;

    int stok = stoi(data[i][1]);
    if (stok > stoi(data[terbanyak][1])) {
        terbanyak = i;
    }

    return stokTerbanyak(data, i + 1, jumlahProduk, terbanyak);
}

int stokTerdikit(string data[][3], int i, int jumlahProduk, int terdikit) {
    if (i == jumlahProduk) return terdikit;

    int stok = stoi(data[i][1]);
    if (stok < stoi(data[terdikit][1])) {
        terdikit = i;
    }

    return stokTerdikit(data, i + 1, jumlahProduk, terdikit);
}