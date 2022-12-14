#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<unsigned long long, long> mem(1024);

unsigned long long hashKey(vector<int> &vec) {
    unsigned long long key = 0;
    for(int i : vec) {
        key += i;
        key *= 10;
    }
    return key;
}

bool onlyOneByOne(int n, vector<int> &vec) {
    int l = vec[0];
    for(int i = 1; i < n; i++) {
        if(vec[i] >= l && l > 1) return false;
        else {l = vec[i];} 
    }
    return true;
}

long solve(int n, vector<int> &vec) {

    long total = 0;

    long key = hashKey(vec);
    
    if(mem.count(key)) return mem[key];
    
    else if(onlyOneByOne(n, vec)) return 1;
    
    else {
        int col = vec[0];
        int lin = 0;
        int consecutive = 1;
        int i = 1;
        bool next = true;
        while(i < n) {
            while(vec[i] == col && next && i < n) {
                i++; consecutive++;
            }
            if(i == n) break;
            next = false;
            if(vec[i] > col) {
                lin = i;
                col = vec[i];
                consecutive = 1;
                next = true;
            }
            i++;
        }
        if(col > consecutive) col = consecutive;
        while(col > 0) {
            for(int i = lin; i < lin + col; i++) vec[i] -= col;
            total += solve(n, vec);
            for(int i = lin; i < lin + col; i++) vec[i] += col;
            col--;
        }
        mem[key] = total;
    }
    return total;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> vec(n);
    for(int i = 0; i < n; i++) cin >> vec[i];
    if(n == 0 || vec[n-1] == 0) cout << 0 << endl;
    else if(onlyOneByOne(n, vec)) cout << 1 << endl;
    else cout << solve(n, vec) << endl;
    return 0;
}