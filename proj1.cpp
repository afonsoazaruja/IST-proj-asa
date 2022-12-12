#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

map<vector<int>, long> dp;

bool only_square_1(int n, vector<int> &area) {
    int l = area.at(0);
    for(int i = 1; i < n; i++) {
        if(area.at(i) >= l && l > 1) {return false;}
        else {l = area.at(i);} 
    }
    return true;
}



vector<int> copy_vector(int n, vector<int> &area) {
    vector<int> copy(n);
    for(int i = 0; i < n; i++) {
        copy.at(i) = area.at(i);
    }
    return copy;
}

long compute_vector(int n, vector<int> &area, int lin, int square) {
    cout << "OLA\n";
    if(square == -1) {
        int col = area[0];
        int consecutive = 1;
        bool previous = (col == area.at(1));
        bool next = false;
            for(int i = 1; i < n; i++) {
                int sq = area[i];
                if(next == true) {previous = true; next = false;}
                if((sq == col) && (previous)) consecutive++;
                else if(sq > col) {lin = i; col = sq; consecutive = 1; previous = false; next = true;}
                else previous = false;
            }
        if(col > consecutive) square = consecutive;
        else square = col;
    }
    for(int i = lin; i < lin + square; i++) {
        area[i] -= square;
    }

    if(dp.count(area) == 1) {
        if(square == 1) {return dp[area];}
        else {
            long res = dp[area]; //altered
            for(int i = lin; i < lin + square; i++) {area[i] += square;}
            dp[area] = compute_vector(n, area, lin, square-1); //original
            return dp[area] + res;
        }
    }
    else {
        if(only_square_1(n, area)) { //altered
            if(square == 1) return 1;
            else {
                for(int i = lin; i < lin + square; i++) {area[i] += square;}
                dp[area] = compute_vector(n, area, lin, square-1); //original
                return dp[area] + 1;
            }
        }
        else {
            if(square == 1) {
                dp[area] = compute_vector(n, area, 0, -1); //altered
                return dp[area];
            }
            else {
                dp[area] = compute_vector(n, area, 0, -1); //altered
                long res = dp[area];
                for(int i = lin; i < lin + square; i++) {area[i] += square;}
                dp[area] = compute_vector(n, area, lin, square-1); //original
                cout << "AQUI\n";
                return dp[area] + res;
            }
        }
    }
}

int main() {
    int n, m, k;
    cin >> n >> m;
    vector<int> area(n);
    for(int i = 0; i < n; i++) {
        cin >> k;
        area.at(i) = k;
    }
    if(n == 0 || area.at(n-1) == 0) cout << 0 << "\n";
    else if(only_square_1(n, area)) cout << 1 << "\n";
    else cout << compute_vector(n, area, 0, -1) << "\n";
    return 0;
}