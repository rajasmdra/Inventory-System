#ifndef UTILITY_H
#define UTILITY_H

#include <string>
using namespace std;

void writeFile(string data[][3], int &jumlahProduk);
bool isNumber(const string& s);
string toLower(string s);
bool containsIgnoreCase(string text, string key);

#endif
