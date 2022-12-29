#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

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

int extract_max(vector<int> key, vector<int> queue) {
    int i = 0;
    for (int j : queue) {
        if (key[j] > i) {
            i = j;
        }
    }
    return i;
}

int solve(vector<Edge> *adj, vector<int> key, vector<int> queue, int v) {
    for (int i = 0; i < v; i++) {
        int u = extract_max(key, queue);
        //cout << u << "\n";
        for (Edge j : adj[u]) {
            if (queue[j.v] >= 0 && j.w > key[j.v]) {
                key[j.v] = j.w;
                queue[j.v] = j.w;
            }
        }
        queue.erase(u); // after checking all edges, remove vertex from queue
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
    if (e == 0) {
        cout << 0 << endl;
        return 0;
    }
    vector<Edge> adj[v];
    vector<int> key(v, 0);
    vector<int> queue(v);
    for (int i = 0; i < v; i++) {
        queue[i] = i;
    }
    for (int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
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