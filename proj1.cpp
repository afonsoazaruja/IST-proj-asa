#include <iostream>
#include <vector>
#include <map>

using namespace std;

map<vector<int>, long> mem;

bool only_square_1(int n, vector<int> &area) {
    int l = area[0];
    for(int i = 1; i < n; i++) {
        if(area[i] >= l && l > 1) {return false;}
        else {l = area[i];} 
    }
    return true;
}

long compute(int n, vector<int> &area, int lin, int square) {
    if(square == -1) {
        int col = area[0];
        int consecutive = 1;
        bool previous = (col == area[1]);
        bool next = false;
        for(int i = 1; i < n; i++) {
            int sq = area[i];
            if(next == true) {previous = true; next = false;}
            if((sq == col) && (previous)) consecutive++;
            else if(sq > col) {
                lin = i; 
                col = sq; 
                consecutive = 1; 
                previous = false; 
                next = true;
            }
            else previous = false;
        }
        if(col > consecutive) square = consecutive;
        else square = col;
    }
    
    for(int i = lin; i < lin + square; i++) {
        area[i] -= square;
    }

    if(mem.count(area) == 1) {
        if(square == 1) return mem[area];//altered
        long res = mem[area];
        for(int i = lin; i < lin + square; i++) area[i] += square;
        mem[area] = compute(n, area, lin, square-1); //original
        return mem[area] + res;
    }
    if(only_square_1(n, area)) {
        if(square == 1) return 1;
        for(int i = lin; i < lin + square; i++) area[i] += square;
        mem[area] = compute(n, area, lin, square-1);
        return mem[area] + 1;
    }
    if(square == 1) {
        mem[area] = compute(n, area, 0, -1);
        return mem[area];
    }
    mem[area] = compute(n, area, lin, square-1);
    long res = mem[area];
    for(int i = lin; i < lin + square; i++) area[i] += square;
    mem[area] = compute(n, area, 0, -1);
    return mem[area] + res;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> area(n);
    for(int i = 0; i < n; i++) {
        cin >> area[i];
    }
    if(n == 0 || area[n-1] == 0) cout << 0 << endl;
    else if(only_square_1(n, area)) cout << 1 << endl;
    else cout << compute(n, area, 0, -1) << endl;
    return 0;
}