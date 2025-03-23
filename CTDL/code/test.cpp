#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 500; // Adjust this based on your matrix size

int dd[MAX_N][MAX_N]; // To mark visited cells
int n, m; // Matrix dimensions

void dfs(int a[MAX_N][MAX_N], int i, int j) {
    if (i >= 0 && i < n && j >= 0 && j < m) {
        if (a[i][j] == -1 && dd[i][j] == 0) {
            dd[i][j] = 1;
            dfs(a, i - 1, j);
            dfs(a, i, j + 1);
            dfs(a, i + 1, j);
            dfs(a, i, j - 1);
        }
    }
}

int countConnectedComponents(int a[MAX_N][MAX_N]) {
    int components = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == -1 && dd[i][j] == 0) {
                components++;
                dfs(a, i, j);
            }
        }
    }
    return components;
}

int main() {
    int a[MAX_N][MAX_N]; // Your matrix (nXm) containing 0 and -1
    // Read input for matrix a here...

    // Initialize dd array to zeross
    for (int i = 0; i < MAX_N; ++i) {
        for (int j = 0; j < MAX_N; ++j) {
            dd[i][j] = 0;
        }
    }

    // Call the function to find connected components
    int connectedComponents = countConnectedComponents(a);
    cout << "Number of connected components: " << connectedComponents << endl;

    return 0;
}