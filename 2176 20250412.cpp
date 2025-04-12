#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int n, q, dep;
vector<vector<int>> adj;
vector<long long> weight;
vector<int> parent;
vector<int> depth;
vector<vector<int>> fa;
vector<long long> subtreeTag;
vector<long long> routeTag;
void dfs(int now, int father) {
    parent[now] = father;
    depth[now] = depth[father] + 1;
    fa[now][0] = father;
    for (int i = 1; i <= dep; i++)
        fa[now][i] = fa[fa[now][i - 1]][i - 1];
    for (int neighbor : adj[now]) {
        if(neighbor != father) {
            dfs(neighbor, now);
        }
    }
}
int getLCA(int u, int v) {
    if(depth[u] < depth[v])
        swap(u, v);
    for (int i = dep; i >= 0; i--) {
        if(depth[fa[u][i]] >= depth[v])
            u = fa[u][i];
    }
    if(u == v)
        return u;
    for (int i = dep; i >= 0; i--) {
        if(fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}
void route(int u, int v, int c) {
    routeTag[u] += c;
    routeTag[v] += c;
    routeTag[getLCA(u, v)] -= c;
    if(parent[getLCA(u, v)] != 0)
        routeTag[parent[getLCA(u, v)]] -= c;
}
void subtree(int u, int c) {
    subtreeTag[u] += c;
}
void updatesubtree(int now, int father, long long current) {
    current += subtreeTag[now];
    weight[now] += current;
    for(int neighbor : adj[now]) {
        if(neighbor != father) {
            updatesubtree(neighbor, now, current);
        }
        
    }
}
void updateroute(int now, int father) {
    for(int neighbor : adj[now]) {
        if(neighbor != father) {
            updateroute(neighbor, now);
            routeTag[now] += routeTag[neighbor];
        }
    }
    weight[now] += routeTag[now];
}
int main() {
    cin >> n >> q;
    adj.resize(n + 1);
    weight.resize(n + 1, 0);
    parent.resize(n + 1, 0);
    depth.resize(n + 1, 0);
    fa.resize(n + 1, vector<int>(20));
    subtreeTag.resize(n + 1, 0);
    routeTag.resize(n + 1, 0);
    dep = log2(n) + 1;
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0);
    int type, u, v, c;
    while(q--) {
        cin >> type;
        if(type == 1) {
            cin >> u >> v >> c;
            route(u, v, c);
        }else {
            cin >> u >> c;
            subtree(u, c);
        }
    }
    updatesubtree(1, 0, 0);
    updateroute(1, 0);
    for (int i = 1; i <= n; i++) {
        cout << weight[i] << " ";
    }
    cout << endl;
    return 0;
}