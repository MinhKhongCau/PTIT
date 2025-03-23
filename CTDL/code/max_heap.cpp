#include <iostream>
using namespace std;

struct maxHeap {
    int *array;
    int qfront;
    int qRear;
    int qMax;
};

void InitQueue(maxHeap &h) {
    h.array = new int ();
    h.qfront = 0;
    h.qRear = 0;
    h.qMax = 0;
}

void heapify1(maxHeap &h, int offset) {
    if (offset != 1) {
        if (h.array[offset] > h.array[offset/2]) {
            int temp = h.array[offset];
            h.array[offset] = h.array[offset/2];
            h.array[offset/2] = temp;
            heapify1(h,offset/2);
        }
    }
}

void enPqueue(maxHeap &h, int k) {
    if (h.qfront == 0) h.qfront = 1;
    h.qRear++;
    h.array[h.qRear] = k;
    h.qMax++;
    heapify1(h,h.qRear);
}

void heapify2(maxHeap &h, int offset) {
    if (offset < h.qMax) {
        int max = h.array[offset];
        int toffset = offset;
        if (max < h.array[offset*2])  {
            max = h.array[offset*2];
            toffset = offset*2;
        }
        if (max < h.array[offset*2+1]) {
            max = h.array[offset*2+1];
            toffset = offset*2+1;
        } 
        if (toffset != offset) {
            int temp = h.array[offset];
            h.array[offset] = h.array[toffset];
            h.array[toffset] = temp;
            heapify2(h,toffset);
        }
    }
}

void dePqueue(maxHeap &h) {
    h.array[h.qfront] = h.array[h.qRear];
    h.qRear--;
    h.qMax--;
    heapify2(h,1);
}

void printqueue(maxHeap h) {
    for (int i = 1; i <= h.qMax; i++) {
        cout<<h.array[i]<<" ";
    }
    cout<<endl;
}

int main() {
    maxHeap h;
    InitQueue(h);
    enPqueue(h,37);
    enPqueue(h,3);
    enPqueue(h,15);
    enPqueue(h,22);
    enPqueue(h,7);
    enPqueue(h,9);
    printqueue(h);
    dePqueue(h);
    printqueue(h);
    return 0;
}