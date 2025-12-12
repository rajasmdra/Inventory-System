#ifndef APP_H
#define APP_H

#include <string>
using namespace std;

class app {
public:
    void run();
private:
    void tambahProduk(string data[100][3], int &jumlahProduk);
    void tampilkanProduk(string data[100][3], int jumlahProduk);
    void editProduk(string data[100][3], int jumlahProduk);
    void hapusProduk(string data[100][3], int &jumlahProduk);
    void cariProduk(string data[100][3], int jumlahProduk);
    void urutkanProduk(string data[100][3], int jumlahProduk);
    void analisisProduk(string data[100][3], int jumlahProduk);
    void simpanData(string data[100][3], int jumlahProduk);
};

#endif
