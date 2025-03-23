#include <iostream>
using namespace std;

bool songuyento(int n) {
    int temp = n/2;
    for (int i = 2; i<=n/2; i++) {
        if (n%i == 0) return false;
    }
    return true;
}

int tachso(int n) {
    int a = n/2, b = n/2 + n%2;
    while (!songuyento(a) || !songuyento(b)) {
        a--;
        b++;
    }
    
    return a;
}

int main(){
    int n = 100;
    cout<<tachso(n)<<" " <<n-tachso(n);
    return 0;
}