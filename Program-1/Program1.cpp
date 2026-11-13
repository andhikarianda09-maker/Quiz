#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Mahasiswa {
    string nim;
    string nama;
    int nilai;
    Mahasiswa* next;
};

Mahasiswa* head = NULL;

int* dataNilai = NULL;
int jumlah = 0;
int kapasitas = 2;

// Menambah kapasitas Dynamic Array
void tambahKapasitas() {
    kapasitas *= 2;

    int* baru = new int[kapasitas];

    for (int i = 0; i < jumlah; i++) {
        baru[i] = dataNilai[i];
    }

    delete[] dataNilai;
    dataNilai = baru;
}

// Menambahkan data mahasiswa
void tambahMahasiswa() {
    Mahasiswa* baru = new Mahasiswa;

    cout << "Masukkan NIM   : ";
    cin >> baru->nim;

    Mahasiswa* cek = head;

    while (cek != NULL) {
        if (cek->nim == baru->nim) {
            cout << "NIM sudah terdaftar!\n";
            delete baru;
            return;
        }

        cek = cek->next;
    }

    cout << "Masukkan Nama  : ";
    getline(cin >> ws, baru->nama);

    cout << "Masukkan Nilai : ";
    cin >> baru->nilai;

    if (baru->nilai < 0 || baru->nilai > 100) {
        cout << "Nilai harus 0 sampai 100!\n";
        delete baru;
        return;
    }

    baru->next = NULL;

    if (head == NULL) {
        head = baru;
    } else {
        Mahasiswa* bantu = head;

        while (bantu->next != NULL) {
            bantu = bantu->next;
        }

        bantu->next = baru;
    }

    if (jumlah == kapasitas) {
        tambahKapasitas();
    }

    dataNilai[jumlah] = baru->nilai;
    jumlah++;

    cout << "Data mahasiswa berhasil ditambahkan!\n";
}

// Menampilkan data mahasiswa
void tampilkanMahasiswa() {
    Mahasiswa* bantu = head;

    cout << "\n========== DATA MAHASISWA ==========\n";

    if (head == NULL) {
        cout << "Belum ada data mahasiswa.\n";
        return;
    }

    cout << left << setw(15) << "NIM"
         << setw(20) << "Nama"
         << "Nilai\n";

    while (bantu != NULL) {
        cout << left << setw(15) << bantu->nim
             << setw(20) << bantu->nama
             << bantu->nilai << endl;

        bantu = bantu->next;
    }
}

// Linear Search berdasarkan NIM
void linearSearch(string cari) {
    Mahasiswa* bantu = head;

    while (bantu != NULL) {
        if (bantu->nim == cari) {
            cout << "\nData mahasiswa ditemukan!\n";
            cout << "NIM   : " << bantu->nim << endl;
            cout << "Nama  : " << bantu->nama << endl;
            cout << "Nilai : " << bantu->nilai << endl;
            return;
        }

        bantu = bantu->next;
    }

    cout << "Mahasiswa tidak ditemukan!\n";
}

// Insertion Sort dari kecil ke besar
void insertionSort() {
    for (int i = 1; i < jumlah; i++) {
        int key = dataNilai[i];
        int j = i - 1;

        while (j >= 0 && dataNilai[j] > key) {
            dataNilai[j + 1] = dataNilai[j];
            j--;
        }

        dataNilai[j + 1] = key;
    }
}

// Menampilkan nilai yang sudah diurutkan
void tampilkanNilaiUrut() {
    if (jumlah == 0) {
        cout << "Belum ada nilai mahasiswa.\n";
        return;
    }

    insertionSort();

    cout << "\n===== NILAI SETELAH DIURUTKAN =====\n";

    for (int i = 0; i < jumlah; i++) {
        cout << dataNilai[i] << " ";
    }

    cout << endl;
}

// Binary Search berdasarkan nilai
void binarySearch(int cari) {
    insertionSort();

    int awal = 0;
    int akhir = jumlah - 1;

    while (awal <= akhir) {
        int tengah = (awal + akhir) / 2;

        if (dataNilai[tengah] == cari) {
            cout << "Nilai " << cari << " ditemukan!\n";
            return;
        }
        else if (dataNilai[tengah] < cari) {
            awal = tengah + 1;
        }
        else {
            akhir = tengah - 1;
        }
    }

    cout << "Nilai " << cari << " tidak ditemukan!\n";
}

// Menghapus seluruh data
void hapusSemua() {
    while (head != NULL) {
        Mahasiswa* hapus = head;
        head = head->next;
        delete hapus;
    }

    delete[] dataNilai;
}

int main() {
    dataNilai = new int[kapasitas];

    int pilihan;
    string nim;
    int nilai;

    do {
        cout << "\n===== SISTEM PENGELOLAAN NILAI MAHASISWA =====\n";
        cout << "1. Tambah Data Mahasiswa\n";
        cout << "2. Tampilkan Data Mahasiswa\n";
        cout << "3. Cari Mahasiswa berdasarkan NIM\n";
        cout << "4. Urutkan Nilai (Insertion Sort)\n";
        cout << "5. Cari Nilai (Binary Search)\n";
        cout << "6. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahMahasiswa();
                break;

            case 2:
                tampilkanMahasiswa();
                break;

            case 3:
                cout << "Masukkan NIM yang dicari: ";
                cin >> nim;
                linearSearch(nim);
                break;

            case 4:
                tampilkanNilaiUrut();
                break;

            case 5:
                if (jumlah == 0) {
                    cout << "Belum ada nilai mahasiswa.\n";
                } else {
                    cout << "Masukkan nilai yang dicari: ";
                    cin >> nilai;
                    binarySearch(nilai);
                }
                break;

            case 6:
                cout << "Program selesai.\n";
                break;

            default:
                cout << "Pilihan tidak valid!\n";
        }

    } while (pilihan != 6);

    hapusSemua();

    return 0;
}
