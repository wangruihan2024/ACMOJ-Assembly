#include <iostream>
#include <vector>
using namespace std;
constexpr int N = 5e5 + 5;
int n, m;
vector<vector<int>> adj(N); 
int dfn[N], low[N], bcc_cnt;
vector<int> sta;
int cnt;
bool cut[N];
vector<int> dcc[N];
int root;
void tarjan(int u) {
    dfn[u] = low[u] = ++bcc_cnt;
    sta.push_back(u);
    if (u == root && adj[u].empty()) {
        dcc[++cnt].push_back(u);
        return;
    }
    int f = 0;
    for (int v : adj[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                if (++f > 1 || u != root) cut[u] = true;
                cnt++;
                int x;
                do {
                    x = sta.back();
                    sta.pop_back();
                    dcc[cnt].push_back(x);
                } while (x != v);
                dcc[cnt].push_back(u);
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        if (u != v) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            root = i;
            tarjan(i);
        }
    }
    cout << cnt << endl;
    for (int i = 1; i <= cnt; i++) {
        cout << dcc[i].size() << ' ';
        for (int x : dcc[i]) {
            cout << x << ' ';
        }
        cout << endl;
    }
    return 0;
}