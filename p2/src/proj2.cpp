#include <iostream>
#include <vector>

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
    adj[u-1].push_back(make_edge(v-1, w));
    adj[v-1].push_back(make_edge(u-1, w));
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

int solve(vector<Edge> *adj, vector<int> key, int v) {
    vector<int> queue(v, 1);
    for (int i = 0; i < v; i++) {
        int u = extract_max(key, queue, v);
        cout << u << "\n";
        for (Edge j : adj[u]) {
            if (j.w > key[j.v] && queue[j.v] == 1) {
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
    cin >> v >> e;
    vector<int> key(v, 0);
    vector<Edge> adj[v];
    for (int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        addEdge(adj, u, v, w);
    }
    for (int i = 0; i < v; i++) {
        cout << i << "->";
        for (Edge j : adj[i]) {
            cout << "(" << j.v << "," << j.w << ")";
        }
        cout << "\n";
    }
    cout << solve(adj, key, v) << endl;
    return 0;
}