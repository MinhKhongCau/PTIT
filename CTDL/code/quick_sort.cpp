#include <iostream>
using namespace std;

void quick_sort(int a[], int left, int right) {
    int pivot = left, L = left, R = right;
    while (L <= R) {
        while (a[L] < a[pivot] && L < right) L++;
        while (a[R] > a[pivot] && R > left) R--;
        if (L <= R) {
            if ( L < R ) {
                int temp = a[L];
                a[L] = a[R];
                a[R] = temp;
            }
            L++;
            R--;
        }
    }
    if (left < R) quick_sort(a,left,R);
    if (right > L) quick_sort(a,L,right);
}

int main() {
    // nhap dau vao
    int a[100];
    int n;
    cin>>n;
    for (int i = 0; i < n; i++) {
        cin>>a[i];
    }
    quick_sort(a,0,n-1);
    for (int i = 0; i<n; i++){
        cout<<a[i] <<" ";
    }
    return 0;
}
// 9
// 40 20 10 80 60 50 7 30 100