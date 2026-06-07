#include <iostream>

struct Simpul {
    int info;
    Simpul* left;
    Simpul* right;
};

typedef Simpul* pointer;
typedef pointer Tree;

void insertBST(Tree& Root, pointer pBaru);

void createSimpul(pointer& pBaru);

void preOrder(Tree Root);

void inOrder(Tree Root);

void postOrder(Tree Root);

void insertBST(Tree& Root, pointer pBaru) {
    if (Root == nullptr) Root = pBaru;
    else if (pBaru->info < Root->info) insertBST(Root->left, pBaru);
    else if (pBaru->info > Root->info) insertBST(Root->right, pBaru);
    else std::cout << "Sudah ada";
}

void createSimpul(pointer& pBaru) {
    pBaru = new Simpul;
    std::cout << "Masukkan satu angka: ";
    std::cin >> pBaru->info;
    pBaru->left = nullptr;
    pBaru->right = nullptr;
}

void preOrder(Tree Root) {
    if (Root != nullptr) {
    std::cout << Root->info << std::endl;
    preOrder(Root->left);
    preOrder(Root->right);
    }
}

void inOrder(Tree Root) {
    if (Root != nullptr) {
        inOrder(Root->left);
        std::cout << Root->info << std::endl;
        inOrder(Root->right);
    }
}

void postOrder(Tree Root) {
    if (Root != nullptr) {
        postOrder(Root->left);
        postOrder(Root->right);
        std::cout << Root->info << std::endl;
    }
}

int main() {
    Tree Root = nullptr;
    pointer pBaru;

    int pilihan;

    do {
        std::cout << "\n=== MENU BST ===\n";
        std::cout << "1. Insert Node\n";
        std::cout << "2. Pre Order\n";
        std::cout << "3. In Order\n";
        std::cout << "4. Post Order\n";
        std::cout << "0. Keluar\n";
        std::cout << "Pilihan : ";
        std::cin >> pilihan;

        switch (pilihan) {
        case 1:
            createSimpul(pBaru);
            insertBST(Root, pBaru);
            break;

        case 2:
            std::cout << "\nPre Order:\n";
            preOrder(Root);
            break;

        case 3:
            std::cout << "\nIn Order:\n";
            inOrder(Root);
            break;

        case 4:
            std::cout << "\nPost Order:\n";
            postOrder(Root);
            break;

        case 0:
            std::cout << "Program selesai.\n";
            break;

        default:
            std::cout << "Pilihan tidak valid!\n";
        }

    } while (pilihan != 0);

    return 0;
}