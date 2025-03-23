#include <iostream>
using namespace std;

int dem (int a[],int n, int b[], int m) {
    int ind1 = 0, ind2 = 0;
    int sum = m+n;
    while (sum--) {
        if (a[ind1] < b[ind2] && ind1 < n && ind2 < m) {
            ind1++;
        } else {
            ind2++;
            cout<<ind1<<" ";
        }
    }
}

int main() {
    int a[6] = {1,6,9,13,18,18};
    int b[7] = {2,3,8,13,15,21,25};
    dem(a,6,b,7);
    return 0;
}