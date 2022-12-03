#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> matrix;

void initialize_matrix(int n, int m, vector<int> &area, matrix &mat) {
    for(int i = 0; i < n; i++) {
        vector<int> vec = {};
        int l = area.at(i);
        for(int j = 0; j < m; j++) {
            if(j < l) vec.push_back(1);
            else {vec.push_back(0);}
        }
        mat.push_back(vec);
    }
}

void print_matrix(int n, int m, matrix &mat) {
    for(vector<int> x : mat) {
        cout << "\n";
        for(int y : x) {
            cout << y;
        }
    }
}

void compute_areas(int n, int m, matrix &mat) {
    int biggest_square = 0;
    for(int i = 0; i < n; i++) {
        int k = 0;
        for(int j = 0; (j < m) && (mat.at(i).at(j) > 0) && (i+j < n); j++) {
            k++;
        }
        if(k > biggest_square) biggest_square = k;
    }
    cout << "\n" << biggest_square;
}






int main() {
    int n, m, k;
    vector<int> area = {};
    matrix mat = {};
 
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> k;
        area.push_back(k);
    }
 
    initialize_matrix(n, m, area, mat);
    print_matrix(n, m, mat);
    compute_areas(n, m, mat);
    return 0;
}