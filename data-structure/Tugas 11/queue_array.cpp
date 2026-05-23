/*  Nama program    :   Array Queue Pegawai
    Nama            :   Muhammad Athar Alfarisi (Khaled Meshaal Ahmadinejad Mujaddid Thariq Mardova Fadhilah 250056, M<uhammad Faiz Hariy Nugroho 250029)
    NPM             :   140810250005
    Tanggal buat    :   17 Mei 2026
    Deskripsi       :   Input cetak, enqueue (insert last),
                        dequeue (delete first), tampilkan semua data
                        menggunakan array circular
*/

#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

const int maxElemen = 100;

struct Pegawai {
    int    NIP;
    string Nama;
    int    Gol;
};

struct Queue {
    Pegawai info[maxElemen];
    int     Head;
    int     Tail;
};

void   createQueue (Queue& Q);
void   enqueue     (Queue& Q);
void   dequeue     (Queue& Q);
void   traversal   (Queue  Q);
string formatRupiah(long long angka);

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
        if (i != 0 && (i - sisa) % 3 == 0)
            hasil += '.';
        hasil += s[i];
    }
    return hasil;
}

int main() {
    int pOps, n;
    Queue Q;

    createQueue(Q);

    do {
        cout << "\n========================================\n";
        cout << "    Daftar Gaji Pegawai PT INFORMATIKA\n";
        cout << "      (Queue Array Circular)            \n";
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
                    enqueue(Q);
                }
                traversal(Q);
                break;

            case 2:
                dequeue(Q);
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
    Q.Head = 0;
    Q.Tail = -1;
}

void enqueue(Queue& Q) {
    // insertQueue

    if (Q.Tail == maxElemen-1) {
        // Kasus kosong pertama kali
        cout << "Antrian sudah penuh!\n";
    } else {
        Q.Tail = Q.Tail + 1;
        
        cout << "NIP      : "; cin >> Q.info[Q.Tail].NIP;
        cout << "Nama     : "; cin >> Q.info[Q.Tail].Nama;
        cout << "Golongan : "; cin >> Q.info[Q.Tail].Gol;
    }
}

void dequeue(Queue& Q) {
    // deleteQueue circular
    Pegawai elemenHapus;

    if (Q.Head > Q.Tail) {
        // Kasus kosong
        cout << "Antrian kosong.\n";
    } else {
        elemenHapus = Q.info[Q.Head];
        for (int i = 0; i < Q.Tail; i++)
        {
            Q.info[i] = Q.info[i+1];
        }
           
        --Q.Tail;
    }
}

void traversal(Queue Q) {
    if (Q.Tail == -1) {
        cout << "Data kosong.\n";
        return;
    }

    cout << "\n\t\tDAFTAR GAJI PEGAWAI PT. INFORMATIKA\n";
    cout << "\t\t    (Queue Array Circular - FIFO)\n";
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

    long long jumlahGaji      = 0;
    long long jumlahTunjangan = 0;
    long long jumlahTotal     = 0;
    int       cnt             = 0;
    int       i               = Q.Head;

    while (true) {
        long long gaji      = getGaji(Q.info[i].Gol);
        long long tunjangan = getTunjangan(Q.info[i].Gol);
        long long total     = gaji + tunjangan;

        jumlahGaji      += gaji;
        jumlahTunjangan += tunjangan;
        jumlahTotal     += total;
        cnt++;

        cout << left
             << setw(4)  << cnt
             << setw(9)  << Q.info[i].NIP
             << setw(14) << Q.info[i].Nama
             << setw(5)  << Q.info[i].Gol
             << setw(15) << formatRupiah(gaji)
             << setw(15) << formatRupiah(tunjangan)
             << setw(15) << formatRupiah(total) << "\n";

        if (i == Q.Tail) break;
        ++i;
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