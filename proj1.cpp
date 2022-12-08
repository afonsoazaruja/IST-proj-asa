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

int compute_max_area_by_vec(int n, vector<int> area) {
    int max = 0;
    for(int i = 0; i < n; i++) {
        int square = area.at(i);
        if((square <= n) && (i+square <= n) && (square > max)) max = square;
    }
    return max;
}

matrix copy_matrix(int n, int m, matrix &mat) {
    matrix copy = {};
    for(int i = 0; i<n; i++) {
        vector<int> vec = {};
        for(int j = 0; j<m; j++) {
            vec.push_back(mat.at(i).at(j));
        }
        copy.push_back(vec);
    }
    return copy;
}

void clear_area(matrix &mat, int l, int c, int size) {
    for(int i = l; i < l+size-1; i++) { 
        for(int j = c; j < c+size-1; j++) {
            mat.at(i).at(j) = 0;
        }
    }
}

int compute_max_by_matrix(int n, int m, matrix &mat, int max_size) {
    int big = 0;
    int times = 0;
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < m-1; j++) {
            int size = 1;
            bool valid = true;
            if((mat.at(i).at(j) == 1) && mat.at(i+1).at(j+1) == 1) {
                for(int iter = 1; (i+iter < n) && (j+iter < m) && (valid == true); iter++) {
                    for(int k = i+iter; k >= i; k--) {
                        if(mat.at(k).at(j+iter) == 0) {valid = false;}
                    }
                    for(int l = j+iter; l >= j; l--) {
                        if(mat.at(i+iter).at(l) == 0) {valid = false;}
                    }
                    if(valid) {
                        size++;
                        if(size == max_size) {
                            matrix aux = copy_matrix(n, m, mat);
                            clear_area(aux, i, j, size);
                            print_matrix(n, m, aux);
                            return compute_max_by_matrix(n, m, aux, max_size) + 1;
                        }
                    }
                }
            }
            if(size > big) {big = size; times = 1;}
            else if(size == big) times++;
        }
    }
    //cout << "\nsize:" << big << "\ntimes:" << times;
    if(max_size < 1) return 0;
    else return compute_max_by_matrix(n, m, mat, max_size-1) + 1;
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
    int initial_max = compute_max_area_by_vec(n, area);
    int ways = compute_max_by_matrix(n, m, mat, initial_max);
    cout << "\nPossibilidades: " << ways; 
    return 0;
}