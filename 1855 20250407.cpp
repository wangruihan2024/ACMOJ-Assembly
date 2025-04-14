#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
constexpr int MAXN = 5e5 + 5;
constexpr int MAXE = 2 * MAXN;
int n, idx;
int head[MAXN]; // 节点指向的边的编号
int to[MAXE], nxt[MAXE]; // 边指向的点-边的旁边一条边
long long dp[MAXN][2];
void init() {
    memset(head, -1, sizeof(head));
    idx = 0;
}
void add(int u, int v) {
    to[idx] = v;
    nxt[idx] = head[u];
    head[u] = idx++;
}
void dfs(int u, int parent) { // u是点的编号
    for(int i = head[u]; i != -1; i = nxt[i]) {
        int v = to[i];
        if(v == parent)
            continue;
        dfs(v, u);
    }
    for(int i = head[u]; i != -1; i = nxt[i]) {
        int v = to[i];
        if(v == parent)
            continue;
        dp[u][0] += max(dp[v][0], dp[v][1]);
    }
    long long sum = 0;
    for (int i = head[u]; i != -1; i = nxt[i]) {
        int v = to[i];
        if(v == parent)
            continue;
        sum += dp[v][0];
    }
    for (int i = head[u]; i != -1; i = nxt[i]) {
        int v = to[i];
        if(v == parent)
            continue;
        dp[u][1] = max(dp[u][1], dp[u][0] - max(dp[v][0], dp[v][1]) + dp[v][0]+ 1);
    }
}
int main() {
    cin >> n;
    init();
    int u, v;
    for(int i = 1; i <= n - 1; i++) {
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    
    dfs(1, 0);
    cout << max(dp[1][0], dp[1][1]);

    return 0;
}