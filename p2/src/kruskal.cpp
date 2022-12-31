#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct {
    int u = 0;
    int v = 0;
    int w = 0;
} Edge;

class DisjSet {
    int *rank, *parent, n;
    
public:
    DisjSet(int n) {
        rank = new int[n];
        parent = new int[n];
        this->n = n;
        makeSet();
    }

    void makeSet() {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unionSet(int x, int y) {
        int xp = find(x);
        int yp = find(y);

        if (rank[xp] > rank[yp]) {
            parent[yp] = xp;
        }
        else {
            parent[xp] = yp;
            if (rank[xp] == rank[yp]) {
                rank[yp] += 1;
            }
        }
    }
};

bool sortDescending(const Edge &a, const Edge &b) {
    return a.w > b.w;
}

int main() {
    ios::sync_with_stdio(false);
    int V, E;
    cin >> V >> E;
    DisjSet obj(V); // O(V)
    vector<Edge> edges(E); // O(E)
    
    int u, v, w;
    for (int i = 0; i < E; i++) { // O(E)
        cin >> u >> v >> w;
        edges[i].u = u-1;
        edges[i].v = v-1;
        edges[i].w = w;
    }
    
    int res = 0;
    sort(edges.begin(), edges.end(), sortDescending); // O(E*logE)
    for (Edge e : edges) { // O(E)
        if (obj.find(e.u) != obj.find(e.v)) { // O(logE)
            obj.unionSet(e.u, e.v);
            res += e.w;
        }
    }
    cout << res << endl;
    return 0;
}