#include "utility.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <sstream>
#include <string>

using namespace std;

void writeFile(string data[][3], int &jumlahProduk) {
    ifstream file("data.txt");
    string line;


    while (getline(file, line)) {
        stringstream ss(line);
        string value;
        int col = 0;

        while (getline(ss, value, ',')) {
            data[jumlahProduk][col] = value;
            col++;
        }
        jumlahProduk++;
    }
    file.close();
}

bool isNumber(const string& s) {
    for (char c : s)
        if (!isdigit(c)) return false;
    return true;
}

string toLower(string s) {
    for (char &c : s) c = tolower(c);
    return s;
}

bool containsIgnoreCase(string text, string key) {
    text = toLower(text);
    key  = toLower(key);
    return text.find(key) != string::npos; // partial matching
}

