/*  Nama program    :   Soal 1 Doubly List Circular
    Nama            :   Muhammad Athar Alfarisi
    NPM             :   140810250005
    Tanggal buat    :   22 Juni 2026
    Deskripsi       :   Program doubly list circular dengan fungsi insertLast dan traversal
*/

#include <iostream>
using namespace std;

struct Node {
    char info;
    Node* next;
    Node* prev;
};

typedef Node* Pointer;

typedef Pointer DoublyListCircular; 

void createList(DoublyListCircular& head){
    head = nullptr;
}

void createElement(Pointer& newElement, char info){
    newElement = new Node;
    newElement->info = info;
    newElement->next = nullptr;
    newElement->prev = nullptr;                          
}

void insertLast(DoublyListCircular& head, Pointer pNew){
    if (head == nullptr)
    {
        head = pNew;
        head->next = head;
        head->prev = head;
    } else 
    {
        head->prev->next = pNew;
        pNew->next = head;
        head->prev = pNew;
        pNew->prev = head->prev;
    }
}

void traversal(DoublyListCircular head){
    if (head == nullptr) {
        cout << "List kosong" << endl;
    } else {
        Pointer pTraverse = head;
        do
        {
            cout << pTraverse->info << " ";
            pTraverse = pTraverse->next;
        } while (pTraverse != head);
        cout << endl;
    }
}

void menu(DoublyListCircular& head){
    int choice;
    char info;
    Pointer newElement;

    do
    {
        cout << "\n===== MENU =====" << endl;
        cout << "1. Insert Last" << endl;
        cout << "2. Traversal" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Input info (char): ";
            cin >> info;
            createElement(newElement, info);
            insertLast(head, newElement);
            cout << "Element dimasukan." << endl;
            break;
        case 2:
            cout << "Hasil traversal: ";
            traversal(head);
            break;
        case 0:
            cout << "Keluar program." << endl;
            break;
        default:
            cout << "Pilihan tidak valid." << endl;
            break;
        }
    } while (choice != 0);
}

int main(){
    DoublyListCircular head;
    Pointer newElement;

    createList(head);

    menu(head);

    return 0;
}