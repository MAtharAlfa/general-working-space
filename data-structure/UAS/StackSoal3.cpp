#include <iostream>
using namespace std;

const int maxElement = 100;

//Struct Mahasiswa
struct Mahasiswa{
    string NPM;
    string nama;
    int nilai;
};

struct Stack {
    Mahasiswa info[maxElement];
    int top;
};

void createStack(Stack& stackMhs){
    stackMhs.top = -1;   // -1 artinya stack kosong
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

double rataRataNilai(Stack& stackMhs) {
    double total = 0; 
    int jumlah = 0;
    int idxBantu = stackMhs.top;

    while (idxBantu >= 0)
    {
        total += stackMhs.info[idxBantu].nilai;
        ++jumlah;
        --idxBantu;
    }
    
    return total / jumlah;
}

Mahasiswa createElement(string npm, string nama, int nilai) {
    Mahasiswa element;
    element.NPM = npm;
    element.nama = nama;
    element.nilai = nilai;

    return element;
}

void push(Stack& stackMhs, Mahasiswa& elementBaru) {
    if (stackMhs.top == maxElement - 1)
    {
        cout << "Tumpukan sudah penuh" << "\n"; //fun fact: \n lebih efisien daripada endl kalo buat print kaya gini.
    }
    else
    {
        stackMhs.top = stackMhs.top + 1;
        stackMhs.info[stackMhs.top] = elementBaru;
    }
}

void pop(Stack& stackMhs, Mahasiswa& elementHapus){
    if (stackMhs.top < 0) {
        cout << "Tumpukan sudah kosong " << "\n";
    }
    else 
    {
        elementHapus = stackMhs.info[stackMhs.top];
        stackMhs.top = stackMhs.top - 1;
    }
}

void traversal(Stack& stackMhs) {
    if (stackMhs.top == -1) 
    {
        cout << "Stack kosong.\n";
        return;
    }
    cout << "-------------------------------------------------------\n";
    cout << "No\tNPM\tNama\tNilai\tHM\tStatus\n";
    cout << "-------------------------------------------------------\n";
    int no = 1;
    for (int i = stackMhs.top; i >= 0; --i) {
        cout << no << "\t" << stackMhs.info[i].NPM << "\t" << stackMhs.info[i].nama
             << "\t" << stackMhs.info[i].nilai << "\t" << tentukanHM(stackMhs.info[i])
             << "\t" << tentukanKelulusan(stackMhs.info[i]) << "\n";
        no++;
    }
    cout << "-------------------------------------------------------\n";
    cout << "Rata-rata Nilai = " << rataRataNilai(stackMhs) << "\n";
} // ini traversal ada dua, karena disuruh yang biasa juga, tapi sebenernya tampilkanDaftar aja juga udah cukup

// Tampilkan daftar nilai sesuai pilihan (1=lulus, 2=tidak lulus, 3=semua) 
void tampilkanDaftar(Stack& stackMhs, int pilihan) {
    cout << "\nDaftar Nilai Mhs MK Struktur Data 2023\n";

    if (pilihan == 1) cout << "Pilihan : Lulus\n";
    else if (pilihan == 2) cout << "Pilihan : Tidak Lulus\n";
    else cout << "Pilihan : Semua Mahasiswa\n";

    cout << "-------------------------------------------------------\n";
    cout << "No\tNPM\tNama\tNilai\tHM\tStatus\n";
    cout << "-------------------------------------------------------\n";

    int no = 1;
    for (int i = stackMhs.top; i >= 0; i--) {
        bool tampilkan = false;
        if (pilihan == 1 && tentukanKelulusan(stackMhs.info[i]) == "Lulus") tampilkan = true;
        else if (pilihan == 2 && tentukanKelulusan(stackMhs.info[i]) == "Tidak Lulus") tampilkan = true;
        else if (pilihan == 3) tampilkan = true;

        if (tampilkan) {
            cout << no << "\t" << stackMhs.info[i].NPM << "\t" << stackMhs.info[i].nama
                 << "\t" << stackMhs.info[i].nilai << "\t" << tentukanHM(stackMhs.info[i])
                 << "\t" << tentukanKelulusan(stackMhs.info[i]) << "\n";
            no++;
        }
    }
    cout << "-------------------------------------------------------\n";
    cout << "Rata-rata Nilai = " << rataRataNilai(stackMhs) << "\n";
}

int main() {
    Stack stack;
    createStack(stack);   // inisialisasi stack

    Mahasiswa newElement;
    // Memasukkan data mahasiswa sesuai tabel pada soal
    newElement = createElement("250001", "Kanji", 85);
    push(stack, newElement);
    newElement = createElement("250002", "Teddy", 75);
    push(stack, newElement);
    newElement = createElement("250003", "Rise", 55);
    push(stack, newElement);
    newElement = createElement("250004", "John", 45);
    push(stack, newElement);
    newElement = createElement("250067", "Person4", 10);
    push(stack, newElement);

    cout << "\n\n------------Isi Stack (Traversal dari Top)------------\n";
    traversal(stack);

    // Menampilkan sesuai pilihan: 1=lulus, 2=tidak lulus, 3=semua
    tampilkanDaftar(stack, 3);   // contoh: tampilkan semua mahasiswa
    tampilkanDaftar(stack, 1);   // contoh: tampilkan yang lulus saja
    tampilkanDaftar(stack, 2);   // contoh: tampilkan yang tidak lulus saja

    // Contoh proses pop dari stack
    cout << "\n\n-----------------Proses Pop dari Stack-----------------\n";
    Mahasiswa elementHapus;
    pop(stack, elementHapus);
    traversal(stack);

    return 0;
}