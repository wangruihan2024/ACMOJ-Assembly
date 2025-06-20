#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;
const int MAXN = 1005;
vector<int> adj[MAXN];
int color[MAXN];
int p[MAXN]; 
bool used[MAXN];
bool vis_left[MAXN], vis_right[MAXN];
vector<int> left_nodes, right_nodes;
void dfs_color(int u, int c) {
    color[u] = c;
    if (c == 0) {
        left_nodes.push_back(u);
    } else {
        right_nodes.push_back(u);
    }
    for (int v : adj[u])
        if (color[v] == -1)
            dfs_color(v, 1 - c);
}
bool dfs_match(int u) {
    for (int v : adj[u]) {
        if (!used[v]) {
            used[v] = true;
            if (p[v] == -1 || dfs_match(p[v])) {
                p[v] = u;
                return true;
            }
        }
    }
    return false;
}
void dfs_mark(int u, vector<int>& match_to) {
    vis_left[u] = true;
    for (int v : adj[u]) {
        if (!vis_right[v] && match_to[v] != u) {
            vis_right[v] = true;
            if (p[v] != -1 && !vis_left[p[v]]) {
                dfs_mark(p[v], match_to);
            }
        }
    }
}
int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    memset(color, -1, sizeof(color));
    for (int u = 1; u <= n; ++u) {
        if (color[u] == -1) {
            dfs_color(u, 0);
        }
    }
    memset(p, -1, sizeof(p));
    for (int u : left_nodes) {
        memset(used, false, sizeof(used));
        dfs_match(u);
    }
    vector<int> match_to(n + 1, -1);
    for (int v : right_nodes) {
        if (p[v] != -1) {
            match_to[p[v]] = v;
        }
    }
    memset(vis_left, false, sizeof(vis_left));
    memset(vis_right, false, sizeof(vis_right));
    for (int u : left_nodes) {
        bool is_matched = false;
        for (int v : right_nodes) {
            if (p[v] == u) {
                is_matched = true;
                break;
            }
        }
        if (!is_matched && !vis_left[u]) {
            dfs_mark(u, match_to);
        }
    }
    vector<int> independent_set;
    for (int u : right_nodes) {
        if (!vis_right[u]) {
            independent_set.push_back(u);
        }
    }
    for (int v : left_nodes) {
        if (vis_left[v]) {
            independent_set.push_back(v);
        }
    }
    cout << independent_set.size() << endl;
    for (int u : independent_set) {
        cout << u << " ";
    }
    cout << endl;
    return 0;
}