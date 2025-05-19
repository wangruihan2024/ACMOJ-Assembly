#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
constexpr int MAXN = 100010;
int n, q, r, a, b, z;
int w[MAXN];
int cur, h[MAXN], nxt[MAXN * 2], p[MAXN * 2];
int siz[MAXN], top[MAXN], son[MAXN], dep[MAXN], fa[MAXN], dfn[MAXN], rnk[MAXN], cnt;
int in[MAXN], out[MAXN], time_stamp;
void add_edge(int x, int y) {
    cur++;
    nxt[cur] = h[x];
    h[x] = cur;
    p[cur] = y;
}
struct SegTree {
    long long sum[MAXN * 4], lazy[MAXN * 4];
    void push_up(int o) {
        sum[o] = sum[o << 1] + sum[o << 1 | 1];
    }
    void push_down(int o, int l, int r) {
        if (lazy[o]) {
            int mid = (l + r) >> 1;
            sum[o << 1] += lazy[o] * (mid - l + 1);
            sum[o << 1 | 1] += lazy[o] * (r - mid);
            lazy[o << 1] += lazy[o];
            lazy[o << 1 | 1] += lazy[o];
            lazy[o] = 0;
        }
    }
    void build(int o, int l, int r) {
        lazy[o] = 0;
        if (l == r) {
            sum[o] = w[rnk[l]];
            return;
        }
        int mid = (l + r) >> 1;
        build(o << 1, l, mid);
        build(o << 1 | 1, mid + 1, r);
        push_up(o);
    }
    void update_range(int o, int l, int r, int ql, int qr, int val) {
        if (ql <= l && r <= qr) {
            sum[o] += val * (r - l + 1LL);
            lazy[o] += val;
            return;
        }
        push_down(o, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) update_range(o << 1, l, mid, ql, qr, val);
        if (qr > mid) update_range(o << 1 | 1, mid + 1, r, ql, qr, val);
        push_up(o);
    }
    long long query_range(int o, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return sum[o];
        push_down(o, l, r);
        int mid = (l + r) >> 1;
        long long res = 0;
        if (ql <= mid) res += query_range(o << 1, l, mid, ql, qr);
        if (qr > mid) res += query_range(o << 1 | 1, mid + 1, r, ql, qr);
        return res;
    }
} st;
void dfs1(int o, int father) {
    son[o] = -1;
    siz[o] = 1;
    fa[o] = father;
    dep[o] = dep[father] + 1;
    for (int j = h[o]; j; j = nxt[j]) {
        if (p[j] == father) continue;
        dfs1(p[j], o);
        siz[o] += siz[p[j]];
        if (son[o] == -1 || siz[p[j]] > siz[son[o]]) {
            son[o] = p[j];
        }
    }
}
void dfs2(int o, int t) {
    top[o] = t;
    cnt++;
    dfn[o] = cnt;
    rnk[cnt] = o;
    in[o] = ++time_stamp;
    if (son[o] == -1) {
        out[o] = time_stamp;
        return;
    }
    dfs2(son[o], t);
    for (int j = h[o]; j; j = nxt[j]) {
        if (p[j] != son[o] && p[j] != fa[o]) {
            dfs2(p[j], p[j]);
        }
    }
    out[o] = time_stamp;
}
void update_path(int x, int y, int z) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        st.update_range(1, 1, n, dfn[top[x]], dfn[x], z);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    st.update_range(1, 1, n, dfn[x], dfn[y], z);
}
long long query_path(int x, int y) {
    long long res = 0;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        res += st.query_range(1, 1, n, dfn[top[x]], dfn[x]);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    res += st.query_range(1, 1, n, dfn[x], dfn[y]);
    return res;
}
void update_subtree(int x, int z) {
    st.update_range(1, 1, n, in[x], out[x], z);
}
long long query_subtree(int x) {
    return st.query_range(1, 1, n, in[x], out[x]);
}
int main() {
    cin >> n >> q >> r;
    for (int i = 1; i <= n; i++) cin >> w[i];
    for (int i = 1; i < n; i++) {
        cin >> a >> b;
        add_edge(a, b);
        add_edge(b, a);
    }
    dfs1(r, 0);
    dfs2(r, r);
    st.build(1, 1, n);
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            cin >> a >> b >> z;
            update_path(a, b, z);
        } else if (op == 2) {
            cin >> a >> b;
            cout << query_path(a, b) << endl;
        } else if (op == 3) {
            cin >> a >> z;
            update_subtree(a, z);
        } else if (op == 4) {
            cin >> a;
            cout << query_subtree(a) << endl;
        }
    }
    
    return 0;
}