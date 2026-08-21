/*  Nama program    :   Soal 2.A & 2.B Tree Node Traversal
    Nama            :   Muhammad Athar Alfarisi
    NPM             :   140810250005
    Tanggal buat    :   22 Juni 2026
    Deskripsi       :   Program Tree Node dengan fungsi traversal
*/

#include <iostream>
using namespace std;

struct TreeNode  {
    char data;
    TreeNode* left;
    TreeNode* right;
};

typedef TreeNode* Pointer;
typedef Pointer Tree;

Pointer buatNode(char data) {
    Pointer node = new TreeNode;
    node->data = data;
    node->left = nullptr;
    node->right = nullptr;

    return node;
}

void preOrder(TreeNode* root) { // V L R
    if (root == nullptr) {
        return;
    }
    cout << root->data << " "; //v
    preOrder(root->left); //L
    preOrder(root->right); //R
}

void inOrder(TreeNode* root) { // L V R
    if (root == nullptr) {
        return;
    }
    inOrder(root->left); //L 
    cout << root->data << " "; //V
    inOrder(root->right); //R
}

void postOrder(TreeNode* root) { //L R V
    if (root == nullptr) {
        return;
    }
    postOrder(root->left); //L
    postOrder(root->right); //R
    cout << root->data << " "; //V
}



int main () {
    Pointer E = buatNode('E');
    Pointer C = buatNode('C');
    Pointer G = buatNode('G');
    Pointer A = buatNode('A');
    Pointer D = buatNode('D');
    Pointer F = buatNode('F');
    Pointer H = buatNode('H');
    Pointer B = buatNode('B');
    Pointer J = buatNode('J');
    Pointer M = buatNode('M');
    Pointer K = buatNode('K');
    Pointer L = buatNode('L');
    Pointer I = buatNode('I');

    E->left = C; E->right = G;
    C->left = A; C->right = D;
    A->right = B;
    B->left = L;
    D->right = J;
    J->right = I;
    G->left = F; G->right = H;
    F->right = M;
    H->right = K;

    cout << "Hasil preOrder: ";
    preOrder(E);
    cout << "\n";
    cout << "Hasil inOrder: ";
    inOrder(E);
    cout << "\n";
    cout << "Hasil PostOrder: ";
    postOrder(E);
    cout << "\n";
    
    return 0;
}