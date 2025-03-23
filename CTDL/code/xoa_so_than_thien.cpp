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

    int ucln(int n, int m) {
        if (n == m) return n;
        else if (n > m) {
            n = n - m;
        } else {
            m = m - n;
        }
        return ucln(n,m);
    }

    bool isNknumfre(int n) {
        //dao so
        int temp = n, dao = 0;
        while (temp != 0) {
            dao += temp%10;
            temp /= 10;
            if (temp != 0)
                dao *= 10;
        }
        //tim ucln
        if (ucln(n,dao) == 1) {
            return true;
        }
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

    void deletenumfre() {
        int i = 1;
        Node *temp = head;
        while (temp != NULL) {
            if (isNknumfre(temp->data)) {
                deleteNode(i);
                i--;
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
    list.insertNode(34);
    list.insertNode(31);
    list.insertNode(71);
    list.insertNode(40);



    cout << "Elements of the list are: ";
    list.printList();

    list.deletenumfre();
    list.printList();

    return 0;
}
