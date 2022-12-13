#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<long, unsigned long> mem;

bool onlyOneByOne(int n, vector<int> &area) {
    int l = area[0];
    for(int i = 1; i < n; i++) {
        if(area[i] >= l && l > 1) {return false;}
        else {l = area[i];} 
    }
    return true;
}

unsigned long hashKey(vector<int> &vec) {
    unsigned long key = 0;
    for(int i : vec) {
        key += i;
        key *= 10;
    }
    return key;
}

unsigned long solve(int n, vector<int> &area) {
    if(onlyOneByOne(n, area)) return 1;

    unsigned long total = 0;

    unsigned long key = hashKey(area);
    
    if(mem.count(key)) total = mem[key];
    
    else {
        int square;
        int lin = 0;
        int col = area[0]; int consecutive = 1;
        bool previous = (col == area[1]); bool next = false;
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
        while(square > 0) {
            for(int i = lin; i < lin + square; i++) area[i] -= square;
            total += solve(n, area);
            for(int i = lin; i < lin + square; i++) area[i] += square;
            square--;
        }
        mem[key] = total;
    }
    return total;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> area(n);
    for(int i = 0; i < n; i++) cin >> area[i];
    if(n == 0 || area[n-1] == 0) cout << 0 << endl;
    else if(onlyOneByOne(n, area)) cout << 1 << endl;
    else cout << solve(n, area) << endl;
    return 0;
}