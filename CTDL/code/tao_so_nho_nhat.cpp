#include <iostream>
#include <string>
using namespace std;

int sonhonhat(int n) {
    string str = to_string(n);
    bool dk = false;
    for (int i = 0; i < str.length(); i++) {
        if (dk) {
            str[i] = str[i+1];
        } else {
            if (str[i] > str[i+1]) {
                str[i] = str[i+1];
                dk = true;
            }
        }
    }
    n = stoi(str);
    return n;
}

int main () {
    int n = 2198;
    cout<<sonhonhat(n);
    return 0;
}