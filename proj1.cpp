#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> matrix;

void initialize_matrix(int n, int m, vector<int> &area, matrix &mat) {
    for(int i = 0; i < n; i++) {
        vector<int> vec(m);
        int l = area.at(i);
        for(int j = 0; j < m; j++) {
            if(j < l) vec.at(j) = 1;
            else {vec.at(j) = 0;}
        }
        mat.at(i) = vec;
    }
}

void print_matrix(int n, int m, matrix &mat) {
    for(vector<int> x : mat) {
        cout << "\n";
        for(int y : x) {
            cout << y;
        }
    }
    cout << "\n";
}

bool only_square_1(int n, vector<int> &area) {
    int l = area.at(0);
    for(int i = 1; i < n; i++) {
        if(area.at(i) >= l && l > 1) {return false;}
        else {l = area.at(i);} 
    }
    return true;
}

matrix copy_matrix(int n, int m, matrix &mat) {
    matrix copy(n);
    for(int i = 0; i < n; i++) {
        vector<int> vec(m);
        for(int j = 0; j<m; j++) {
            vec.at(j) = mat.at(i).at(j);
        }
        copy.at(i) = vec;
    }
    return copy;
}

vector<int> copy_vector(int n, vector<int> &area) {
    vector<int> copy(n);
    for(int i = 0; i < n; i++) {
        copy.at(i) = area.at(i);
    }
    return copy;
}

int compute(int n, int m, int square, matrix &mat, vector<int> &area) {
    if(square == 0) return 0;
    matrix aux_mat = copy_matrix(n, m, mat);
    vector<int> aux_area = copy_vector(n, area);
    int lin = 0;
    int col = area.at(0)-1;
    for(int l = 1; l < n; l++) {
        int value = area.at(l)-1;
        if(value > col) {col = value; lin = l;}
    }
    //cout << "\n" << lin << col << "\n";
    aux_mat.at(lin).at(col) = 0;
    int size = 1;
    for(; (lin + size < n) && (col - size > -1) && (size < square) && (aux_mat.at(lin+size).at(col) != 0); size++) {
        for(int i = lin + size; (i >= lin); i--) {
            aux_mat.at(i).at(col - size) = 0;
        }
        for(int i = col - size; i <= col; i++) {
            aux_mat.at(lin + size).at(i) = 0;
        }
    }
    //print_matrix(n, m, aux_mat);
    for(int i = lin; i < size + lin; i++) {
        aux_area.at(i) = aux_area.at(i) - size;
    }
    if(only_square_1(n, aux_area)) {return 1 + compute(n, m, size-1, mat, area);}
    else return compute(n, m, size-1, mat, area) + compute(n, m, 999, aux_mat, aux_area);
}

int main() {
    int n, m, k;
    cin >> n >> m;
    matrix mat(n);
    vector<int> area(n);
    for(int i = 0; i < n; i++) {
        cin >> k;
        area.at(i) = k;
    }
    initialize_matrix(n, m, area, mat);
    //print_matrix(n, m, mat);
    cout << compute(n, m, 999, mat, area) << "\n";
    //cout << only_square_1(n, area)<< "\n";
    return 0;
}