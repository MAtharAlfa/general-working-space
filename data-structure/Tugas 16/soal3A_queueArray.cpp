/*  Nama program    :   Soal 3.A. Queue Array Daftar Kendaraan Parkir
    Nama            :   Muhammad Athar Alfarisi
    NPM             :   140810250005
    Tanggal buat    :   22 Juni 2026
    Deskripsi       :   Sebuah program yang mengelola Queue tentang Daftar Kendaraan Parkir menggunakan array
*/

#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

struct Waktu {
    int jam, menit, detik;
};

struct KendaraanParkir {
    string NoKendaraan;
    int Jenis;
    Waktu JamMasuk;
    Waktu JamPulang;
};

const int maxElement = 255;

struct Queue {
    KendaraanParkir info[maxElement];
    int head;
    int tail;
};

void createQueue(Queue& Q) {
    Q.head = 0;
    Q.tail = -1;
}

void inputDataKendaraan(KendaraanParkir &info) {
    cout << "No Kendaraan: ";
    cin.ignore();
    getline(cin, info.NoKendaraan);

    cout << "Jenis (1 = Mobil, 2 = Motor): ";
    cin >> info.Jenis;

    cout << "Jam Datang (Jam Menit Detik): ";
    cin >> info.JamMasuk.jam >> info.JamMasuk.menit >> info.JamMasuk.detik;

    cout << "Jam Pulang (Jam Menit Detik): ";
    cin >> info.JamPulang.jam >> info.JamPulang.menit >> info.JamPulang.detik;
}


void enqueue(Queue& Q, KendaraanParkir newInfo) {
    if (Q.tail == maxElement - 1) {
        cout << "Antrian sudah penuh" << endl;
    } else {
        ++Q.tail;
        Q.info[Q.tail] = newInfo;
    }
}

void dequeue(Queue& Q, KendaraanParkir& hasilHapus) {
    if (Q.head > Q.tail) {
        cout << "Antrian masih kosong" << endl;
    } else {
        hasilHapus = Q.info[Q.head];
        for (int i = 0; i < Q.tail; i++)
        {
            Q.info[i] = Q.info[i+1];
        }
        --Q.tail;
    }
}

int waktuToSecond(Waktu& inputWaktu) {
    int temp = 0;

    temp += (inputWaktu.jam*3600);
    temp += (inputWaktu.menit*60);
    temp += (inputWaktu.detik);

    return temp;
}

Waktu getLama(Waktu& waktuDatang, Waktu& waktuPulang) {
    int tempDatang = waktuToSecond(waktuDatang), tempPulang = waktuToSecond(waktuPulang);

    int tempSisa = tempPulang - tempDatang;

    Waktu tempHasil;
    tempHasil.jam = tempSisa/3600;
    tempSisa %= 3600;
    tempHasil.menit = tempSisa/60;
    tempSisa %= 60;
    tempHasil.detik = tempSisa;

    return tempHasil;
}

string printWaktu(Waktu& inputWaktu) {
    stringstream ss;
    ss << inputWaktu.jam << ":" << inputWaktu.menit << ":" << inputWaktu.detik;

    string hasil = ss.str();
    return hasil;
}

int getBayar(Waktu& waktuLama, int jenis) {
    int tempHasil = 0;

    if (jenis == 1)
    {
        --waktuLama.jam;
        tempHasil += 5000;

        tempHasil += waktuLama.jam*3000;

        if (waktuLama.menit > 0 || waktuLama.detik > 0) tempHasil += 3000;
    } else 
    {
        --waktuLama.jam;
        tempHasil += 3000;

        tempHasil += waktuLama.jam*2000;

        if (waktuLama.menit > 0 || waktuLama.detik > 0) tempHasil += 2000;
    }
    
    return tempHasil;
}

int getJumlahBayar(Queue& Q) {
     if (Q.head > Q.tail)
    {
        cout << "Queue kosong" << endl;
        return -1;
    } else {
        int traverse = Q.tail, tempJumlah = 0;

        while (traverse >= 0)
        {
            Waktu lama = getLama(Q.info[traverse].JamMasuk, Q.info[traverse].JamPulang);
            tempJumlah += getBayar(lama, Q.info[traverse].Jenis);
            --traverse;
        }
        
        return tempJumlah;
    }
}

string cetakJenis(Queue Q, int i) {
    stringstream ss;
    (Q.info[i].Jenis == 1) ? (ss << "Mobil") : (ss << "Motor");

    string hasil = ss.str();

    return hasil;
}

void cetakTraversal(Queue& Q) {
    if (Q.head > Q.tail)
    {
        cout << "Queue kosong" << endl;
        return;
    }
    
    int no = 1;

    cout << "\n\nDaftar Kendaraan Parkir PT Parkir Aman" << endl;
    cout << setfill('-') << setw(131) << "" << endl;
    cout << setfill(' ');

    cout << left
        << setw(5) << "No"
        << setw(15) << "No Kend."
        << setw(15) << "Jenis"
        << setw(25) << "Jam Datang"
        << setw(25) << "Jam Pulang"
        << setw(20) << "Lama Parkir"
        << setw(15) << "Bayar"
        << endl;

    cout << setfill('-') << setw(131) << "" << endl;
    cout << setfill(' ');

    for (size_t i = 0; i <= Q.tail; ++i)
    {
        Waktu lama = getLama(Q.info[i].JamMasuk, Q.info[i].JamPulang);
        cout << setw(5) << no
        << setw(15) << Q.info[i].NoKendaraan 
        << setw(15) << cetakJenis(Q, i)
        << setw(25) << printWaktu(Q.info[i].JamMasuk) 
        << setw(25) << printWaktu(Q.info[i].JamPulang) 
        << setw(20) << printWaktu(lama)
        << setw(15) << getBayar(lama, Q.info[i].Jenis) << "\n";

        no++;
    }

    cout << setfill('-') << setw(131) << "" << endl;
    cout << setfill(' ');

    cout << "Jumlah Bayar: " << getJumlahBayar(Q) << endl;
}

void printMenu() {
    cout << "\n\nDaftar Kendaraan Parkir PT Parkir Aman" << endl;
    cout << "---------- MENU ----------\n"
    << "1. Enqueue\n"
    << "2. Dequeue\n"
    << "3. Print all\n"
    << "0. Quit\n"
    << "input: ";
}

void menu(Queue &Q) {
    int input = -1;
    while (input != 0)
    {
        printMenu();
        cin >> input;

        switch (input)
        {
            case 1:
            {
                KendaraanParkir info;
                inputDataKendaraan(info);
                enqueue(Q, info);
                break;
            }
            case 2:
            {
                KendaraanParkir hapus;
                dequeue(Q, hapus);
                break;
            }
            case 3:
                cetakTraversal(Q);
                break;

            default: 
                cout << "Terimakasih sudah menggunakan" << endl; break;

        }
    }
}

int main()
{
    Queue daftarParkir;
    createQueue(daftarParkir);
    menu(daftarParkir);
    return 0;
}