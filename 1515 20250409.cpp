#include <iostream>
#include <cmath>
using namespace std;
constexpr int MAXN = 1e5 + 5;
constexpr int MAXE = 2e5 + 5;
int n;
int idx = 0, dep;
int head[MAXN];
int depth[MAXN], fat[MAXN][20];
long long value[MAXN]; // 从根节点到这个点的得分之和
struct Edge {
    int to;
    int nxt;
    int weight;
} edge[MAXE];
void init() {
    fill(head, head + MAXN, -1);
    dep = log2(n) + 1;
    fill(depth, depth + MAXN, 0);
    fill(value, value + MAXN, 0);
}
void add(int u, int v, int w) {
    edge[idx].to = v;
    edge[idx].weight = w;
    edge[idx].nxt = head[u];
    head[u] = idx++;
}
void dfs(int now, int fa) {
    depth[now] = depth[fa] + 1;
    fat[now][0] = fa;
    // value[now] = value[fa] + edge[fa].weight;
    for(int l = 1; l <= dep; l++)
        fat[now][l] = fat[fat[now][l - 1]][l - 1];
    for (int l = head[now]; l != -1; l = edge[l].nxt)
        if(edge[l].to != fa) {
            value[edge[l].to] = value[now] + edge[l].weight;
            dfs(edge[l].to, now);
        }
            
}
int getLCA(int u, int v) {
    if(depth[u] < depth[v])
        swap(u, v);
    for (int i = dep; i >= 0; i--) {
        if(depth[fat[u][i]] >= depth[v])
            u = fat[u][i];
    }
    if(u == v)
        return u;
    for (int l = dep; l >= 0; l--) 
        if(fat[u][l] != fat[v][l]) {
            u = fat[u][l];
            v = fat[v][l];
        }
    return fat[u][0];
}
int main() {
    cin >> n;
    int u, v, w;
    init();
    for (int i = 1; i <= n - 1; i++) {
        cin >> u >> v >> w;
        add(u, v, w);
        add(v, u, w);
    }
    dfs(1, 0);
    // for (int i = 1; i <= 5; i++)
    //     cout << edge[i].weight << endl;
    // for (int i = 1; i <= 5; i++)
    //     cout << value[i] << endl;
        
    int m;
    cin >> m;
    for (int cnt = 1; cnt <= m; cnt++) {
        cin >> u >> v;
        cout << value[u] + value[v] - 2 * value[getLCA(u, v)] << endl;
    }
    return 0;
}