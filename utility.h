#ifndef UTILITY_H
#define UTILITY_H

#include <string>
using namespace std;

bool isNumber(const string& s);
string toLower(string s);
bool ignoreCase(string text, string key);
int produkTermurah(string data[100][3], int i, int jumlahProduk, int termurah);
int produkTermahal(string data[100][3], int i, int jumlahProduk, int termahal);
int totalStok(string data[100][3], int i, int jumlahProduk, int jumlahStok);
int stokTerbanyak(string data[100][3], int i, int jumlahProduk, int terbanyak);
int stokTerdikit(string data[100][3], int i, int jumlahProduk, int terdikit);

#endif