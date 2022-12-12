#include <iostream>
#include <vector>
#include <map>

using namespace std;

map<vector<int>, long> mem;

bool only1x1(int n, vector<int> &area) {
    int l = area[0];
    for(int i = 1; i < n; i++) {
        if(area[i] >= l && l > 1) {return false;}
        else {l = area[i];} 
    }
    return true;
}

long compute(int n, vector<int> &area, int lin, int square) {
    vector<int> copy(n);
    for(int i = 0; i < n; i++) copy[i] = area[i];
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
        copy[i] -= square;
    }

    if(mem.count(copy)) {
        if(square == 1) return mem[copy];
        mem[area] = compute(n, area, lin, square-1);
        return mem[area] + mem[copy];
    }
    if(only1x1(n, copy)) {
        if(square == 1) return 1;
        mem[area] = compute(n, area, lin, square-1);
        return mem[area] + 1;
    }
    if(square == 1) {
        mem[copy] = compute(n, copy, 0, -1);
        return mem[copy];
    }
    mem[area] = compute(n, area, lin, square-1);
    mem[copy] = compute(n, copy, 0, -1);
    return mem[area] + mem[copy];
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> area(n);
    for(int i = 0; i < n; i++) {
        cin >> area[i];
    }
    if(n == 0 || area[n-1] == 0) cout << 0 << endl;
    else if(only1x1(n, area)) cout << 1 << endl;
    else cout << compute(n, area, 0, -1) << endl;
    return 0;
}