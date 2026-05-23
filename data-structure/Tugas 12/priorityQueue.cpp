/*  Nama program    :   Singly Circular Linked List Priority Queue IGD
    Nama            :   Muhammad Athar Alfarisi (Khaled Meshaal Ahmadinejad Mujaddid Thariq Mardova Fadhilah 250056, M<uhammad Faiz Hariy Nugroho 250029)
    NPM             :   140810250005
    Tanggal buat    :   23 Mei 2026
    Deskripsi       :   Input cetak, enqueue (insert last), dequeue (delete first), tampilkan semua data. Enqueue dilakukan dengan sistem: nomor 1 paling urgent
*/

#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

struct Pasien {
    int NIK;
    string nama;
    int priority;
};

struct NodePasien {
    Pasien pasien;
    NodePasien* next;
};

typedef NodePasien* Pointer;

struct Queue {
    Pointer head;
    Pointer tail;
};

void createQueue(Queue& Q);
void createElement(Pointer& pBaru);
void enqueue(Queue& Q, Pointer pBaru);
void dequeue(Queue& Q, Pointer& pHapus);
void traversal(Queue Q);
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
        if (i != 0 && (i - sisa) % 3 == 0) hasil += '.';
        hasil += s[i];
    }
    return hasil;
}

int main() {
    Pointer pBaru  = nullptr;
    Pointer pHapus = nullptr;
    int pOps, n;
    Queue Q;

    createQueue(Q);

    do {
        cout << "\n========================================\n";
        cout << "    Daftar Gaji Pasien PT INFORMATIKA\n";
        cout << "          (Struktur Queue)              \n";
        cout << "========================================\n";
        cout << "1. Input & Cetak Data Pasien (Enqueue)\n";
        cout << "2. Hapus Data head (Dequeue)\n";
        cout << "3. Tampilkan Semua Data\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pOps;

        switch (pOps) {
            case 1:
                cout << "Masukkan jumlah Pasien: ";
                cin >> n;
                for (int i = 0; i < n; i++) {
                    cout << "\n--- Pasien ke-" << i + 1 << " ---\n";
                    createElement(pBaru);
                    enqueue(Q, pBaru);
                }
                traversal(Q);
                break;

            case 2:
                dequeue(Q, pHapus);
                if (pHapus != nullptr) {
                    cout << "Data " << pHapus->pasien.nama
                    << " (head) berhasil dihapus dengan Dequeue.\n";
                    delete pHapus;
                    pHapus = nullptr;
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
    Q.head = nullptr;
    Q.tail = nullptr;
}

void createElement(Pointer& pBaru) {
    pBaru = new NodePasien;
    cout << "NIK      : "; cin >> pBaru->pasien.NIK;
    cout << "Nama     : "; cin >> pBaru->pasien.nama;
    cout << "Priority : "; cin >> pBaru->pasien.priority;
    pBaru->next = nullptr;
}

void enqueue(Queue& Q, Pointer pBaru) {
    // InsertLast
    if (Q.head == nullptr) {
        pBaru->next = pBaru;
        Q.head = pBaru;
        Q.tail = pBaru;
    } else {
        Pointer pTraverse = Q.tail;

        do
        {
            if (pTraverse->next->pasien.priority > pBaru->pasien.priority)
            {
                pBaru->next = pTraverse->next;
                pTraverse->next = pBaru;
                if (pTraverse == Q.tail) Q.head = pBaru;
                return;
            } else 
            {
                pTraverse = pTraverse->next;
            }
        } while (pTraverse != Q.tail);

        if (pTraverse == Q.tail)  
        {
            pBaru->next = Q.head;
            Q.tail->next = pBaru;
            Q.tail = pBaru;
        }
    }
}

void dequeue(Queue& Q, Pointer& pHapus) {
    // DeleteFirst
    if (Q.head == nullptr) {
        cout << "Queue kosong.\n";
        pHapus = nullptr;
    } else if (Q.head->next == Q.head) {
        // Kasus 1 elemen
        pHapus = Q.head;
        Q.head = nullptr;
        Q.tail = nullptr;
    } else {
        // Kasus > 1 elemen
        pHapus = Q.head;
        Q.head = Q.head->next;
        Q.tail->next = Q.head;
        pHapus->next = nullptr;
    }
}

void traversal(Queue Q) {
    if (Q.head == nullptr) {
        cout << "Data kosong.\n";
        return;
    }
        cout << "Data ada.\n";

    cout << "\n\t\tDAFTAR GAJI pasien PT. INFORMATIKA\n";
    cout << string(80, '-') << "\n";
    cout << left
    << setw(4)  << "No"
    << setw(9)  << "NIK"
    << setw(14) << "Nama"
    << setw(5)  << "Prioritas\n";
    cout << string(80, '-') << "\n";

    Pointer pBantu = Q.head;
    int no = 1;
    int cnt = 0;

    do {
        cnt++;

        cout << left
        << setw(4)  << no
        << setw(9)  << pBantu->pasien.NIK
        << setw(14) << pBantu->pasien.nama
        << setw(5)  << pBantu->pasien.priority << "\n";

        no++;
        pBantu = pBantu->next;
    } while (pBantu != Q.head);
    cout << string(80, '-') << "\n";
}