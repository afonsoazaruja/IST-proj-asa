#include <iostream>
#include <vector>
#include <map>
#include <bits/stdc++.h>

using namespace std;

typedef struct {
    int v;
    int w;
} Edge;

// Comparator function to sort pairs
// according to second value
bool cmp(pair<int, int>& a, pair<int, int>& b) {
	return a.second > b.second;
}

int sort(map<int, int>& M) {

	// Declare vector of pairs
	vector<pair<int, int>> A;

	// Copy key-value pair from Map
	// to vector of pairs
	for (auto& it : M) {
		A.push_back(it);
	}

	// Sort using comparator function
	sort(A.begin(), A.end(), cmp);
    for (auto& it : A) {
        cout << it.first << ' ' << it.second << endl;
    }
    cout << "---\n";
    return A[0].first;
}

Edge make_edge(int x, int y) {
    Edge edge = {x, y};
    return edge;
}

void addEdge(vector<Edge> *adj, int u, int v, int w) {
    adj[u-1].push_back(make_edge(v-1, w));
    adj[v-1].push_back(make_edge(u-1, w));
}

int extract_max(map<int, int> &queue) {
    return queue[0];
}

int solve(vector<Edge> *adj, vector<int> key, map<int, int> &queue, int v) {
    for (int i = 0; i < v; i++) {
        int u = sort(queue);
        cout << u << "\n";
        for (Edge j : adj[u]) {
            if (queue.count(j.v) > 0 && j.w > key[j.v]) {
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
    vector<Edge> adj[v];
    vector<int> key(v, 0);
    map<int, int> queue;
    for (int i = 0; i < v; i++) {
        queue[i] = 0;
    }
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
    cout << solve(adj, key, queue, v) << endl;
    return 0;
}