#include <iostream>
#include <memory>
#include <utility>

struct Simpul {
    int info;
    std::unique_ptr<Simpul> left;
    std::unique_ptr<Simpul> right;
};

using Pointer = std::unique_ptr<Simpul>;
using Tree = Pointer;

void insertBST(Tree& Root, Pointer& pBaru);

void createSimpul(Pointer& pBaru);

void preOrder(const Simpul* root);

void inOrder(const Simpul* root);

void postOrder(const Simpul* root);

void insertBST(Tree& Root, Pointer& pBaru) {
    if (Root == nullptr) Root = std::move(pBaru);
    else if (pBaru->info < Root->info) insertBST(Root->left, pBaru);
    else if (pBaru->info > Root->info) insertBST(Root->right, pBaru);
    else std::cout << "Sudah ada";
}

void createSimpul(Pointer& pBaru) {
    int value;

    std::cout << "Masukkan satu angka: ";
    std::cin >> value;

    pBaru = std::make_unique<Simpul>();
    pBaru->info = value;
    pBaru->left = nullptr;
    pBaru->right = nullptr;
}

void preOrder(const Simpul* root) {
    if (root != nullptr) {
        std::cout << root->info << " ";
        preOrder(root->left.get());
        preOrder(root->right.get());
    }
}

void inOrder(const Simpul* root) {
    if (root != nullptr) {
        inOrder(root->left.get());
        std::cout << root->info << " ";
        inOrder(root->right.get());
    }
}

void postOrder(const Simpul* root) {
    if (root != nullptr) {
        postOrder(root->left.get());
        postOrder(root->right.get());
        std::cout << root->info << " ";
    }
}

int main() {
    Tree root = nullptr;
    Pointer pBaru = nullptr;

    int pilihan = -1;

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
            insertBST(root, pBaru);
            break;

        case 2:
            std::cout << "\nPre Order:\n";
            preOrder(root.get());
            break;

        case 3:
            std::cout << "\nIn Order:\n";
            inOrder(root.get());
            break;

        case 4:
            std::cout << "\nPost Order:\n";
            postOrder(root.get());
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