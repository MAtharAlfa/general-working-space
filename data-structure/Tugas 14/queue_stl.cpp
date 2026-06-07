/*  Nama program    :   Tree
    Nama            :   Muhammad Athar Alfarisi (Khaled Meshaal Ahmadinejad Mujaddid Thariq Mardova Fadhilah 250056, M	uhammad Faiz Hariy Nugroho 250029)
    NPM             :   140810250005
    Tanggal buat    :   7 Juni 2026
    Deskripsi       :   Operasi Tree menggunakan STL C++
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <queue>
#include <stdexcept>
using namespace std;


struct Pegawai {
   int    NIP;
   string Nama;
   int    Gol;
};


typedef queue<Pegawai> Queue;


void      createElement(Pegawai& pBaru);
void      enqueue(Queue& Q, Pegawai pBaru);
Pegawai   dequeue(Queue& Q);
void      traversal(Queue Q);


string    formatRupiah(long long angka);
long long getGaji(int gol);
long long getTunjangan(int gol);
long long getTotal(int gol);


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
       tunjangan = getGaji(gol);
   else if (gol == 2)
       tunjangan = (long long)(getGaji(gol) * 1.25);
   else
       tunjangan = (long long)(getGaji(gol) * 1.5);


   return tunjangan;
}


long long getTotal(int gol) {
   return getGaji(gol) + getTunjangan(gol);
}


string formatRupiah(long long angka) {
   string s = to_string(angka);
   string hasil = "";


   int sisa = s.length() % 3;


   for (int i = 0; i < s.length(); i++) {
       if (i != 0 && (i - sisa) % 3 == 0)
           hasil += '.';


       hasil += s[i];
   }


   return hasil;
}


int main() {
   Queue   queuePegawai;
   Pegawai pBaru;


   int pOps;
   int n;


   do {
       cout << "\n========================================\n";
       cout << "    Daftar Gaji Pegawai PT INFORMATIKA\n";
       cout << "          (Struktur Queue)\n";
       cout << "========================================\n";
       cout << "1. Input Data Pegawai (Enqueue)\n";
       cout << "2. Hapus Data Head (Dequeue)\n";
       cout << "3. Tampilkan Semua Data\n";
       cout << "0. Keluar\n";
       cout << "Pilihan : ";
       cin >> pOps;


       switch (pOps) {


           case 1:
               cout << "Masukkan jumlah pegawai : ";
               cin >> n;


               for (int i = 0; i < n; i++) {
                   cout << "\n--- Pegawai ke-" << i + 1 << " ---\n";


                   createElement(pBaru);
                   enqueue(queuePegawai, pBaru);
               }


               traversal(queuePegawai);
               break;


           case 2:
               try {
                   Pegawai hapus = dequeue(queuePegawai);


                   cout << "Data "
                        << hapus.Nama
                        << " (Head) berhasil dihapus dengan Dequeue.\n";


                   traversal(queuePegawai);
               }
               catch (const runtime_error& e) {
                   cout << "Error : "
                        << e.what()
                        << "\n";
               }
               break;


           case 3:
               traversal(queuePegawai);
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


void createElement(Pegawai& pBaru) {
   cout << "NIP      : ";
   cin >> pBaru.NIP;


   cout << "Nama     : ";
   cin >> pBaru.Nama;


   cout << "Golongan : ";
   cin >> pBaru.Gol;
}


void enqueue(Queue& Q, Pegawai pBaru) {
   Q.push(pBaru);
}


Pegawai dequeue(Queue& Q) {
   if (Q.empty())
       throw runtime_error("Queue kosong.");


   Pegawai pHapus = Q.front();


   Q.pop();


   return pHapus;
}


void traversal(Queue Q) {


   if (Q.empty()) {
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
        << setw(15) << "Total"
        << "\n";


   cout << string(80, '-') << "\n";


   int jumlahPegawai = 0;


   long long jumlahGaji      = 0;
   long long jumlahTunjangan = 0;
   long long jumlahTotal     = 0;


   while (!Q.empty()) {


       Pegawai bantu = Q.front();
       Q.pop();


       long long gaji      = getGaji(bantu.Gol);
       long long tunjangan = getTunjangan(bantu.Gol);
       long long total     = getTotal(bantu.Gol);


       jumlahPegawai++;
       jumlahGaji      += gaji;
       jumlahTunjangan += tunjangan;
       jumlahTotal     += total;


       cout << left
            << setw(4)  << jumlahPegawai
            << setw(9)  << bantu.NIP
            << setw(14) << bantu.Nama
            << setw(5)  << bantu.Gol
            << setw(15) << formatRupiah(gaji)
            << setw(15) << formatRupiah(tunjangan)
            << setw(15) << formatRupiah(total)
            << "\n";
   }


   cout << string(80, '-') << "\n";


   cout << left
        << setw(32) << "Jumlah"
        << setw(15) << formatRupiah(jumlahGaji)
        << setw(15) << formatRupiah(jumlahTunjangan)
        << setw(15) << formatRupiah(jumlahTotal)
        << "\n";


   cout << string(80, '-') << "\n";


   cout << "Rata-rata Gaji Total : "
        << formatRupiah(jumlahTotal / jumlahPegawai)
        << "\n";


   cout << string(80, '-') << "\n";
}
