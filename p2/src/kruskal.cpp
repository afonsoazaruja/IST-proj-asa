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

    void Union(int x, int y) {
        int xset = find(x);
        int yset = find(y);

        if (rank[xset] > rank[yset]) {
            parent[yset] = xset;
        }
        else {
            parent[xset] = yset;
            if (rank[xset] == rank[yset]) {
                rank[yset] = rank[yset] + 1;
            }
        }
    }
};

bool sortDescending(const Edge &a, const Edge &b) {
    return a.w > b.w;
}

int main() {
    int V, E;
    if (scanf("%d %d", &V, &E) == 0) return 0;
    DisjSet obj(V); // O(V)
    vector<Edge> edges(E); // O(E)
    
    int u, v, w;
    for (int i = 0; i < E; i++) { // O(E)
        if (scanf("%d %d %d", &u, &v, &w) == 0) return 0;
        edges[i].u = u-1;
        edges[i].v = v-1;
        edges[i].w = w;
    }
    
    int res = 0;
    sort(edges.begin(), edges.end(), sortDescending); // O(E*logE)
    for (Edge ed : edges) { // O(E)
        if (obj.find(ed.u) != obj.find(ed.v)) {
            obj.Union(ed.u, ed.v);
            res += ed.w;
        }
    }
    cout << res << endl;
    return 0;
}