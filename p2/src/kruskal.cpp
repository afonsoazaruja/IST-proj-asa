#include <iostream>
#include <vector>

using namespace std;

typedef struct {
    int u;
    int v;
    int w;
} Edge;

int comparator(Edge p1, Edge p2) {
    return p2.w-p1.w;
}

Edge make_edge(int u, int v, int w) {
    Edge edge = {u, v, w};
    return edge;
}

void make_set(int x, int p[], int rank[]) {
    p[x] = x;
    rank[x] = 0;
}

int find_set(int x, int p[]) {
    if (x != p[x]) {
        p[x] = find_set(p[x], p);
    }
    return p[x];
}

void link(int x, int y, int p[], int rank[]) {
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

void union_set(int x, int y, int p[], int rank[]) {
    link(find_set(x, p), find_set(y, p), p, rank);
}


int solve(vector<Edge> edges, int e, int p[], int rank[]) {
    qsort(edges, e, sizeof(edges[0]), comparator);
    int res = 0;
    for (Edge ed : edges) {
        if (find_set(ed.u, p) != find_set(ed.v, p)) {
            union_set(ed.u, ed.v, p, rank);
            res += ed.w;
        }
    }
    return res;
}


int main() {
    int v, e;
    cin >> v >> e;
    if (e == 0) {
        cout << 0 << endl;
        return 0;
    }
    vector<Edge> edges[e];
    int p[e];
    int rank[e]
    for (int i = 0; i < v; i++) {
        make_set(i);
    }
    int u, v, w;
    for (int i = 0; i < e; i++) {
        cin >> u >> v >> w;
        edges[i] = make_edge(u, v, w);
    }

    /*
    for (int i = 0; i < v; i++) {
        cout << i << "->";
        for (Edge j : adj[i]) {
            cout << "(" << j.v << "," << j.w << ")";
        }
        cout << "\n";
    }
    */
    cout << solve(edges, e) << endl;
    return 0;
}