#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
constexpr int MAXN = 1e5 + 5;
int n, q, dep;
vector<vector<int>> adj, fa;
vector<int> depth;
void dfs(int node, int parent) {
    fa[node][0] = parent;
    for(int i = 1; i <= dep; i++) {
        fa[node][i] = fa[fa[node][i - 1]][i - 1];
    }
    for(int neighbor : adj[node]) {
        if(parent != neighbor) {
            depth[neighbor] = depth[node] + 1;
            dfs(neighbor, node);
        }
    }
}
int getLCA(int u, int v) {
    if(depth[u] < depth[v])
        swap(u, v);
    for(int i = dep; i >= 0; i--) {
        if(depth[fa[u][i]] >= depth[v])
            u = fa[u][i];
    }
    if(u == v)
        return u;
    for(int i = dep; i >= 0; i--) {
        if(fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}
bool ckeck(int u, int v, int w) {
    int LCA = getLCA(u, v);
    if(getLCA(u, w) == w && getLCA(w, v) == LCA)
        return true;
    if(getLCA(v, w) == w && getLCA(w, u) == LCA)
        return true;
    return false;
}
int main() {
    cin >> n >> q;
    adj.resize(n + 1);
    dep = log2(n) + 1;
    fa.resize(n + 1, vector<int>(dep + 1));
    depth.resize(n + 1);
    for(int i = 0; i < n - 1; i ++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 1);
    while(q--) {
        int u, v, w;
        cin >> u >> v >> w;
        bool ans = false;
        if(ckeck(u, v, w) || ckeck(v, w, u) || ckeck(u, w, v))
            ans = true;
        if(ans)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}