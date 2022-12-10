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

vector<int> find_start(int n, vector<int> &area) {
    vector<int> coord(2);
    coord.at(0) = 0;
    coord.at(1) = area.at(0);
    for(int lin = 1; lin < n; lin++) {
        int value = area.at(lin);
        if(value > coord.at(1)) {coord.at(1) = value; coord.at(0) = lin;}
    }
    return coord;
}

int compute(int n, int m, int square, matrix &mat, vector<int> &area) {
    if(square == 0) return 0;
    vector<int> coord = find_start(n, area);
    matrix aux_mat = copy_matrix(n, m, mat);
    vector<int> aux_area = copy_vector(n, area);
    int lin = coord.at(0);
    int col = coord.at(1) - 1;
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
    bool finished = true;
    for(int i = 0; i < n; i++) {
        if(aux_area.at(i) != 0) finished = false;
    }
    if(finished) {
        //cout << "ENTROU\n"; 
        return 1 + compute(n, m, size-1, mat, area);
        }
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
    return 0;
}