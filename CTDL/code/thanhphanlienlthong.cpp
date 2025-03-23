#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int dd[500][500];
int n;

void danhdau (int a[500][500],int i,int j) {
    if (i >= 0 && i < n && j >= 0 && j < n) {
        if (a[i][j] == -1 && dd[i][j] == 0) {
            dd[i][j] = 1;
            danhdau(a,i - 1,j);
            danhdau(a,i,j + 1);
            danhdau(a,i + 1,j);
            danhdau(a,i,j - 1);

        }
    }
}

int dem_tplt(int a[500][500]) {
    int t = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] == -1 && dd[i][j] == 0) {
                t++;
                danhdau(a,i,j);
            }
        }
    }
    return t;
}

int main () {
    int a[500][500];
    ifstream input("D:/PTIT/NAM_2/CTDL/in_tplt.txt");
    if (input.fail()) {
        cout<<"Failed to open this file! ";
        return -1;
    }
    int i = 0;
    while (!input.eof()) {
        string str;
        getline(input, str);
        stringstream ss(str);
        int j = 0;
        while (ss >> str) {
            a[i][j] = stoi(str);
            j++;
        }
        i++;
    }
    n = i;
    input.close();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j< n; j++) {
            cout<<a[i][j]<<" ";
        }
        cout<<"\n";
    }
    int tplt = dem_tplt(a);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j< n; j++) {
            cout<<dd[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<tplt<<"\n";
    return 0;
}