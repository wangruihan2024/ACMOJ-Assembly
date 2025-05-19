#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 5e5 + 5;
struct Edge {
    int u, v, w;
    bool operator<(const Edge& e) const { return w < e.w; }
};
int n, m, q;
vector<Edge> edges;
vector<pair<int, int>> tree[MAXN];
int fa_set[MAXN];
int find_set(int x) { return fa_set[x] == x ? x : fa_set[x] = find_set(fa_set[x]); }
void kruskal() {
    sort(edges.begin(), edges.end());
    for (int i = 1; i <= n; ++i) fa_set[i] = i;
    for (auto &[u, v, w] : edges) {
        int fu = find_set(u), fv = find_set(v);
        if (fu != fv) {
            fa_set[fu] = fv;
            tree[u].emplace_back(v, w);
            tree[v].emplace_back(u, w);
        }
    }
}
int fa[MAXN], dep[MAXN], siz[MAXN], son[MAXN];
int top[MAXN], dfn[MAXN], rnk[MAXN], val[MAXN];
int tclock = 0;
void dfs1(int u, int f) {
    fa[u] = f;
    dep[u] = dep[f] + 1;
    siz[u] = 1;
    for (auto &[v, w] : tree[u]) {
        if (v == f) continue;
        val[v] = w;
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
    }
}
void dfs2(int u, int tp) {
    dfn[u] = ++tclock;
    rnk[tclock] = u;
    top[u] = tp;
    if (son[u]) dfs2(son[u], tp);
    for (auto &[v, _] : tree[u]) {
        if (v != fa[u] && v != son[u]) dfs2(v, v);
    }
}
int seg[MAXN << 2];
void build(int o, int l, int r) {
    if (l == r) {
        seg[o] = val[rnk[l]];
        return;
    }
    int mid = (l + r) / 2;
    build(o << 1, l, mid);
    build(o << 1 | 1, mid + 1, r);
    seg[o] = max(seg[o << 1], seg[o << 1 | 1]);
}
int query(int o, int l, int r, int ql, int qr) {
    if (ql > qr) return 0;
    if (ql <= l && r <= qr) return seg[o];
    int mid = (l + r) / 2, res = 0;
    if (ql <= mid) res = max(res, query(o << 1, l, mid, ql, qr));
    if (qr > mid) res = max(res, query(o << 1 | 1, mid + 1, r, ql, qr));
    return res;
}
int query_path(int x, int y) {
    int res = 0;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        res = max(res, query(1, 1, n, dfn[top[x]], dfn[x]));
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    res = max(res, query(1, 1, n, dfn[x] + 1, dfn[y]));
    return res;
}
int main() {
    cin >> n >> m >> q;
    edges.resize(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    kruskal();
    dfs1(1, 0);
    dfs2(1, 1);
    build(1, 1, n);
    while (q--) {
        int x, y;
        cin >> x >> y;
        cout << query_path(x, y) << endl;
    }
    return 0;
}