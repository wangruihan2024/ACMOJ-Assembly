#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int n, m, s, t;
long long k;
vector<vector<int>> adj;
vector<bool> loop;
vector<long long> dist;
vector<bool> has_loop;
vector<int> color;
vector<bool> is_non_bipartite;

bool is_bipartite(int start) {
    queue<int> q;
    q.push(start);
    color[start] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (color[v] == -1) {
                color[v] = color[u] ^ 1;
                q.push(v);
            } else if (color[v] == color[u]) {
                return false;
            }
        }
    }
    return true;
}
void bfs() {
    dist.assign(n + 1, -1);
    has_loop.assign(n + 1, false);
    queue<int> q;
    dist[s] = 0;
    has_loop[s] = loop[s];
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1 || dist[v] == dist[u] + 1) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    has_loop[v] = has_loop[u] || loop[v];
                    q.push(v);
                } else {
                    has_loop[v] = has_loop[v] || (has_loop[u] || loop[v]);
                }
            }
        }
    }
}

int main() {
    cin >> n >> m >> s >> t >> k;
    adj.resize(n + 1);
    loop.assign(n + 1, false);
    color.assign(n + 1, -1);
    is_non_bipartite.assign(n + 1, false);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        if (u == v) {
            loop[u] = true;
        }
    }
    if (color[t] == -1) {
        is_non_bipartite[t] = !is_bipartite(t);
    }
    bfs();
    if (dist[t] == -1 || dist[t] > k) {
        cout << "No" << endl;
    } else if (dist[t] == k) {
        cout << "Yes" << endl;
    } else {
        if (adj[t].empty()) {
            cout << "No" << endl;
        } else {
            if ((k - dist[t]) % 2 == 0) {
                cout << "Yes" << endl;
            } else {
                if (loop[t] || is_non_bipartite[t]) {
                    cout << "Yes" << endl;
                } else {
                    cout << "No" << endl;
                }
            }
        }
    }
    return 0;
}