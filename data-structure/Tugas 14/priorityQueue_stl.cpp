/*  Nama program    :   Priority Queue
    Nama            :   Muhammad Athar Alfarisi
    NPM             :   1408102500
    Tanggal buat    :   7 Juni 2026
    Deskripsi       :   Operasi Priority Queue menggunakan STL C++
*/


#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
using namespace std;


struct Pegawai
{
        string nip;
        string nama;
        int    gol;
};


typedef queue<Pegawai> antrian_pegawai;


void menu(antrian_pegawai& daftar_pegawai);
void createQueue(antrian_pegawai& daftar_pegawai);


int main()
{
        antrian_pegawai daftar_pegawai;
        createQueue(daftar_pegawai);


        menu(daftar_pegawai);
        return 0;
}


void createQueue(antrian_pegawai& daftar_pegawai)
{
        while (!daftar_pegawai.empty()) daftar_pegawai.pop();
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
        long long n;
        if (gol == 1)
                n = getGaji(gol) * 1;
        else if (gol == 2)
                n = getGaji(gol) * 1.25;
        else n = getGaji(gol) * 1.5;


	return n;
}


string formatRupiah(long long angka)
{
        string s     = to_string(angka);
        string hasil = "";
        int sisa     = s.length() % 3;
        for (int i = 0; i < (int)s.length(); i++)
        {
                if (i != 0 && (i - sisa) % 3 == 0)
                        hasil += '.';
                hasil += s[i];
        }
        return hasil;
}


void insertPegawai(antrian_pegawai& daftar_pegawai)
{
        Pegawai p;
        cout << "NIP      : "; cin >> p.nip;
        cout << "Nama     : "; cin >> p.nama;
        cout << "Golongan : "; cin >> p.gol;


	 antrian_pegawai temp;
        while (!daftar_pegawai.empty() && daftar_pegawai.front().gol >= p.gol)
        {
                temp.push(daftar_pegawai.front());
                daftar_pegawai.pop();
        }




        temp.push(p);
        while (!daftar_pegawai.empty())
        {
                temp.push(daftar_pegawai.front());
                daftar_pegawai.pop();
        }


        daftar_pegawai = temp;


        cout << "Pegawai " << p.nama << " berhasil ditambahkan.\n";


}


void deletePegawai(antrian_pegawai& daftar_pegawai)
{
        if (daftar_pegawai.empty())
        {
                cout << "Antrian kosong!\n";
                return;
        }


        Pegawai p = daftar_pegawai.front();
        daftar_pegawai.pop();


        long long gaji      = getGaji(p.gol);
        long long tunjangan = getTunjangan(p.gol);
        long long total     = gaji + tunjangan;


        cout << "Pegawai \"" << p.nama << "\" (Gol " << p.gol << ") berhasil dilayani.\n";
        cout << "  Gaji      : Rp " << formatRupiah(gaji)      << "\n";
        cout << "  Tunjangan : Rp " << formatRupiah(tunjangan)  << "\n";
        cout << "  Total     : Rp " << formatRupiah(total)      << "\n";
}


void printAll(antrian_pegawai daftar_pegawai)
{
        if (daftar_pegawai.empty())
        {
                cout << "Antrian kosong!\n";
                return;
        }


        long long jumlah_gaji      = 0;
        long long jumlah_tunjangan = 0;
        long long jumlah_total     = 0;
        int cnt                    = 0;


        cout << "\n\t\tDAFTAR ANTRIAN PEGAWAI PT. INFORMATIKA\n";
        cout << "\t\t    (Queue FIFO - urut masuk)\n";
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


        while (!daftar_pegawai.empty())
        {
                Pegawai p   = daftar_pegawai.front();
                daftar_pegawai.pop();


                long long gaji      = getGaji(p.gol);
                long long tunjangan = getTunjangan(p.gol);
                long long total     = gaji + tunjangan;


                jumlah_gaji      += gaji;
                jumlah_tunjangan += tunjangan;
                jumlah_total     += total;
                cnt++;


                cout << left
                     << setw(4)  << cnt
                     << setw(9)  << p.nip
                     << setw(14) << p.nama
                     << setw(5)  << p.gol
                     << setw(15) << formatRupiah(gaji)
                     << setw(15) << formatRupiah(tunjangan)
                     << setw(15) << formatRupiah(total) << "\n";
        }


        cout << string(80, '-') << "\n";
        cout << left
             << setw(32) << "Jumlah"
             << setw(15) << formatRupiah(jumlah_gaji)
             << setw(15) << formatRupiah(jumlah_tunjangan)
             << setw(15) << formatRupiah(jumlah_total) << "\n";
        cout << string(80, '-') << "\n";
        cout << "Rata-rata Gaji Total : " << formatRupiah(jumlah_total / cnt) << "\n";
        cout << string(80, '-') << "\n";
}


void displayMenu()
{
        cout << "\n========================================\n";
        cout << "   Antrian Pegawai PT. INFORMATIKA\n";
        cout << "========================================\n";
        cout << "1. Tampilkan semua\n";
        cout << "2. Masukkan pegawai\n";
        cout << "3. Hapus pegawai\n";
        cout << "0. Selesai\n";
        cout << "Pilihan: ";
}


void menu(antrian_pegawai& daftar_pegawai)
{
        int user_input = -1;
        while (true)
        {
                displayMenu();


                cin >> user_input;
                switch (user_input)
                {
                        case 1:
                                printAll(daftar_pegawai);
                                break;


                        case 2:
                                insertPegawai(daftar_pegawai);
                                break;


                        case 3:
                                deletePegawai(daftar_pegawai);
                                break;


                        case 0: cout << "Terimakasih.\n"; return; break;


                        default: cout << "Pilihan tidak valid.\n"; break;
                }
        }
}
