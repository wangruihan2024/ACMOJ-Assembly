#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;
int n, m, s, t;

int main() {
    cin >> n >> m >> s >> t;
    vector<vector<pair<int, long long>>> adj(n + 1);
    for (int i = 1; i <= m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    vector<long long> dist(n + 1, LONG_LONG_MAX);
    dist[s] = 0;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.emplace(0, s);
    while(!pq.empty()) {
        long long current_dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if(current_dist > dist[u])
            continue;
        for(auto [v, w] : adj[u]) {
            if(dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.emplace(dist[v], v);
            }
        }
    }
    cout << dist[t] << endl;
}