#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;
constexpr int MAXN = 205;
int m, n;
int score[MAXN]; // 学分
int head[MAXN]; // 第一条边
int idx = 0; // 编号
int dp[MAXN][MAXN]; // 以i为根的子树中j个节点
struct Edge {
    int to; // 指向的节点
    int nxt; // 旁边的边的编号
} edge[MAXN];
void add (int fa, int son) {
    edge[idx].to = son;
    edge[idx].nxt = head[fa];
    head[fa] = idx++;
}
void dfs(int u, int t) {
    if(t <= 0)
        return;
    for(int i = head[u]; i != -1; i = edge[i].nxt) {
        int v = edge[i].to;
        for (int k = 0; k < t; k++)
            dp[v][k] = dp[u][k] + score[v];
        dfs(v, t - 1);
        for (int k = 1; k <= t; k++)
            dp[u][k] = max(dp[u][k], dp[v][k - 1]);
    }
}
int main() {
    cin >> m >> n;
    int tmp;
    fill(head, head + MAXN, -1);
    for(int i = 1; i <= m; i++) {
        cin >> tmp >> score[i];
        add(tmp, i);
    }
    dfs(0, n);
    cout << dp[0][n] << endl;
    return 0;
}