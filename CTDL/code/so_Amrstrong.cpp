#include <iostream>
#include <string>
#include <math.h>

using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int data) : data(data), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    void insertNode(int data) {
        Node* newNode = new Node(data);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    void printList() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    bool isArmstrong(int n) {
        string str = to_string(n);
        int l = str.length(); 
        int temp = 0, k = n;
        for (int i = 0; i<l; i++) {
            temp += pow(k%10,l);
            k = k/10;
        }
        if (temp == n) return true;
        return false;
    }

    void deleteNode(int offset) {
        Node *temp = head;
        Node *prev = head;
        if (head == NULL) return ;
        if (offset == 1) {
            head = head->next;
            delete temp;
        } else {
            for (int i = 0; i < offset-1; i++) {
                prev = temp;
                temp = temp->next;
            }
            prev->next = temp->next;
            delete temp;
        }
    }

    void delete_Armstrong() {
        Node* temp = head;
        int i = 1;
        while (temp != NULL) {
            if (isArmstrong(temp->data)) {
                deleteNode(i);
            }
            i++;
            temp = temp->next;
        }
    }
};

int main() {
    LinkedList list;
    list.insertNode(10);
    list.insertNode(20);
    list.insertNode(30);
    list.insertNode(153);
    list.insertNode(40);


    cout << "Elements of the list are: ";
    list.printList();

    list.delete_Armstrong();
    list.printList();

    return 0;
}
