
#include <iostream>
using namespace std;

struct TreeNode  {
    char data;
    TreeNode* left;
    TreeNode* right;
};

TreeNode* buatNode(char data) {
    TreeNode* node = new TreeNode;
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
    TreeNode* E = buatNode('E');
    TreeNode* C = buatNode('C');
    TreeNode* G = buatNode('G');
    TreeNode* A = buatNode('A');
    TreeNode* D = buatNode('D');
    TreeNode* F = buatNode('F');
    TreeNode* H = buatNode('H');
    TreeNode* B = buatNode('B');
    TreeNode* M = buatNode('M');
    TreeNode* K = buatNode('K');
    TreeNode* L = buatNode('L');
    TreeNode* I = buatNode('I');

    E->left = C; E->right = G;
    C->left = A; C->right = D;
    A->right = B;
    B->left = L;
    G->left = F; G->right = H;
    F->right = M;
    H->right = K;
    K->left = I;

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