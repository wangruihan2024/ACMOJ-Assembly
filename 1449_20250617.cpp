#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>
using namespace std;
constexpr int MAXN = 205;
int n, m;
long long int capacity[MAXN][MAXN];
long long int flow[MAXN][MAXN];
int parent[MAXN];

int bfs(int s, int t) {
    fill(parent, parent + n + 1, -1);
    parent[s] = s;
    queue<pair<int, long long int>> q;
    q.push({s, LONG_MAX});
    while(!q.empty()) {
        int u = q.front().first;
        long long int f = q.front().second;
        q.pop();
        for(int v = 1; v <= n; v++) {
            if(parent[v] == -1 && capacity[u][v] > flow[u][v]) {
                parent[v] = u;
                long long int new_flow = min(f, capacity[u][v] - flow[u][v]);
                if(v == t)
                    return new_flow;
                q.push({v, new_flow});
            }
        }
    }
    return 0;
}

long long int karp(int s, int t) {
    long long int max_flow = 0;
    long long int new_flow;
    while((new_flow = bfs(s, t)) > 0) {
        int cur = t;
        while(cur != s) {
            int prev = parent[cur];
            flow[prev][cur] += new_flow;
            flow[cur][prev] -= new_flow;
            cur = prev;
        }
        max_flow += new_flow;
    }
    return max_flow;
}
int main() {
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        capacity[u][v] += c;
    }
    cout << karp(1, n) << endl;
    return 0;
}
