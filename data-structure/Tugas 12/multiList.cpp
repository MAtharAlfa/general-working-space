/*  Nama program   :   Multi list Singly Circular Linked List Priority Queue IGD
   Nama            :   Khaled Meshaal Ahmadinejad Mujaddid Thariq Mardova Fadhilah 250056 (Athar 250005, Faiz 250029)
   NPM             :   140810250056
   Tanggal buat    :   23 Mei 2026
   Deskripsi       :   insert first/last dan delete first divisi & karyawan,
                       traversal divisi, traversal divisi+karyawan, cari karyawan by NIP,
                       dan filter karyawan per divisi.
*/


#include <iostream>
#include <string>
#include <iomanip>
using namespace std;


struct Karyawan {
   string nip;
   string nama;
   Karyawan* next;
};


struct Divisi {
   string namaDivisi;
   Karyawan* firstKar;
   Divisi* next;
};


typedef Divisi*   ptrDivisi;
typedef Karyawan* ptrKaryawan;
typedef ptrDivisi ListDivisi;


void        createListDivisi(ListDivisi& first);
void        createElemDivisi(ptrDivisi& pBaru, const string& namaDivisi);
void        createElemKaryawan(ptrKaryawan& pBaru, const string& nip, const string& nama);


ptrDivisi   tailDivisi(ListDivisi first);
ptrDivisi   cariDivisi(ListDivisi first, const string& namaDivisi);
ptrKaryawan tailKaryawan(ptrKaryawan firstKar);


void        insertFirstDivisi(ListDivisi& first, ptrDivisi pBaru);
void        insertLastDivisi(ListDivisi& first, ptrDivisi pBaru);
void        deleteFirstDivisi(ListDivisi& first, ptrDivisi& pHapus);


void        insertFirstKaryawan(ListDivisi first, const string& namaDivisi, ptrKaryawan pBaru);
void        insertLastKaryawan(ListDivisi first, const string& namaDivisi, ptrKaryawan pBaru);
void        deleteFirstKaryawan(ListDivisi first, const string& namaDivisi, ptrKaryawan& pHapus);
void        deleteKaryawanByNIP(ListDivisi first, const string& namaDivisi, const string& nip, ptrKaryawan& pHapus);


void        cetakGaris(int lebar);
void        traversalDivisi(ListDivisi first);
void        tampilSemuaDivisiKaryawan(ListDivisi first);
void        cariKaryawanByNIP(ListDivisi first, const string& nip);
void        tampilKaryawanPerDivisi(ListDivisi first, const string& namaDivisi);
void        tampilMenu();


int main() {
   ListDivisi first;
   createListDivisi(first);


   int pilihan;
   do {
       tampilMenu();
       cin >> pilihan;
       cin.ignore();


       switch (pilihan)
       {
        case 0:
            cout << "Program selesai.\n";
            break;
        case 1:
        {
           int n;
           cout << "Masukkan jumlah Divisi: ";
           cin >> n;
           cin.ignore();
           for (int i = 0; i < n; i++) {
               cout << "\n--- Divisi ke-" << i + 1 << " ---\n";
               string nama;
               cout << "Nama Divisi: ";
               getline(cin, nama);
               ptrDivisi pBaru;
               createElemDivisi(pBaru, nama);
               insertLastDivisi(first, pBaru);
               cout << "[+] Divisi \"" << nama << "\" ditambahkan.\n";
           }
       }
            break;
        case 2:
        {
           ptrDivisi pHapus;
           deleteFirstDivisi(first, pHapus);
           if (pHapus != NULL) {
               cout << "[+] Divisi \"" << pHapus->namaDivisi << "\" dilepas dari list.\n";
               delete pHapus;
           }
        }
            break;
        case 3:
        {
           string divisi;
           cout << "Nama Divisi tujuan: ";
           getline(cin, divisi);
           int n;
           cout << "Masukkan jumlah Karyawan: ";
           cin >> n;
           cin.ignore();
           for (int i = 0; i < n; i++) {
               cout << "\n--- Karyawan ke-" << i + 1 << " ---\n";
               string nip, nama;
               cout << "NIP Karyawan  : ";
               getline(cin, nip);
               cout << "Nama Karyawan : ";
               getline(cin, nama);
               ptrKaryawan pBaru;
               createElemKaryawan(pBaru, nip, nama);
               insertLastKaryawan(first, divisi, pBaru);
               cout << "[+] Karyawan \"" << nama << "\" ditambahkan.\n";
           }
       }
            break;
        case 4:
        {
           string divisi;
           cout << "Nama Divisi: ";
           getline(cin, divisi);
           ptrKaryawan pHapus;
           deleteFirstKaryawan(first, divisi, pHapus);
           if (pHapus != NULL) {
               cout << "[+] Karyawan \"" << pHapus->nama << "\" (NIP: " << pHapus->nip << ") dilepas.\n";
               delete pHapus;
           }
       }
            break;
        case 5:
        {
           string divisi, nip;
           cout << "Nama Divisi  : ";
           getline(cin, divisi);
           cout << "NIP Karyawan : ";
           getline(cin, nip);
           ptrKaryawan pHapus;
           deleteKaryawanByNIP(first, divisi, nip, pHapus);
           if (pHapus != NULL) {
               cout << "[+] Karyawan \"" << pHapus->nama << "\" (NIP: " << pHapus->nip << ") dilepas.\n";
               delete pHapus;
           }
       }
            break;
        case 6:
           traversalDivisi(first);
            break;
        case 7:
           tampilSemuaDivisiKaryawan(first);
            break;
        case 8:
        {
            string nip;
            cout << "NIP yang dicari: ";
            getline(cin, nip);
            cariKaryawanByNIP(first, nip);
        }
            break;
        case 9:
        {
           string divisi;
           cout << "Nama Divisi: ";
           getline(cin, divisi);
           tampilKaryawanPerDivisi(first, divisi);
        }
            break;
        default:
           cout << "[!] Pilihan tidak valid.\n";
            break;
       }
   } while (pilihan != 0);

   return 0;
}


void createListDivisi(ListDivisi& first) {
   first = NULL;
}


void createElemDivisi(ptrDivisi& pBaru, const string& namaDivisi) {
   pBaru = new Divisi;
   pBaru->namaDivisi = namaDivisi;
   pBaru->firstKar   = NULL;
   pBaru->next       = NULL;
}


void createElemKaryawan(ptrKaryawan& pBaru, const string& nip, const string& nama) {
   pBaru = new Karyawan;
   pBaru->nip  = nip;
   pBaru->nama = nama;
   pBaru->next = NULL;
}


ptrDivisi tailDivisi(ListDivisi first) {
   if (first == NULL) return NULL;
   ptrDivisi p = first;
   while (p->next != first) p = p->next;
   return p;
}


ptrDivisi cariDivisi(ListDivisi first, const string& namaDivisi) {
   if (first == NULL) return NULL;
   ptrDivisi p = first;
   do {
       if (p->namaDivisi == namaDivisi) return p;
       p = p->next;
   } while (p != first);
   return NULL;
}


ptrKaryawan tailKaryawan(ptrKaryawan firstKar) {
   if (firstKar == NULL) return NULL;
   ptrKaryawan p = firstKar;
   while (p->next != firstKar) p = p->next;
   return p;
}


void insertFirstDivisi(ListDivisi& first, ptrDivisi pBaru) {
   if (first == NULL) {
       first       = pBaru;
       pBaru->next = first;
   } else {
       ptrDivisi tail = tailDivisi(first);
       pBaru->next    = first;
       tail->next     = pBaru;
       first          = pBaru;
   }
}


void insertLastDivisi(ListDivisi& first, ptrDivisi pBaru) {
   if (first == NULL) {
       first       = pBaru;
       pBaru->next = first;
   } else {
       ptrDivisi tail = tailDivisi(first);
       tail->next     = pBaru;
       pBaru->next    = first;
   }
}


// Melepas divisi pertama dari list, node dikembalikan via pHapus
void deleteFirstDivisi(ListDivisi& first, ptrDivisi& pHapus) {
   if (first == NULL) {
       cout << "[!] List divisi kosong.\n";
       pHapus = NULL;
       return;
   }
   pHapus = first;
   if (first->next == first) { // satu-satunya node
       first = NULL;
   } else {
       ptrDivisi tail = tailDivisi(first);
       tail->next     = first->next;
       first          = first->next;
   }
   pHapus->next = NULL;
}


void insertFirstKaryawan(ListDivisi first, const string& namaDivisi, ptrKaryawan pBaru) {
   ptrDivisi pDiv = cariDivisi(first, namaDivisi);
   if (pDiv == NULL) {
       cout << "[!] Divisi \"" << namaDivisi << "\" tidak ditemukan.\n";
       return;
   }
   if (pDiv->firstKar == NULL) {
       pDiv->firstKar = pBaru;
       pBaru->next    = pDiv->firstKar;
   } else {
       ptrKaryawan tail = tailKaryawan(pDiv->firstKar);
       pBaru->next      = pDiv->firstKar;
       tail->next       = pBaru;
       pDiv->firstKar   = pBaru;
   }
}


void insertLastKaryawan(ListDivisi first, const string& namaDivisi, ptrKaryawan pBaru) {
   ptrDivisi pDiv = cariDivisi(first, namaDivisi);
   if (pDiv == NULL) {
       cout << "[!] Divisi \"" << namaDivisi << "\" tidak ditemukan.\n";
       return;
   }
   if (pDiv->firstKar == NULL) {
       pDiv->firstKar = pBaru;
       pBaru->next    = pDiv->firstKar;
   } else {
       ptrKaryawan tail = tailKaryawan(pDiv->firstKar);
       tail->next       = pBaru;
       pBaru->next      = pDiv->firstKar;
   }
}


// Melepas karyawan pertama dari divisi, node dikembalikan via pHapus
void deleteFirstKaryawan(ListDivisi first, const string& namaDivisi, ptrKaryawan& pHapus) {
   ptrDivisi pDiv = cariDivisi(first, namaDivisi);
   if (pDiv == NULL) {
       cout << "[!] Divisi \"" << namaDivisi << "\" tidak ditemukan.\n";
       pHapus = NULL;
       return;
   }
   if (pDiv->firstKar == NULL) {
       cout << "[!] Tidak ada karyawan di divisi \"" << namaDivisi << "\".\n";
       pHapus = NULL;
       return;
   }
   pHapus = pDiv->firstKar;
   if (pDiv->firstKar->next == pDiv->firstKar) { // satu-satunya
       pDiv->firstKar = NULL;
   } else {
       ptrKaryawan tail = tailKaryawan(pDiv->firstKar);
       tail->next       = pDiv->firstKar->next;
       pDiv->firstKar   = pDiv->firstKar->next;
   }
   pHapus->next = NULL;
}


// Melepas karyawan berdasarkan NIP, node dikembalikan via pHapus
void deleteKaryawanByNIP(ListDivisi first, const string& namaDivisi, const string& nip, ptrKaryawan& pHapus) {
   ptrDivisi pDiv = cariDivisi(first, namaDivisi);
   if (pDiv == NULL) {
       cout << "[!] Divisi \"" << namaDivisi << "\" tidak ditemukan.\n";
       pHapus = NULL;
       return;
   }
   if (pDiv->firstKar == NULL) {
       cout << "[!] Tidak ada karyawan di divisi \"" << namaDivisi << "\".\n";
       pHapus = NULL;
       return;
   }


   ptrKaryawan prev = NULL, curr = pDiv->firstKar;
   ptrKaryawan tail = tailKaryawan(pDiv->firstKar);
   bool ketemu      = false;
   do {
       if (curr->nip == nip) { ketemu = true; break; }
       prev = curr;
       curr = curr->next;
   } while (curr != pDiv->firstKar);


   if (!ketemu) {
       cout << "[!] NIP \"" << nip << "\" tidak ditemukan.\n";
       pHapus = NULL;
       return;
   }


   if (curr->next == pDiv->firstKar && prev == NULL) // satu-satunya
       pDiv->firstKar = NULL;
   else if (curr == pDiv->firstKar) {               // hapus head
       tail->next     = pDiv->firstKar->next;
       pDiv->firstKar = pDiv->firstKar->next;
   } else {                                         // hapus non-head
       prev->next = curr->next;
   }


   pHapus       = curr;
   pHapus->next = NULL;
}


void cetakGaris(int lebar) {
   for (int i = 0; i < lebar; i++) cout << '-';
   cout << '\n';
}


// Traversal list divisi saja (tanpa karyawan)
void traversalDivisi(ListDivisi first) {
   cout << "\n--- Daftar Divisi ---\n";
   if (first == NULL) { cout << "  (Belum ada data)\n"; return; }
   int no = 1;
   ptrDivisi p = first;
   do {
       cout << no++ << ". " << p->namaDivisi << "\n";
       p = p->next;
   } while (p != first);
}


// Traversal semua divisi beserta seluruh karyawannya
void tampilSemuaDivisiKaryawan(ListDivisi first) {
   cout << "\n" << string(60, '=') << "\n";
   cout << "    Daftar Divisi dan Karyawan PT KomputerKu Tbk\n";
   cout << string(60, '=') << "\n";
   cout << left << setw(4)  << "No."
                << setw(14) << "Nama Divisi"
                << setw(16) << "NIP Karyawan"
                << setw(18) << "Nama Karyawan" << "\n";
   cetakGaris(60);


   if (first == NULL) {
       cout << "  (Belum ada data)\n";
       cetakGaris(60);
       return;
   }


   ptrDivisi pDiv = first;
   int no = 1;
   do {
       if (pDiv->firstKar == NULL) {
           cout << left << setw(4) << no << setw(14) << pDiv->namaDivisi
                << setw(16) << "-" << setw(18) << "-" << "\n";
       } else {
           bool firstRow = true;
           ptrKaryawan pKar = pDiv->firstKar;
           do {
               if (firstRow) {
                   cout << left << setw(4) << no << setw(14) << pDiv->namaDivisi
                        << setw(16) << pKar->nip << setw(18) << pKar->nama << "\n";
                   firstRow = false;
               } else {
                   cout << left << setw(4) << "" << setw(14) << ""
                        << setw(16) << pKar->nip << setw(18) << pKar->nama << "\n";
               }
               pKar = pKar->next;
           } while (pKar != pDiv->firstKar);
       }
       no++;
       pDiv = pDiv->next;
   } while (pDiv != first);


   cetakGaris(60);
}


void cariKaryawanByNIP(ListDivisi first, const string& nip) {
   cout << "\n--- Cari Karyawan NIP: " << nip << " ---\n";
   if (first == NULL) { cout << "[!] Data kosong.\n"; return; }


   bool ketemu = false;
   ptrDivisi pDiv = first;
   do {
       if (pDiv->firstKar != NULL) {
           ptrKaryawan pKar = pDiv->firstKar;
           do {
               if (pKar->nip == nip) {
                   cout << "  Ditemukan!\n";
                   cout << "  NIP    : " << pKar->nip        << "\n";
                   cout << "  Nama   : " << pKar->nama       << "\n";
                   cout << "  Divisi : " << pDiv->namaDivisi << "\n";
                   ketemu = true;
               }
               pKar = pKar->next;
           } while (pKar != pDiv->firstKar);
       }
       pDiv = pDiv->next;
   } while (pDiv != first);


   if (!ketemu)
       cout << "  [!] NIP \"" << nip << "\" tidak ditemukan.\n";
}


void tampilKaryawanPerDivisi(ListDivisi first, const string& namaDivisi) {
   cout << "\n--- Karyawan Divisi: " << namaDivisi << " ---\n";
   ptrDivisi pDiv = cariDivisi(first, namaDivisi);
   if (pDiv == NULL) { cout << "  [!] Divisi tidak ditemukan.\n"; return; }
   if (pDiv->firstKar == NULL) { cout << "  (Belum ada karyawan)\n"; return; }


   cout << left << setw(4) << "No." << setw(12) << "NIP" << "Nama\n";
   cetakGaris(36);
   int no = 1;
   ptrKaryawan pKar = pDiv->firstKar;
   do {
       cout << left << setw(4) << no++ << setw(12) << pKar->nip << pKar->nama << "\n";
       pKar = pKar->next;
   } while (pKar != pDiv->firstKar);
   cetakGaris(36);
}


void tampilMenu() {
   cout << "\n========= MENU MULTI LIST =========\n";
   cout << "1. Tambah Divisi\n";
   cout << "2. Hapus Divisi Pertama\n";
   cout << "3. Tambah Karyawan ke Divisi\n";
   cout << "4. Hapus Karyawan Pertama dari Divisi\n";
   cout << "5. Hapus Karyawan by NIP\n";
   cout << "6. Tampil Daftar Divisi\n";
   cout << "7. Tampil Semua Divisi & Karyawan\n";
   cout << "8. Cari Karyawan by NIP\n";
   cout << "9. Tampil Karyawan per Divisi\n";
   cout << "0. Keluar\n";
   cout << "===================================\n";
   cout << "Pilihan: ";
}
