/*  Nama program    :   Linked List Queue Pegawai
    Nama            :   Muhammad Athar Alfarisi (Khaled Meshaal Ahmadinejad Mujaddid Thariq Mardova Fadhilah 250056, M<uhammad Faiz Hariy Nugroho 250029)
    NPM             :   140810250005
    Tanggal buat    :   17 Mei 2026
    Deskripsi       :   Input cetak, enqueue (insert last),
                        dequeue (delete first), tampilkan semua data
*/

#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

struct Pegawai {
    int    NIP;
    string Nama;
    int    Gol;
};

struct NodePegawai {
    Pegawai      pegawai;
    NodePegawai* next;
};

typedef NodePegawai* Pointer;
typedef Pointer      List;

struct Queue {
    List Head;
    List Tail;
};

void   createQueue  (Queue& Q);
void   createElement(Pointer& pBaru);
void   enqueue      (Queue& Q, Pointer pBaru);
void   dequeue      (Queue& Q, Pointer& pHapus);
void   traversal    (Queue Q);
string formatRupiah (long long angka);

long long getGaji(int gol) {
    long long gaji = 0;
    if (gol == 1)
        gaji = 3000000;
    else if (gol == 2)
        gaji = 4000000;
    else
        gaji = 5000000;
    return gaji;
}

long long getTunjangan(int gol) {
    long long tunjangan = 0;
    if (gol == 1)
        tunjangan = (long long)(getGaji(gol) * 1);
    if (gol == 2)
        tunjangan = (long long)(getGaji(gol) * 1.25);
    if (gol == 3)
        tunjangan = (long long)(getGaji(gol) * 1.5);
    return tunjangan;
}

long long getTotal(int gol) {
    return getGaji(gol) + getTunjangan(gol);
}

string formatRupiah(long long angka) {
    string s     = to_string(angka);
    string hasil = "";
    int    sisa  = s.length() % 3;
    for (int i = 0; i < (int)s.length(); i++) {
        if (i != 0 && (i - sisa) % 3 == 0) hasil += '.';
        hasil += s[i];
    }
    return hasil;
}

int main() {
    Pointer pBaru  = NULL;
    Pointer pHapus = NULL;
    int     pOps, n;
    Queue Q;


    createQueue(Q);

    do {
        cout << "\n========================================\n";
        cout << "    Daftar Gaji Pegawai PT INFORMATIKA\n";
        cout << "          (Struktur Queue)              \n";
        cout << "========================================\n";
        cout << "1. Input & Cetak Data Pegawai (Enqueue)\n";
        cout << "2. Hapus Data Head (Dequeue)\n";
        cout << "3. Tampilkan Semua Data\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pOps;

        switch (pOps) {
            case 1:
                cout << "Masukkan jumlah pegawai: ";
                cin >> n;
                for (int i = 0; i < n; i++) {
                    cout << "\n--- Pegawai ke-" << i + 1 << " ---\n";
                    createElement(pBaru);
                    enqueue(Q, pBaru);
                }
                traversal(Q);
                break;

            case 2:
                dequeue(Q, pHapus);
                if (pHapus != NULL) {
                    cout << "Data " << pHapus->pegawai.Nama
                         << " (Head) berhasil dihapus dengan Dequeue.\n";
                    delete pHapus;
                    pHapus = NULL;
                }
                traversal(Q);
                break;

            case 3:
                traversal(Q);
                break;

            case 0:
                cout << "Keluar.\n";
                break;

            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pOps != 0);

    return 0;
}

void createQueue(Queue& Q) {
    Q.Head = NULL;
    Q.Tail = NULL;
}

void createElement(Pointer& pBaru) {
    pBaru = new NodePegawai;
    cout << "NIP      : "; cin >> pBaru->pegawai.NIP;
    cout << "Nama     : "; cin >> pBaru->pegawai.Nama;
    cout << "Golongan : "; cin >> pBaru->pegawai.Gol;
    pBaru->next = NULL;
}

void enqueue(Queue& Q, Pointer pBaru) {
    // InsertLast
    if (Q.Head == NULL && Q.Tail == NULL) {
        Q.Head = pBaru;
        Q.Tail = pBaru;
    } else {
        Q.Tail->next = pBaru;
        Q.Tail       = pBaru;
    }
}

void dequeue(Queue& Q, Pointer& pHapus) {
    // DeleteFirst
    if (Q.Head == NULL && Q.Tail == NULL) {
        cout << "Queue kosong.\n";
        pHapus = NULL;
    } else if (Q.Head->next == NULL) {
        // Kasus 1 elemen
        pHapus = Q.Head;
        Q.Head = NULL;
        Q.Tail = NULL;
    } else {
        // Kasus > 1 elemen
        pHapus       = Q.Head;
        Q.Head       = Q.Head->next;
        pHapus->next = NULL;
    }
}

void traversal(Queue Q) {
    if (Q.Head == NULL) {
        cout << "Data kosong.\n";
        return;
    }

    cout << "\n\t\tDAFTAR GAJI PEGAWAI PT. INFORMATIKA\n";
    cout << "\t\t      (Struktur Queue - FIFO)\n";
    cout << string(80, '-') << "\n";
    cout << left
         << setw(4)  << "No"
         << setw(9)  << "NIP"
         << setw(14) << "Nama"
         << setw(5)  << "Gol"
         << setw(15) << "Gaji"
         << setw(15) << "Tunjangan"
         << setw(15) << "Total" << "\n";
    cout << string(80, '-') << "\n";

    Pointer   bantu         = Q.Head;
    int       no            = 1;
    long long jumlahGaji      = 0;
    long long jumlahTunjangan = 0;
    long long jumlahTotal     = 0;
    int       cnt           = 0;

    while (bantu != NULL) {
        long long gaji      = getGaji(bantu->pegawai.Gol);
        long long tunjangan = getTunjangan(bantu->pegawai.Gol);
        long long total     = gaji + tunjangan;

        jumlahGaji      += gaji;
        jumlahTunjangan += tunjangan;
        jumlahTotal     += total;
        cnt++;

        cout << left
             << setw(4)  << no
             << setw(9)  << bantu->pegawai.NIP
             << setw(14) << bantu->pegawai.Nama
             << setw(5)  << bantu->pegawai.Gol
             << setw(15) << formatRupiah(gaji)
             << setw(15) << formatRupiah(tunjangan)
             << setw(15) << formatRupiah(total) << "\n";

        no++;
        bantu = bantu->next;
    }

    cout << string(80, '-') << "\n";
    cout << left
         << setw(32) << "Jumlah"
         << setw(15) << formatRupiah(jumlahGaji)
         << setw(15) << formatRupiah(jumlahTunjangan)
         << setw(15) << formatRupiah(jumlahTotal) << "\n";
    cout << string(80, '-') << "\n";
    cout << "Rata-rata Gaji Total : " << formatRupiah(jumlahTotal / cnt) << "\n";
    cout << string(80, '-') << "\n";
}