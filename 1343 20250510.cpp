#include <iostream>
#include <climits>
#include <deque>
#include <vector>
using namespace std;
int n, m, s, t;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> s >>t;
    vector<vector<pair<int, int>>> adj(n + 1);
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    vector<int> dist(n + 1, INT_MAX);
    dist[s] = 0;
    deque<int> dq;
    dq.push_front(s);
    while(!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        if(u == t)
            break;
        for(auto [v, w] : adj[u]) {
            if(dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if(w)
                    dq.push_back(v);
                else
                    dq.push_front(v);
            }
        }
    }
    cout << dist[t] << endl;
}