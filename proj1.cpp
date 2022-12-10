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

int compute_max_area_by_vec(int n, vector<int> &area) {
    int max = 0;
    for(int i = 0; i < n; i++) {
        int square = area.at(i);
        if((square <= n) && (i+square <= n) && (square > max)) max = square;
        else if((square > n) && (n-i == n) && (square > max)) max = n-i;
    }
    return max;
}

matrix copy_matrix(int n, int m, matrix &mat) {
    matrix copy = {};
    for(int i = 0; i<n; i++) {
        vector<int> vec(m);
        for(int j = 0; j<m; j++) {
            vec.push_back(mat.at(i).at(j));
        }
        copy.push_back(vec);
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

void clear_area(matrix &mat, int l, int c, int size) {
    for(int i = l; i < l+size; i++) { 
        for(int j = c; j < c+size; j++) {
            mat.at(i).at(j) = 0;
        }
    }
}

int compute_areas(int n, int m, matrix &mat, int max_size) {
    int big = 0;
    int times = 0;
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < m-1; j++) {
            int size = 0;
            bool valid = true;
            if((mat.at(i).at(j) == 1) && mat.at(i+1).at(j+1) == 1) {
                size++;
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
                            return compute_areas(n, m, aux, max_size) + 1;
                        }
                    }
                }
            }
            if(size > big) {big = size; times = 1;}
            else if(size == big) times++;
        }
    }
    cout << "\nsize:" << big << "\ntimes:" << times;
    if(big < 1) return 1;
    else return compute_areas(n, m, mat, max_size-1) + 1;
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
    int size = 0;
    cout << "\n" << lin << col << "\n";
    for(; (lin + size < n) && (col - size < m) && (size < square); size++) {
        aux_mat.at(lin+size).at(col+size) = 0;
        for(int i = lin + size; (size > 0) && (i - lin > size); i--) {
            aux_mat.at(i).at(col + size) = 0;
        }
        for(int i = col + size; (size > 0) && (i - col > size); i++) {
            aux_mat.at(lin + size).at(i) = 0;
        }
    }
    for(int i = lin; i < size + lin; i++) {
        aux_area.at(i) = aux_area.at(i) - size;
    }
    bool finished = true;
    for(int i = 0; i < n; i++) {
        if(aux_area.at(i) != 0) finished = false;
    }
    if(finished) return 1;
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
    print_matrix(n, m, mat);
    cout << compute(n, m, 999, mat, area) << "\endl";
    return 0;
}