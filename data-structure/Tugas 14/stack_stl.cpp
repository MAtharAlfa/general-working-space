/*  Nama program    :   Tree
    Nama            :   Muhammad Athar Alfarisi (Khaled Meshaal Ahmadinejad Mujaddid Thariq Mardova Fadhilah 250056, M	uhammad Faiz Hariy Nugroho 250029)
    NPM             :   140810250005
    Tanggal buat    :   7 Juni 2026
    Deskripsi       :   Operasi Tree menggunakan STL C++
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <stack>
#include <stdexcept>
using namespace std;


struct Pegawai {
   int    NIP;
   string Nama;
   int    Gol;
};


typedef stack<Pegawai> Stack;


void createElement(Pegawai& pBaru);
void push(Stack& Top, Pegawai pBaru);
Pegawai pop(Stack& Top);
void traversal(Stack Top);


long long getGaji(int gol);
long long getTunjangan(int gol);
long long getTotal(int gol);


int main() {
   Stack   stackPegawai;
   Pegawai pBaru;
   int     pOps, n;


   do {
       cout << "\n========================================\n";
       cout << "    Daftar Gaji Pegawai PT INFORMATIKA\n";
       cout << "          (Struktur Stack)\n";
       cout << "========================================\n";
       cout << "1. Input Data Pegawai (Push)\n";
       cout << "4. Hapus Data Top (Pop)\n";
       cout << "6. Tampilkan Semua Data\n";
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
                   push(stackPegawai, pBaru);
               }


               traversal(stackPegawai);
               break;


           case 4:
               try {
                   Pegawai hapus = pop(stackPegawai);


                   cout << "Data "
                        << hapus.Nama
                        << " (Top) berhasil dihapus dengan Pop.\n";


                   traversal(stackPegawai);
               }
               catch (const runtime_error& e) {
                   cout << "Error : " << e.what() << "\n";
               }
               break;


           case 6:
               traversal(stackPegawai);
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


void push(Stack& Top, Pegawai pBaru) {
   Top.push(pBaru);
}


Pegawai pop(Stack& Top) {
   if (Top.empty())
       throw runtime_error("Stack kosong.");


   Pegawai pHapus = Top.top();
   Top.pop();


   return pHapus;
}


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
   long long g = getGaji(gol);
   long long tunjangan = 0;


   if (gol == 1)
       tunjangan = g;
   else if (gol == 2)
       tunjangan = (long long)(g * 1.25);
   else
       tunjangan = (long long)(g * 1.5);


   return tunjangan;
}


long long getTotal(int gol) {
   return getGaji(gol) + getTunjangan(gol);
}


void traversal(Stack Top) {
   if (Top.empty()) {
       cout << "Data kosong.\n";
       return;
   }


   cout << "\n\t\tDAFTAR GAJI PEGAWAI PT. INFORMATIKA\n";
   cout << "\t\t      (Struktur Stack - LIFO)\n";


   cout << string(80, '-') << "\n";


   cout << left
        << setw(4)  << "No"
        << setw(10) << "NIP"
        << setw(14) << "Nama"
        << setw(5)  << "Gol"
        << setw(13) << "Gaji"
        << setw(13) << "Tunjangan"
        << setw(13) << "Total"
        << "\n";


   cout << string(80, '-') << "\n";


   int no = 1;


   long long jumlahGaji      = 0;
   long long jumlahTunjangan = 0;
   long long jumlahTotal     = 0;
   int cnt                   = 0;


   while (!Top.empty()) {


       Pegawai bantu = Top.top();
       Top.pop();


       long long gaji      = getGaji(bantu.Gol);
       long long tunjangan = getTunjangan(bantu.Gol);
       long long total     = getTotal(bantu.Gol);


       jumlahGaji      += gaji;
       jumlahTunjangan += tunjangan;
       jumlahTotal     += total;
       cnt++;


       cout << left
            << setw(4)  << no
            << setw(10) << bantu.NIP
            << setw(14) << bantu.Nama
            << setw(5)  << bantu.Gol
            << setw(13) << gaji
            << setw(13) << tunjangan
            << setw(13) << total
            << "\n";


       no++;
   }


   cout << string(80, '-') << "\n";


   cout << left
        << setw(33) << "Jumlah"
        << setw(13) << jumlahGaji
        << setw(13) << jumlahTunjangan
        << setw(13) << jumlahTotal
        << "\n";


   cout << string(80, '-') << "\n";


   cout << "Rata-rata Gaji Total : "
        << jumlahTotal / cnt << "\n";


   cout << string(80, '-') << "\n";
}