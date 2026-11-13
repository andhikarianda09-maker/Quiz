#include <iostream>
#include <string>
using namespace std;

const int UKURAN = 20;

struct Mahasiswa {
    long long nim;
    string nama;
    int status;
};

Mahasiswa tabel[UKURAN];

int hash1(long long key) {
    return key % UKURAN;
}

int hash2(long long key) {
    return 19 - (key % 19);
}

void insertData(long long nim, string nama) {
    int indeks = hash1(nim);
    int langkah = hash2(nim);
    int indeksHapus = -1;

    for (int i = 0; i < UKURAN; i++) {
        int posisi = (indeks + i * langkah) % UKURAN;

        if (tabel[posisi].status == 1) {
            if (tabel[posisi].nim == nim) {
                cout << "NIM sudah terdaftar!\n";
                return;
            }
        } else if (tabel[posisi].status == 2) {
            if (indeksHapus == -1) {
                indeksHapus = posisi;
            }
        } else {
            if (indeksHapus != -1) {
                posisi = indeksHapus;
            }

            tabel[posisi].nim = nim;
            tabel[posisi].nama = nama;
            tabel[posisi].status = 1;

            cout << "Data berhasil ditambahkan!\n";
            return;
        }
    }

    if (indeksHapus != -1) {
        tabel[indeksHapus].nim = nim;
        tabel[indeksHapus].nama = nama;
        tabel[indeksHapus].status = 1;
        cout << "Data berhasil ditambahkan!\n";
    } else {
        cout << "Hash Table penuh!\n";
    }
}

void searchData(long long nim) {
    int indeks = hash1(nim);
    int langkah = hash2(nim);

    for (int i = 0; i < UKURAN; i++) {
        int posisi = (indeks + i * langkah) % UKURAN;

        if (tabel[posisi].status == 0) {
            break;
        }

        if (tabel[posisi].status == 1 &&
            tabel[posisi].nim == nim) {
            cout << "Data ditemukan!\n";
            cout << "NIM  : " << tabel[posisi].nim << endl;
            cout << "Nama : " << tabel[posisi].nama << endl;
            return;
        }
    }

    cout << "Data mahasiswa tidak ditemukan!\n";
}

void removeData(long long nim) {
    int indeks = hash1(nim);
    int langkah = hash2(nim);

    for (int i = 0; i < UKURAN; i++) {
        int posisi = (indeks + i * langkah) % UKURAN;

        if (tabel[posisi].status == 0) {
            break;
        }

        if (tabel[posisi].status == 1 &&
            tabel[posisi].nim == nim) {
            tabel[posisi].status = 2;
            cout << "Data berhasil dihapus!\n";
            return;
        }
    }

    cout << "Data mahasiswa tidak ditemukan!\n";
}

void displayData() {
    cout << "\n=== DATA MAHASISWA ===\n";

    for (int i = 0; i < UKURAN; i++) {
        if (tabel[i].status == 1) {
            cout << "Indeks : " << i << endl;
            cout << "NIM    : " << tabel[i].nim << endl;
            cout << "Nama   : " << tabel[i].nama << endl;
            cout << "----------------------\n";
        }
    }
}

int main() {
    int pilihan;
    long long nim;
    string nama;

    for (int i = 0; i < UKURAN; i++) {
        tabel[i].status = 0;
    }

    do {
        cout << "\n=== SISTEM DATA MAHASISWA ===\n";
        cout << "1. Insert Data\n";
        cout << "2. Search Data\n";
        cout << "3. Remove Data\n";
        cout << "4. Display Data\n";
        cout << "5. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "Masukkan NIM: ";
                cin >> nim;
                cin.ignore();
                cout << "Masukkan Nama: ";
                getline(cin, nama);
                insertData(nim, nama);
                break;

            case 2:
                cout << "Masukkan NIM yang dicari: ";
                cin >> nim;
                searchData(nim);
                break;

            case 3:
                cout << "Masukkan NIM yang dihapus: ";
                cin >> nim;
                removeData(nim);
                break;

            case 4:
                displayData();
                break;

            case 5:
                cout << "Program selesai.\n";
                break;

            default:
                cout << "Pilihan tidak valid!\n";
        }

    } while (pilihan != 5);

    return 0;
}
