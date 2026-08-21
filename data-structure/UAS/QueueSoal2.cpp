#include <iostream>

using namespace std; //Mending pake ini kalo nulis di kertas biar lebih cepet

//definisi struct Mahasiswa
struct Mahasiswa{
    string NPM;
    string nama;
    int nilai;
};

struct NodeMhs{ //hanya mengandung data dan next karena singly linked list
    Mahasiswa data;
    NodeMhs* next;
};

typedef NodeMhs* PointerMhs;
typedef PointerMhs List; //- Pointer dan List sama-sama merupakan pointer ke NodeMhs, hanya beda nama. 
                      //- Kenapa dibedakan? Mungkin biar lebih jelas, kalau list selalu mencatat kepala dari sebuah list (jadi mencakup keseluruhan)
                      //sedangkan, Pointer bisa mengarah ke siapa aja.
                      
                      //Note: Tapi itu semua asumsi saya doang dan kata Prof kita gak boleh asumsi, karena asumsi itu kuburan kita or smtg. Kalau mau jawaban yang bener tanya pak Akmal.

struct Queue{
    List head; //head mencatat list singly secara keseluruhan
    List tail; //tail hanya mencatat NodeMhs paling akhir (definisi Queue pake List ngikut ppt pak Akmal)
};

void createList(Queue& Q){ //pass by ref, biar ngubah head & tail aslinya.
    Q.head = nullptr;
    Q.tail = nullptr;  
}

PointerMhs createElement(string newNPM, string newNama, int newNilai){ //karena kita mau isi value pas manggil fungsi (argument) literal string, parameter string di sini pake pass by value. contoh: createElement("25001", "test", 100). Yang dalam tanda kutip dua: "xx" itu literal string
    PointerMhs newElement = new NodeMhs;

    newElement->data.NPM = newNPM;
    newElement->data.nama = newNama;
    newElement->data.nilai = newNilai;
    newElement->next = nullptr;

    return newElement;
}

//Untuk Queue linked-list, biasanya pake insertLast & deleteFirst
void insertLast(Queue& Q, PointerMhs& newPtr){ //pass by reference agar langsung menggunakan data aslinya (bukan copy).
    if (Q.head == nullptr) 
    {
        Q.head = newPtr;
        Q.tail = newPtr;
    } else 
    {
        Q.tail->next = newPtr;
        Q.tail = Q.tail->next;
    }
};

void deleteFirst(Queue& Q, PointerMhs& pHapus){ //pHapus dipake agar deletenya di luar fungsi.
    if (Q.head == nullptr)
    {
        pHapus = nullptr;
        cout << "List Queue kosong";
        return;
    } else if (Q.head == Q.tail)
    {
        pHapus = Q.head;
        Q.head = nullptr;
        Q.tail = nullptr;
    } else {
        pHapus = Q.head;
        Q.head = Q.head->next;
        pHapus->next = nullptr;
    }
}

double rataRataNilai(Queue& Q) {
    if (Q.head == nullptr) return 0;
    PointerMhs current = Q.head;
    double total = 0;
    int jumlah = 0;
    while (current != nullptr) {
        total += current->data.nilai;
        jumlah++;
        current = current->next;
    }
    return total/jumlah; //konversi (typecast) ke double secara implisit, karena total udah double. 
}

char tentukanHM(Mahasiswa& mhs){ //pass by ref agar lebih efisien
    char HM;
    if (mhs.nilai >= 80 && mhs.nilai <= 100)
    {
        HM = 'A';
    } else if (mhs.nilai >= 68) {
        HM = 'B';
    } else if (mhs.nilai >= 55) {
        HM = 'C';
    } else if (mhs.nilai >= 45) {
        HM = 'D';
    } else if (mhs.nilai >= 0) {
        HM = 'E';
    } else {
        cout << "Nilai tidak valid! (rentang nilai di luar 0-100)";
        HM = '\0';
    }

    return HM;
}

string tentukanKelulusan(Mahasiswa& mhs){
    string kelulusan;
    if (mhs.nilai >= 55 && mhs.nilai <= 100)
    {
        kelulusan = "Lulus";
    } else if (mhs.nilai >= 0) {
        kelulusan = "Tidak Lulus";
    } else {
        cout << "Nilai tidak valid! (rentang nilai di luar 0-100)";
        kelulusan = '\0';
    }

    return kelulusan;
}

void traversal(Queue& Q) {
    if (Q.head == nullptr) {
        cout << "Antrian kosong.\n";
        return;
    }
    PointerMhs current = Q.head;
    cout << "-------------------------------------------------------\n";
    cout << "No\tNPM\tNama\tNilai\tHM\tStatus\n"; // sintaks "\t" itu kaya mencet tab
    cout << "-------------------------------------------------------\n"; //Ini dikira-kira aja, bapaknya kayaknya gak bakal terlalu merhatiin garis interface ini, pak Akmal most definitely lebih merhatiin logika strukdatnya
    int no = 1; //start dari 1 sampai n
    while (current != nullptr) {
        cout << no << "\t" << current->data.NPM << "\t" << current->data.nama
             << "\t" << current->data.nilai << "\t" << tentukanHM(current->data)
             << "\t" << tentukanKelulusan(current->data) << "\n";
        current = current->next;
        no++;
    }
    cout << "-------------------------------------------------------\n";
    cout << "Rata-rata Nilai = " << rataRataNilai(Q) << "\n";
} // Ini fungsi traversal paling minimal, belum ada filter lulus/Tidak lulus
 // ini traversal ada dua, karena disuruh yang biasa juga, tapi sebenernya tampilkanDaftar aja juga udah cukup

void tampilkanDaftar(Queue& Q ,int pilihan) {
    cout << "\nDaftar Nilai Mhs MK Struktur Data 2023\n";

    if (pilihan == 1) cout << "Pilihan : Lulus\n";
    else if (pilihan == 2) cout << "Pilihan : Tidak Lulus\n";
    else cout << "Pilihan : Semua Mahasiswa\n";

    cout << "-------------------------------------------------------\n";
    cout << "No\tNPM\tNama\tNilai\tHM\tStatus\n";
    cout << "-------------------------------------------------------\n";
 
    PointerMhs current = Q.head;
    int no = 1;
    while (current != nullptr) {
        bool tampilkan = false; //ngecek apakah data di node sekarang ditampilkan atau gak tergantung filter
        if (pilihan == 1 && tentukanKelulusan(current->data) == "Lulus") tampilkan = true;
        else if (pilihan == 2 && tentukanKelulusan(current->data) == "Tidak Lulus") tampilkan = true;
        else if (pilihan == 3) tampilkan = true;
 
        if (tampilkan) {
            cout << no << "\t" << current->data.NPM << "\t" << current->data.nama
                 << "\t" << current->data.nilai << "\t" << tentukanHM(current->data)
                 << "\t" << tentukanKelulusan(current->data) << "\n";
            no++;
        }
        current = current->next;
    }
    cout << "-------------------------------------------------------\n";
    cout << "Rata-rata Nilai = " << rataRataNilai(Q) << "\n";
}

int main() {
    Queue Q;
    createList(Q); // inisialisasi antrian
    PointerMhs newPtr;
    // Memasukkan data mahasiswa sesuai tabel pada soal
    newPtr = createElement("250001", "Kanji", 85);
    insertLast(Q, newPtr);
    newPtr = createElement("250002", "Teddy", 75);
    insertLast(Q, newPtr);
    newPtr = createElement("250003", "Rise", 55);
    insertLast(Q, newPtr);
    newPtr = createElement("250004", "John", 45);
    insertLast(Q, newPtr);
    newPtr = createElement("250067", "Person4", 10);
    insertLast(Q, newPtr);
 
    cout << "\n\n------------Isi Queue (Traversal dari Head)-----------\n";
    traversal(Q);
 
    // Menampilkan sesuai pilihan: 1=lulus, 2=tidak lulus, 3=semua
    tampilkanDaftar(Q, 3);   // contoh: tampilkan semua mahasiswa
    tampilkanDaftar(Q, 1);   // contoh: tampilkan yang lulus saja
    tampilkanDaftar(Q, 2);   // contoh: tampilkan yang tidak lulus saja
 
    // Contoh proses keluar antrian (delete dari depan)
    cout << "\n\n---------------Proses dequeue dari Queue---------------\n";
    PointerMhs pHapus;
    deleteFirst(Q, pHapus);
    traversal(Q);
 
    return 0;
}