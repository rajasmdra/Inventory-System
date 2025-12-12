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
        cout << endl << "=== MENU ===" << endl;
        cout << "1. Tambah Produk" << endl;
        cout << "2. Tampilkan Produk" << endl;
        cout << "3. Edit Produk" << endl;
        cout << "4. Hapus Produk" << endl;
        cout << "5. Cari Produk" << endl;
        cout << "6. Urutkan Produk" << endl;
        cout << "7. Analisis Data" << endl;
        cout << "8. Simpan Data" << endl;
        cout << "9. Keluar" << endl;
        cout << "Pilih menu: ";
        cin >> menu;
        cin.ignore();

        if (menu == 1) tambahProduk(data, jumlahProduk);
        else if (menu == 2) tampilkanProduk(data, jumlahProduk);
        else if (menu == 3) editProduk(data, jumlahProduk);
        else if (menu == 4) hapusProduk(data, jumlahProduk);
        else if (menu == 5) cariProduk(data, jumlahProduk);
        else if (menu == 6) urutkanProduk(data, jumlahProduk);
        else if (menu == 7) analisisProduk(data, jumlahProduk);
        else if (menu == 8) simpanData(data, jumlahProduk);
        else if (menu == 9) break;
        else cout << "Input tidak valid." << endl;
    }
}

void app::tambahProduk(string data[100][3], int &jumlahProduk) {
    if (jumlahProduk >= 100) {
        cout << "Data penuh, tidak bisa menambah produk." << endl;
        return;
    }

    string nama, stok, harga;
    cout << "Masukkan nama produk: ";
    getline(cin, nama);
    cout << "Masukkan jumlah stok: ";
    cin >> stok;
    cout << "Masukkan harga produk: ";
    cin >> harga;
    cin.ignore();

    if (!isNumber(stok) || !isNumber(harga)) {
        cout << "Stok dan harga harus angka!" << endl;
        return;
    }
    
    jumlahProduk++;
    data[jumlahProduk][0] = nama;
    data[jumlahProduk][1] = stok;
    data[jumlahProduk][2] = harga;

    cout << "Produk berhasil ditambahkan!" << endl;
}

void app::tampilkanProduk(string data[100][3], int jumlahProduk) {
    if (jumlahProduk == 0) {
        cout << "Belum ada data produk." << endl;
        return;
    }
    cout << endl << "=== DAFTAR PRODUK ===" << endl;
    cout << left;
    cout << setw(4) << "ID"
        << setw(15) << "Nama Produk"
        << setw(15) << "Stok"
        << setw(15) << "Harga" << endl;
    for (int i = 0; i < jumlahProduk; i++) {
        cout << left;
        cout << setw(4) << i + 1
            << setw(15) << data[i][0]
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

    for (int i = hapus - 1; i < jumlahProduk; i++) {
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

    produkEdit--;
    if (infoEdit == 1) data[produkEdit][0] = infoBaru;
    if (infoEdit == 2) data[produkEdit][1] = infoBaru;
    if (infoEdit == 3) data[produkEdit][2] = infoBaru;

    cout << "Produk berhasil diedit" << endl;
}

void app::cariProduk(string data[100][3], int jumlahProduk) {
    string target;
    bool found = false;

    cout << "Masukkan kata kunci: ";
    cin.ignore();
    getline(cin, target);

    cout << endl << "=== HASIL PENCARIAN ===" << endl;

    cout << left;
    cout << setw(4) << "ID"
        << setw(15) << "Nama Produk"
        << setw(15) << "Stok"
        << setw(15) << "Harga" << endl;

    for (int i = 0; i < jumlahProduk; i++) {
        if (ignoreCase(data[i][0], target)) {
            cout << left;
            cout << setw(4) << i + 1
                << setw(15) << data[i][0]
                << setw(15) << data[i][1]
                << setw(15) << data[i][2] << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Produk tidak ditemukan." << endl;
    }
}

void app::urutkanProduk(string data[100][3], int jumlahProduk) {
    int pilihan, urutan;

    if (jumlahProduk == 0) {
        cout << "Belum ada data.\n";
        return;
    }

    string sortData[100][3];
    for (int i = 0; i < jumlahProduk; i++) {
        sortData[i][0] = data[i][0];
        sortData[i][1] = data[i][1];
        sortData[i][2] = data[i][2];
    }

    cout << "\n=== SORTING PRODUK (Shell Sort) ===\n";
    cout << "1. Nama Produk\n";
    cout << "2. Stok\n";
    cout << "3. Harga\n";
    cout << "Pilih kategori sorting: ";
    cin >> pilihan;

    cout << "1. Urutkan dari terkecil" << endl;
    cout << "2. Urutkan dari terbesar" << endl;
    cout << "Pilih urutan: ";
    cin >> urutan;

    for (int gap = jumlahProduk / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < jumlahProduk; i++) {

            string a = sortData[i][0];
            string b = sortData[i][1];
            string c = sortData[i][2];

            int j = i;

            while (j >= gap) {
                bool kondisi = false;

                if (pilihan == 1) { 
                    if (urutan == 1) kondisi = a < sortData[j-gap][0];
                    else kondisi = a > sortData[j-gap][0];
                }
                else if (pilihan == 2) {
                    int x = stoi(b);
                    int y = stoi(sortData[j-gap][1]);
                    if (urutan == 1) kondisi = x < y;
                    else kondisi = x > y;
                }
                else if (pilihan == 3) {
                    int x = stoi(c);
                    int y = stoi(sortData[j-gap][2]);
                    if (urutan == 1) kondisi = x < y;
                    else kondisi = x > y;
                }

                if (!kondisi) break;

                sortData[j][0] = sortData[j-gap][0];
                sortData[j][1] = sortData[j-gap][1];
                sortData[j][2] = sortData[j-gap][2];

                j -= gap;
            }

            sortData[j][0] = a;
            sortData[j][1] = b;
            sortData[j][2] = c;
        }
    }
    
    cout << endl << "=== HASIL SORTING ===" << endl;
    cout << left;
    cout << setw(4) << "ID"
        << setw(15) << "Nama Produk"
        << setw(15) << "Stok"
        << setw(15) << "Harga" << endl;
    for (int i = 0; i < jumlahProduk; i++) {
        cout << left 
            << setw(4) << i + 1
            << setw(15) << sortData[i][0]
            << setw(15) << sortData[i][1]
            << setw(15) << sortData[i][2]<< endl;
    }
}

void app::analisisProduk(string data[100][3], int jumlahProduk) {
    string termahal= 0, termurah = 0;
    for (int i = 0; i < jumlahProduk; i++) {
    }
    cout << "Jumlah produk: " << jumlahProduk << endl;
    cout << "Produk termurah: " << produkTermurah(data, 0, jumlahProduk, 0) << endl;
    cout << "Produk termahal: " << produkTermahal(data, 0, jumlahProduk, 0) << endl;
}

void app::simpanData(string data[100][3], int jumlahProduk) {
    ofstream out("data.txt", ios::trunc);
    for (int i = 0; i < jumlahProduk; i++) {
        out << data[i][0] << "," << data[i][1] << "," << data[i][2] << endl;
    }
    out.close();
}