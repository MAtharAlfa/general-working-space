/*  Nama program    :   Soal 3.B. Queue Linked List Daftar Kendaraan Parkir
    Nama            :   Muhammad Athar Alfarisi
    NPM             :   140810250005
    Tanggal buat    :   22 Juni 2026
    Deskripsi       :   Sebuah program yang mengelola Queue tentang Daftar Kendaraan Parkir menggunakan linked-list.
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

struct Node {
    KendaraanParkir info;
    Node* next;
};

typedef Node* Pointer;
typedef Pointer List;

struct Queue {
    List head;
    List Tail;
};

void createQueue(Queue& Q) {
    Q.head = nullptr;
    Q.Tail = nullptr;
}

void createNode(Pointer& newNode, KendaraanParkir info) {
    newNode = new Node;
    newNode->info = info;
    newNode->next = nullptr;
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

void enqueue(Queue& Q, Pointer newNode) {
    if (Q.head == nullptr) {
        Q.head = newNode;
        Q.Tail = newNode;
    } else {
        Q.Tail->next = newNode;
        Q.Tail = newNode;
    }
}

void dequeue(Queue& Q, Pointer& hasilHapus) {
    if (Q.head == nullptr) {
        cout << "Antrian masih kosong" << endl;
    } else if (Q.head->next == nullptr) {
        hasilHapus = Q.head;
        Q.head = nullptr;
        Q.Tail = nullptr;
    } else {
        hasilHapus = Q.head;
        Q.head = Q.head->next;
        hasilHapus->next = nullptr;
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

    int tempSisa;
    if (tempPulang < tempDatang) tempPulang += (3600*24);
    tempSisa = tempPulang - tempDatang;

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
    if (Q.head == nullptr)
    {
        cout << "Queue kosong" << endl;
        return -1;
    } else {
        Pointer traverse = Q.head;
        int tempJumlah = 0;

        while (traverse != nullptr)
        {
            Waktu lama = getLama(traverse->info.JamMasuk, traverse->info.JamPulang);
            tempJumlah += getBayar(lama, traverse->info.Jenis);
            traverse = traverse->next;
        }
        
        return tempJumlah;
    }
}

string cetakJenis(Pointer p) {
    stringstream ss;
    (p->info.Jenis == 1) ? (ss << "Mobil") : (ss << "Motor");

    string hasil = ss.str();

    return hasil;
}

void cetakTraversal(Queue& Q) {
    if (Q.head == nullptr)
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

    Pointer traverse = Q.head;
    while (traverse != nullptr)
    {
        Waktu lama = getLama(traverse->info.JamMasuk, traverse->info.JamPulang);
        cout << setw(5) << no
        << setw(15) << traverse->info.NoKendaraan 
        << setw(15) << cetakJenis(traverse)
        << setw(25) << printWaktu(traverse->info.JamMasuk) 
        << setw(25) << printWaktu(traverse->info.JamPulang) 
        << setw(20) << printWaktu(lama)
        << setw(15) << getBayar(lama, traverse->info.Jenis) << "\n";

        no++;
        traverse = traverse->next;
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

                Pointer pNew;
                createNode(pNew, info);

                enqueue(Q, pNew);
                break;
            }
            case 2:
            {
                Pointer hapus;
                dequeue(Q, hapus);
                delete hapus;
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