#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

typedef struct {
    int v;
    int w;
} Edge;

Edge make_edge(int x, int y) {
    Edge edge = {x, y};
    return edge;
}

void addEdge(vector<Edge> *adj, int u, int v, int w) {
    adj[u].push_back(make_edge(v, w));
    adj[v].push_back(make_edge(u, w));
}

int extract_max(vector<int> key, vector<int> queue, int v) {
    int max = 0;
    int i = 0;
    for (; i < v; i++) {
        if (queue[i] != 0) {
            max = i;
            break;
        }
    }
    for (; i < v; i++) {
        if (queue[i] != 0 && key[i] > key[max]) {
            max = i; 
        }
    }
    return max;
}

int solve(vector<Edge> *adj, vector<int> key, unordered_map<int, int> queue, int v) {
    for (int i = 0; i < v; i++) {
        int u = extract_max(key, queue, v);
        // cout << u << "\n";
        for (Edge j : adj[u]) {
            if (queue[j.v] == 1 && j.w > key[j.v]) {
                key[j.v] = j.w;
            }
        }
        queue[u] = 0; // after checking all edges, remove vertex from queue
    }
    int res = 0;
    for(int i = 0; i < v; i++) {
        res += key[i];
    }
    return res;
}

int main() {
    int v, e;
    if (scanf("%d %d", &v, &e) == 0) return 0;
    if (e == 0) {
        cout << 0 << endl;
        return 0;
    }
    unordered_map<int, int> queue;
    for(int i = 0; i < v; i++) {
        queue[i] = 0;
    }
    vector<int> key(v, 0);
    vector<Edge> adj[v];
    for (int i = 0; i < e; i++) {
        int u, v, w;
        if (scanf("%d %d %d", &u, &v, &w) == 0) return 0;
        addEdge(adj, u-1, v-1, w);
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
    cout << solve(adj, key, queue, v) << endl;
    return 0;
}