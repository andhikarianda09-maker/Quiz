#include <iostream>
#include <queue>
#include <stack>
using namespace std;

// Struktur data buku untuk BST
struct Node {
    int id;
    Node* left;
    Node* right;
};

// Struktur data mahasiswa untuk antrean
struct Mahasiswa {
    string nama;
    int idBuku;
};

// Inisialisasi Queue, Stack, dan BST
queue<Mahasiswa> antrean;
stack<Mahasiswa> riwayat;
Node* root = NULL;

// Membuat node baru untuk BST
Node* buatNode(int id) {
    Node* baru = new Node;
    baru->id = id;
    baru->left = NULL;
    baru->right = NULL;
    return baru;
}

// Menambahkan ID buku ke BST
Node* tambahBuku(Node* root, int id) {
    if (root == NULL) {
        return buatNode(id);
    }

    if (id < root->id) {
        root->left = tambahBuku(root->left, id);
    } else if (id > root->id) {
        root->right = tambahBuku(root->right, id);
    } else {
        cout << "ID buku sudah terdaftar!\n";
    }

    return root;
}

// Mencari ID buku dalam BST
bool cariBuku(Node* root, int id) {
    if (root == NULL) {
        return false;
    }

    if (root->id == id) {
        return true;
    } else if (id < root->id) {
        return cariBuku(root->left, id);
    } else {
        return cariBuku(root->right, id);
    }
}

// Traversal Pre-Order
void preOrder(Node* root) {
    if (root != NULL) {
        cout << root->id << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Traversal In-Order
void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        cout << root->id << " ";
        inOrder(root->right);
    }
}

// Traversal Post-Order
void postOrder(Node* root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->id << " ";
    }
}

// Menambahkan mahasiswa ke antrean
void tambahAntrean() {
    Mahasiswa m;

    cout << "Masukkan nama mahasiswa: ";
    cin.ignore();
    getline(cin, m.nama);

    cout << "Masukkan ID buku: ";
    cin >> m.idBuku;

    if (!cariBuku(root, m.idBuku)) {
        cout << "ID buku tidak ditemukan!\n";
        return;
    }

    antrean.push(m);
    cout << "Mahasiswa berhasil masuk antrean!\n";
}

// Memproses peminjaman buku
void prosesPeminjaman() {
    if (antrean.empty()) {
        cout << "Antrean masih kosong!\n";
        return;
    }

    Mahasiswa m = antrean.front();
    antrean.pop();

    cout << "Peminjaman berhasil diproses!\n";
    cout << "Nama mahasiswa: " << m.nama << endl;
    cout << "ID buku: " << m.idBuku << endl;
}

// Mengembalikan buku dan menyimpan riwayat
void kembalikanBuku() {
    Mahasiswa m;

    cout << "Masukkan nama mahasiswa: ";
    cin.ignore();
    getline(cin, m.nama);

    cout << "Masukkan ID buku: ";
    cin >> m.idBuku;

    if (!cariBuku(root, m.idBuku)) {
        cout << "ID buku tidak ditemukan!\n";
        return;
    }

    riwayat.push(m);
    cout << "Buku berhasil dikembalikan!\n";
}

// Menampilkan antrean
void tampilkanAntrean() {
    if (antrean.empty()) {
        cout << "Antrean masih kosong!\n";
        return;
    }

    queue<Mahasiswa> temp = antrean;

    cout << "Daftar antrean peminjaman:\n";

    while (!temp.empty()) {
        cout << temp.front().nama
             << " - ID Buku: " << temp.front().idBuku << endl;
        temp.pop();
    }
}

// Menampilkan riwayat pengembalian
void tampilkanRiwayat() {
    if (riwayat.empty()) {
        cout << "Riwayat pengembalian masih kosong!\n";
        return;
    }

    stack<Mahasiswa> temp = riwayat;

    cout << "Riwayat pengembalian buku:\n";

    while (!temp.empty()) {
        cout << temp.top().nama
             << " - ID Buku: " << temp.top().idBuku << endl;
        temp.pop();
    }
}

// Menghapus seluruh node BST
void hapusBST(Node* root) {
    if (root != NULL) {
        hapusBST(root->left);
        hapusBST(root->right);
        delete root;
    }
}

int main() {
    int pilihan, id;

    do {
        cout << "\n=== SISTEM PERPUSTAKAAN ===\n";
        cout << "1. Tambah ID Buku\n";
        cout << "2. Tambah Antrean Peminjaman\n";
        cout << "3. Proses Peminjaman\n";
        cout << "4. Pengembalian Buku\n";
        cout << "5. Tampilkan Antrean\n";
        cout << "6. Tampilkan Riwayat Pengembalian\n";
        cout << "7. Cari ID Buku\n";
        cout << "8. Traversal Pre-Order\n";
        cout << "9. Traversal In-Order\n";
        cout << "10. Traversal Post-Order\n";
        cout << "11. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "Masukkan ID buku: ";
                cin >> id;
                root = tambahBuku(root, id);
                break;

            case 2:
                tambahAntrean();
                break;

            case 3:
                prosesPeminjaman();
                break;

            case 4:
                kembalikanBuku();
                break;

            case 5:
                tampilkanAntrean();
                break;

            case 6:
                tampilkanRiwayat();
                break;

            case 7:
                cout << "Masukkan ID buku yang dicari: ";
                cin >> id;

                if (cariBuku(root, id)) {
                    cout << "ID buku ditemukan!\n";
                } else {
                    cout << "ID buku tidak ditemukan!\n";
                }
                break;

            case 8:
                cout << "Pre-Order: ";
                preOrder(root);
                cout << endl;
                break;

            case 9:
                cout << "In-Order: ";
                inOrder(root);
                cout << endl;
                break;

            case 10:
                cout << "Post-Order: ";
                postOrder(root);
                cout << endl;
                break;

            case 11:
                cout << "Program selesai.\n";
                break;

            default:
                cout << "Pilihan tidak valid!\n";
        }

    } while (pilihan != 11);

    hapusBST(root);

    return 0;
}
