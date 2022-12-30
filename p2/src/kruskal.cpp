#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct {
    unsigned int u = 0;
    unsigned int v = 0;
    unsigned int w = 0;
} Edge;

bool comparator(const Edge &a, const Edge &b) {
    return a.w > b.w;
}

unsigned int find_set(unsigned int x, unsigned int p[]) {
    if (x != p[x]) {
        p[x] = find_set(p[x], p);
    }
    return p[x];
}

void link(unsigned int x, unsigned int y, unsigned int p[], unsigned int rank[]) {
    if (rank[x] > rank[y]) {
        p[y] = x;
    }
    else {
        p[x] = y;
        if (rank[x] == rank[y]) {
            rank[y] += 1;
        }
    }
}

void union_set(unsigned int x, unsigned int y, unsigned int p[], unsigned int rank[]) {
    link(find_set(x, p), find_set(y, p), p, rank);
}

unsigned int solve(vector<Edge> edges, unsigned int p[], unsigned int rank[], unsigned int v) {
    sort(edges.begin(), edges.end(), comparator);
    for (Edge ed : edges) {
        cout << ed.u << ' ' << ed.v << ' ' << ed.w << "\n"; 
    }
    cout << ".......\n";
    unsigned int res = 0;
    unsigned int stop = 0;
    for (Edge ed : edges) {
        if (find_set(ed.u, p) != find_set(ed.v, p)) {
            cout << ed.u << ' ' << ed.v << ' ' << ed.w << "\n"; 
            union_set(ed.u, ed.v, p, rank);
            res += ed.w;
            if (++stop == v-1) break;
        }
    }
    return res;
}

int main() {
    unsigned int V, E;
    if (scanf("%u %u", &V, &E) == 0) return 0;
    if (E == 0) {
        cout << 0 << endl;
        return 0;
    }
    vector<Edge> edges(E);
    unsigned int u, v, w;
    for (unsigned int i = 0; i < E; i++) {
        if (scanf("%u %u %u", &u, &v, &w) == 0) return 0;
        edges[i].u = u-1;
        edges[i].v = v-1;
        edges[i].w = w;
    }
    unsigned int rank[V] = {0};
    unsigned int p[V];
    for (unsigned int i = 0; i < V; i++) { // make-set
        p[i] = i;
    }
    cout << solve(edges, p, rank, V) << endl;
    return 0;
}