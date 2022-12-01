#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> matrix;

void parse_input(int n, int m, vector<int> area, matrix &mat) {
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
    }
}

void initialize_matrix(int n, int m, matrix &mat) {
    for(int i = 0; i < n; i++) {
        vector<int> vec = {};
        for(int j = 0; j < m; j++) {
            vec.push_back(0);
        }
    }
}

int main() {
    int n, m;
    vector<int> area = {};
    matrix mat = {};
    parse_input(n, m, area, mat);
    return 0;
}