#include <iostream>
#include <queue>
#include <climits>
#include <cctype>
using namespace std;

const int JUMLAH = 6;
const int INF = 999999;

char vertex[JUMLAH] = {'A', 'B', 'C', 'D', 'E', 'F'};

int graph[JUMLAH][JUMLAH] = {
    {0, 4, 2, 0, 0, 0},
    {4, 0, 1, 5, 3, 0},
    {2, 1, 0, 8, 6, 0},
    {0, 5, 8, 0, 2, 4},
    {0, 3, 6, 2, 0, 3},
    {0, 0, 0, 4, 3, 0}
};

int cariIndex(char v) {
    v = toupper(v);

    for (int i = 0; i < JUMLAH; i++) {
        if (vertex[i] == v) {
            return i;
        }
    }

    return -1;
}

// Breadth First Search
void BFS(int awal) {
    bool dikunjungi[JUMLAH] = {false};
    queue<int> q;

    dikunjungi[awal] = true;
    q.push(awal);

    cout << "Hasil BFS: ";

    while (!q.empty()) {
        int sekarang = q.front();
        q.pop();

        cout << vertex[sekarang] << " ";

        for (int i = 0; i < JUMLAH; i++) {
            if (graph[sekarang][i] != 0 &&
                !dikunjungi[i]) {

                dikunjungi[i] = true;
                q.push(i);
            }
        }
    }

    cout << endl;
}

// Depth First Search
void DFSRekursif(int sekarang, bool dikunjungi[]) {
    dikunjungi[sekarang] = true;
    cout << vertex[sekarang] << " ";

    for (int i = 0; i < JUMLAH; i++) {
        if (graph[sekarang][i] != 0 &&
            !dikunjungi[i]) {

            DFSRekursif(i, dikunjungi);
        }
    }
}

void DFS(int awal) {
    bool dikunjungi[JUMLAH] = {false};

    cout << "Hasil DFS: ";
    DFSRekursif(awal, dikunjungi);
    cout << endl;
}

// Algoritma Dijkstra
void Dijkstra(int awal, int tujuan) {
    int jarak[JUMLAH];
    int parent[JUMLAH];
    bool dikunjungi[JUMLAH] = {false};

    for (int i = 0; i < JUMLAH; i++) {
        jarak[i] = INF;
        parent[i] = -1;
    }

    jarak[awal] = 0;

    for (int i = 0; i < JUMLAH; i++) {
        int minimum = INF;
        int sekarang = -1;

        for (int j = 0; j < JUMLAH; j++) {
            if (!dikunjungi[j] && jarak[j] < minimum) {
                minimum = jarak[j];
                sekarang = j;
            }
        }

        if (sekarang == -1) {
            break;
        }

        dikunjungi[sekarang] = true;

        for (int j = 0; j < JUMLAH; j++) {
            if (graph[sekarang][j] != 0 &&
                !dikunjungi[j] &&
                jarak[sekarang] + graph[sekarang][j] < jarak[j]) {

                // Baris yang sudah diperbaiki
                jarak[j] = jarak[sekarang] + graph[sekarang][j];
                parent[j] = sekarang;
            }
        }
    }

    if (jarak[tujuan] == INF) {
        cout << "Rute tidak ditemukan!\n";
        return;
    }

    int rute[JUMLAH];
    int panjang = 0;
    int sekarang = tujuan;

    while (sekarang != -1) {
        rute[panjang++] = sekarang;
        sekarang = parent[sekarang];
    }

    cout << "Rute terpendek: ";

    for (int i = panjang - 1; i >= 0; i--) {
        cout << vertex[rute[i]];

        if (i > 0) {
            cout << " -> ";
        }
    }

    cout << "\nTotal jarak: " << jarak[tujuan] << endl;
}

// Menampilkan Adjacency Matrix
void tampilkanGraph() {
    cout << "\nAdjacency Matrix:\n    ";

    for (int i = 0; i < JUMLAH; i++) {
        cout << vertex[i] << " ";
    }

    cout << endl;

    for (int i = 0; i < JUMLAH; i++) {
        cout << vertex[i] << "   ";

        for (int j = 0; j < JUMLAH; j++) {
            cout << graph[i][j] << " ";
        }

        cout << endl;
    }
}

int main() {
    int pilihan;
    char awal, tujuan;
    int indexAwal, indexTujuan;

    do {
        cout << "\n=== SISTEM PENCARIAN RUTE KAMPUS ===\n";
        cout << "1. Tampilkan Adjacency Matrix\n";
        cout << "2. Breadth First Search (BFS)\n";
        cout << "3. Depth First Search (DFS)\n";
        cout << "4. Dijkstra (Rute Terpendek)\n";
        cout << "5. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tampilkanGraph();
                break;

            case 2:
                cout << "Masukkan vertex awal (A-F): ";
                cin >> awal;

                indexAwal = cariIndex(awal);

                if (indexAwal == -1) {
                    cout << "Vertex tidak valid!\n";
                } else {
                    BFS(indexAwal);
                }
                break;

            case 3:
                cout << "Masukkan vertex awal (A-F): ";
                cin >> awal;

                indexAwal = cariIndex(awal);

                if (indexAwal == -1) {
                    cout << "Vertex tidak valid!\n";
                } else {
                    DFS(indexAwal);
                }
                break;

            case 4:
                cout << "Masukkan vertex awal (A-F): ";
                cin >> awal;

                cout << "Masukkan vertex tujuan (A-F): ";
                cin >> tujuan;

                indexAwal = cariIndex(awal);
                indexTujuan = cariIndex(tujuan);

                if (indexAwal == -1 || indexTujuan == -1) {
                    cout << "Vertex tidak valid!\n";
                } else {
                    Dijkstra(indexAwal, indexTujuan);
                }
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
