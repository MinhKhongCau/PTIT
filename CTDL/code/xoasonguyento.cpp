#include <iostream>

struct Node {
  int data;
  Node* left;
  Node* right;

  Node(int data) {
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
  }
};

class BinaryTree {
 private:
  Node* root;

 public:
  BinaryTree() {
    root = nullptr;
  }

  // Insert a new node with the given data
  void insert(int data) {
    insertHelper(root, data);
  }

  // Helper function for recursive insertion
  void insertHelper(Node*& node, int data) {
    if (node == nullptr) {
      node = new Node(data);
      return;
    }

    if (data < node->data) {
      insertHelper(node->left, data);
    } else {
      insertHelper(node->right, data);
    }
  }

  // In-order traversal to print the tree elements
  void inOrder() {
    inOrderHelper(root);
  }

  // Helper function for in-order traversal
  void inOrderHelper(Node* node) {
    if (node != nullptr) {
      inOrderHelper(node->left);
      std::cout << node->data << " ";
      inOrderHelper(node->right);
    }
  }
  bool SNT(int n) {
    for (int i = 2; i<n/2; i++) {
        if (n%i == 0) return false;
    }
    return true;
  }
  void DeleteNode(Node *t) {
    if (t->left) {
        Node *temp = t->left;
        while (temp->right)
        {
            temp = temp->right;
        }
        t->data = temp->data;
        delete t;
    } else {
        if (t->right) {
            t->data = t->right->data;
            delete t->right;
        }
        else
            delete t;
    }
  }
  void DeleteSNT() {
    in_traveler(root);
  }
  void in_traveler(Node *temp) {
    if (temp != nullptr) {
        in_traveler(temp->left);
        if (SNT(temp->data)) DeleteNode(temp);
        in_traveler(temp->right);
    }
  }
};

int main() {
  BinaryTree tree;
  tree.insert(50);
  tree.insert(30);
  tree.insert(20);
  tree.insert(41);
  tree.insert(70);
  tree.insert(23);
  tree.insert(80);

  std::cout << "In-order traversal: ";
  tree.inOrder();
  std::cout << std::endl;
  tree.DeleteSNT();
  tree.inOrder();

  return 0;
}
