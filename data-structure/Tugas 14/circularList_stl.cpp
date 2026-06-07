/*  Nama program    :   Linked list
    Nama            :   Muhammad Athar Alfarisi
    NPM             :   140810250005
    Tanggal buat    :   7 Juni 2026
    Deskripsi       :   Operasi Linked List menggunakan STL C++
*/


#include <iostream>
#include <iomanip>
#include <forward_list>
#include <string>


struct Pegawai
{
        std::string nip;
        std::string nama;
        int gol;
};


struct CircularForwardList
{
        std::forward_list<Pegawai> list;
        std::forward_list<Pegawai>::iterator tail;
        bool empty;
};


typedef CircularForwardList circular_list;
typedef circular_list list_pegawai;


void menu(list_pegawai& daftar_pegawai);
void createList(list_pegawai& daftar_pegawai);


int main()
{
        list_pegawai daftar_pegawai;
        createList(daftar_pegawai);


        menu(daftar_pegawai);
        return 0;
}


void createList(list_pegawai& daftar_pegawai)
{
        daftar_pegawai.tail  = daftar_pegawai.list.before_begin();
        daftar_pegawai.empty = true;
}


long long getGaji(int gol)
{
        long long n;
        if (gol == 1)
                n = 3000000;
        else if (gol == 2)
                n = 4000000;
        else n = 5000000;


        return n;
}


long long getTunjangan(int gol)
{
        if (gol == 1) return getGaji(gol) * 1;
        else if (gol == 2) return (long long)(getGaji(gol) * 1.25);
        else return (long long)(getGaji(gol) * 1.5);
}


std::string formatRupiah(long long angka)
{
        std::string s     = std::to_string(angka);
        std::string hasil = "";
        int sisa          = s.length() % 3;
        for (int i = 0; i < (int)s.length(); i++)
        {
                if (i != 0 && (i - sisa) % 3 == 0)
                        hasil += '.';
                hasil += s[i];
        }
        return hasil;
}


void insertPegawai(list_pegawai& daftar_pegawai)
{
        Pegawai p;
        std::cout << "NIP      : "; std::cin >> p.nip;
        std::cout << "Nama     : "; std::cin >> p.nama;
        std::cout << "Golongan : "; std::cin >> p.gol;


        daftar_pegawai.tail  = daftar_pegawai.list.insert_after(daftar_pegawai.tail, p);
        daftar_pegawai.empty = false;


        std::cout << "Pegawai " << p.nama << " berhasil ditambahkan.\n";
}




void hapusPegawai(list_pegawai& daftar_pegawai)
{
        if (daftar_pegawai.empty)
        {
                std::cout << "Daftar pegawai kosong!\n";
                return;
        }


        std::string target_nip;
        std::cout << "Masukkan NIP pegawai yang akan dihapus: ";
        std::cin >> target_nip;


        std::forward_list<Pegawai>::iterator prev = daftar_pegawai.list.before_begin();
        std::forward_list<Pegawai>::iterator curr = daftar_pegawai.list.begin();


        while (curr != daftar_pegawai.list.end())
        {
                if (curr->nip == target_nip)
                {
                        std::cout << "Pegawai " << curr->nama << " berhasil dihapus.\n";


                        if (curr == daftar_pegawai.tail)
                                daftar_pegawai.tail = prev;


                        daftar_pegawai.list.erase_after(prev);


                        if (daftar_pegawai.list.empty())
                                daftar_pegawai.empty = true;


                        return;
                }
                prev = curr;
                ++curr;
        }


        std::cout << "Pegawai dengan NIP " << target_nip << " tidak ditemukan.\n";
}


void printAll(list_pegawai& daftar_pegawai)
{
        if (daftar_pegawai.empty)
        {
                std::cout << "Daftar pegawai kosong!\n";
                return;
        }


        long long jumlah_gaji      = 0;
        long long jumlah_tunjangan = 0;
        long long jumlah_total     = 0;
        int cnt                    = 0;


        std::cout << "\n\t\tDAFTAR GAJI PEGAWAI PT. INFORMATIKA\n";
        std::cout << "\t\t  (Circular Forward List - FIFO)\n";
        std::cout << std::string(80, '-') << "\n";
        std::cout << std::left
                  << std::setw(4)  << "No"
                  << std::setw(9)  << "NIP"
                  << std::setw(14) << "Nama"
                  << std::setw(5)  << "Gol"
                  << std::setw(15) << "Gaji"
                  << std::setw(15) << "Tunjangan"
                  << std::setw(15) << "Total" << "\n";
        std::cout << std::string(80, '-') << "\n";


        std::forward_list<Pegawai>::iterator curr = daftar_pegawai.list.begin();
        while (true)
        {
                long long gaji      = getGaji(curr->gol);
                long long tunjangan = getTunjangan(curr->gol);
                long long total     = gaji + tunjangan;


                jumlah_gaji      += gaji;
                jumlah_tunjangan += tunjangan;
                jumlah_total     += total;
                cnt++;


                std::cout << std::left
                          << std::setw(4)  << cnt
                          << std::setw(9)  << curr->nip
                          << std::setw(14) << curr->nama
                          << std::setw(5)  << curr->gol
                          << std::setw(15) << formatRupiah(gaji)
                          << std::setw(15) << formatRupiah(tunjangan)
                          << std::setw(15) << formatRupiah(total) << "\n";


                if (curr == daftar_pegawai.tail) break;
                ++curr;
        }


        std::cout << std::string(80, '-') << "\n";
        std::cout << std::left
                  << std::setw(32) << "Jumlah"
                  << std::setw(15) << formatRupiah(jumlah_gaji)
                  << std::setw(15) << formatRupiah(jumlah_tunjangan)
                  << std::setw(15) << formatRupiah(jumlah_total) << "\n";
        std::cout << std::string(80, '-') << "\n";
        std::cout << "Rata-rata Gaji Total : " << formatRupiah(jumlah_total / cnt) << "\n";
        std::cout << std::string(80, '-') << "\n";
}


void displayMenu()
{
        std::cout << "\n========================================\n";
        std::cout << "    Daftar Gaji Pegawai PT INFORMATIKA\n";
        std::cout << "========================================\n";
        std::cout << "1. Tampilkan semua\n";
        std::cout << "2. Masukkan pegawai baru\n";
        std::cout << "3. Hapus pegawai\n";
        std::cout << "0. Selesai\n";
        std::cout << "Pilihan: ";
}


void menu(list_pegawai& daftar_pegawai)
{
        int user_input = -1;
        while (true)
        {
                displayMenu();


                std::cin >> user_input;
                switch (user_input)
                {
                        case 1:
                                printAll(daftar_pegawai);
                                break;


                        case 2:
                                insertPegawai(daftar_pegawai);
                                break;


                        case 3:
                                hapusPegawai(daftar_pegawai);
                                break;


                        case 0: std::cout << "Terimakasih.\n"; return; break;


                        default: std::cout << "Pilihan tidak valid.\n"; break;
                }
        }
}
