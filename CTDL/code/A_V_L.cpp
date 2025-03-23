#include <iostream>
using namespace std;

#define RNE -2
#define LNE 2
#define EH 0
#define RH -1
#define LH 1

struct Node {
    int key;
    Node* left;
    Node* right;
    int BalFactor;
};

void Init(Node **root) {
    (*root)->BalFactor = 0;
    (*root)->key = 0;
    (*root)->left = NULL;
    (*root)->right = NULL;
}

int InsertNode(Node **root, int key) {
    if ((*root) == NULL) {
        Node *T = new Node();
        if (T) {
            cout<<"Create node fail";
            return;
        }
        T->BalFactor = 1;
        T->key = key;
        T->left = NULL;
        T->right = NULL; 
    } else {
        int res;
        if ((*root)->key == key) return;
        if (key < (*root)->key) {
            res = InsertNode(&(*root)->left,key);
            
        }
    }
}

int main() {
    return 0;
}