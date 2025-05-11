#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;
constexpr int MAXN = 3e4 + 5;
int n, m;
vector<int> adj[MAXN];
int dfn[MAXN], low[MAXN];
bool in_stack[MAXN];
int stamp = 0, sc = 0; // sc是强连通分量的个数
vector<int> scc_id;
vector<vector<int>> sccs;
stack<int> stk;
void tarjan(int u) {
    dfn[u] = low[u] = ++stamp;
    stk.push(u);
    in_stack[u] = true;
    for (int v : adj[u]) {
        if (!dfn[v]) { 
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (in_stack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]) {
        ++sc;
        vector<int> component;
        int x;
        do {
            x = stk.top();
            stk.pop();
            in_stack[x] = false;
            scc_id[x] = sc;
            component.push_back(x);
        } while (x != u);
        sccs.push_back(component);
    }
}
int main() {
    cin >> n >> m;
    scc_id.resize(n + 1);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }
    vector<vector<int>> scc_adj(sc + 1);
    vector<int> degree(sc + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int e : adj[i]) {
            if (scc_id[e] != scc_id[i]) {
                scc_adj[scc_id[i]].push_back(scc_id[e]);
            }
        }
    }
    for (int i = 1; i <= sc; i++) {
        sort(scc_adj[i].begin(), scc_adj[i].end());
        scc_adj[i].erase(unique(scc_adj[i].begin(), scc_adj[i].end()), scc_adj[i].end());
        degree[i] = scc_adj[i].size();
    }
    int zero_count = 0;
    int result = -1;
    for (int i = 1; i <= sc; i++) {
        if (degree[i] == 0) {
            zero_count++;
            result = i;
        }
    }
    if (zero_count == 1) {
        cout << sccs[result - 1].size() << endl; 
    } else {
        cout << 0 << endl;
    }
    return 0;
}