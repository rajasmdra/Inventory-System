#include "app.h"
#include "utility.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <iomanip>
using namespace std;

void app::run() {
    string data[100][3];
    int jumlahProduk = 0;

    ifstream file("data.txt");
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
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

    int menu;
    while (true) {
        cout << "\n=== MENU ===\n";
        cout << "1. Tambah Produk\n";
        cout << "2. Tampilkan Produk\n";
        cout << "3. Edit Produk\n";
        cout << "4. Hapus Produk\n";
        cout << "5. Cari Produk\n";
        cout << "6. Keluar\n";
        cout << "Pilih menu: ";
        cin >> menu;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (menu == 1) tambahProduk(data, jumlahProduk);
        else if (menu == 2) tampilkanProduk(data, jumlahProduk);
        else if (menu == 3) editProduk(data, jumlahProduk);
        else if (menu == 4) hapusProduk(data, jumlahProduk);
        else if (menu == 5) cariProduk(data, jumlahProduk);
        else if (menu == 6) break;
        else cout << "Input tidak valid.\n";
    }

    ofstream out("data.txt", ios::trunc);
    for (int i = 0; i < jumlahProduk; i++) {
        out << data[i][0] << "," << data[i][1] << "," << data[i][2] << endl;
    }
    out.close();
}

void app::tambahProduk(string data[100][3], int &jumlahProduk) {
    if (jumlahProduk >= 100) {
        cout << "Data penuh, tidak bisa menambah produk.\n";
        return;
    }

    string nama, stok, harga;
    cout << "Masukkan nama produk: ";
    getline(cin, nama);
    cout << "Masukkan jumlah stok: ";
    cin >> stok;
    cout << "Masukkan harga produk: ";
    cin >> harga;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (!isNumber(stok) || !isNumber(harga)) {
        cout << "Stok dan harga harus angka!\n";
        return;
    }
    
    jumlahProduk++;
    data[jumlahProduk][0] = nama;
    data[jumlahProduk][1] = stok;
    data[jumlahProduk][2] = harga;

    cout << "Produk berhasil ditambahkan!\n";
}

void app::tampilkanProduk(string data[100][3], int jumlahProduk) {
    if (jumlahProduk == 0) {
        cout << "Belum ada data produk.\n";
        return;
    }
    cout << "\n=== DAFTAR PRODUK ===\n";
    for (int i = 0; i < jumlahProduk; i++) {
        cout << left;
        if (i == 0) cout << setw(4) << "ID";
        else cout << setw(4) << i;
        cout << setw(15) << data[i][0]
            << setw(15) << data[i][1]
            << setw(15) << data[i][2] << endl;
    }
}

void app::hapusProduk(string data[100][3], int &jumlahProduk) {
    tampilkanProduk(data, jumlahProduk);
    
    int hapus;
    while (true) {
        cout << endl << "Pilih produk yang ingin dihapus: ";
        cin >> hapus;

        if (hapus < 1 || hapus > jumlahProduk) cout << "Input tidak valid, silahkan coba lagi" << endl;
        else break;
    }

    for (int i = hapus; i < jumlahProduk; i++) {
        data[i][0] = data [i + 1][0];
        data[i][1] = data [i + 1][1];
        data[i][2] = data [i + 1][2];
    }
    jumlahProduk--;

    cout << endl << "Produk berhasil dihapus" << endl;
}

void app::editProduk(string data[100][3], int jumlahProduk) {
    tampilkanProduk(data, jumlahProduk);
    
    int produkEdit, infoEdit;
    while (true) {
        cout << endl << "Pilih produk yang ingin diedit: ";
        cin >> produkEdit;

        if (produkEdit < 1 || produkEdit > jumlahProduk) cout << "Input tidak valid, silahkan coba lagi" << endl;
        else break;
    }
    
    while (true){
        cout << "1. Nama Produk" << endl;
        cout << "2. Stok" << endl;
        cout << "3. Harga" << endl;
        cout << "Pilih informasi yang ingin diedit: ";
        cin >> infoEdit;
        if (infoEdit < 1 || infoEdit > 3) cout << "Input tidak valid, silahkan coba lagi" << endl;
        else break;
    }
    
    string infoBaru;
    cout << "Masukkan informasi baru: ";
    cin.ignore();
    getline(cin, infoBaru);

    if (infoEdit == 1) data[produkEdit][0] = infoBaru;
    if (infoEdit == 2) data[produkEdit][1] = infoBaru;
    if (infoEdit == 3) data[produkEdit][2] = infoBaru;

    cout << "Produk berhasil diedit" << endl;
}

void app::cariProduk(string data[100][3], int jumlahProduk) {
    string target;
    int infoCari;
    bool found = false;

    while (true) {
        cout << "1. Nama Produk\n";
        cout << "2. Stok\n";
        cout << "3. Harga\n";
        cout << "Cari berdasarkan: ";
        cin >> infoCari;

        if (infoCari < 1 || infoCari > 3)
            cout << "Input tidak valid, silahkan coba lagi\n";
        else
            break;
    }

    cout << "Masukkan kata kunci: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, target);

    cout << "\n=== HASIL PENCARIAN ===\n\n";

    for (int i = 0; i < jumlahProduk; i++) {
        bool match = false;

        if (infoCari == 1) match = containsIgnoreCase(data[i][0], target);
        if (infoCari == 2) match = containsIgnoreCase(data[i][1], target);
        if (infoCari == 3) match = containsIgnoreCase(data[i][2], target);

        if (match) {
            cout << "ID    : " << i << endl;
            cout << "Nama  : " << data[i][0] << endl;
            cout << "Stok  : " << data[i][1] << endl;
            cout << "Harga : " << data[i][2] << endl;
            cout << "--------------------------\n";
            found = true;
        }
    }

    if (!found) {
        cout << "Produk tidak ditemukan.\n";
    }
}