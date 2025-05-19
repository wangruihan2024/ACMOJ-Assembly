#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
constexpr int MOD = 202404;
constexpr int MAXN = 1e6 + 5;
vector<int> tree[MAXN];
int parent[MAXN], depth[MAXN], siz[MAXN], son[MAXN];
int head[MAXN], pos[MAXN], currentPos = 0;
void dfs1(int u, int p) {
    parent[u] = p;
    depth[u] = depth[p] + 1;
    siz[u] = 1;
    son[u] = -1;
    int maxsiz = 0;
    for (int v : tree[u]) {
        if (v != p) {
            dfs1(v, u);
            siz[u] += siz[v];
            if (siz[v] > maxsiz) {
                maxsiz = siz[v];
                son[u] = v;
            }
        }
    }
}
void dfs2(int u, int h) {
    head[u] = h;
    pos[u] = ++currentPos;
    if (son[u] != -1) {
        dfs2(son[u], h);
    }
    for (int v : tree[u]) {
        if (v != parent[u] && v != son[u]) {
            dfs2(v, v);
        }
    }
}
int lca(int u, int v) {
    while (head[u] != head[v]) {
        if (depth[head[u]] > depth[head[v]]) {
            u = parent[head[u]];
        } else {
            v = parent[head[v]];
        }
    }
    return depth[u] < depth[v] ? u : v;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    int l, r, z;
    scanf("%d%d%d", &l, &r, &z);
    long long ans = 0;
    for (int i = l; i <= r; ++i) {
        int ancestor = lca(i, z);
        ans = (ans + depth[ancestor]) % MOD;
    }
    printf("%lld\n", ans);
    return 0;
}