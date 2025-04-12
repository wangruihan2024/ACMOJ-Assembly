#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
constexpr int MAXN = 2005;
long long n, ans, result;
vector<int> adj[MAXN]; 
long long subtreeSize[MAXN], f[MAXN];
void dfs(int now, int parent) {
    subtreeSize[now] = 1;
    for (int neighbor : adj[now]) {
        if (neighbor != parent) {
            dfs(neighbor, now);
            subtreeSize[now] += subtreeSize[neighbor];
        }
    }
}
void find_f(int now, int parent, long long max_value) {
    f[now] = subtreeSize[now];
    f[parent] -= f[now];
    max_value = max(max_value, f[parent]);
    for (int neighbor : adj[now]) {
        if (neighbor != parent) {
            find_f(neighbor, now, max_value);
        }
    }
    f[parent] += f[now];
    result += max(max_value, subtreeSize[now]);
}
int main() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        result = 0;
        dfs(i, -1);
        find_f(i, -1, 0);
        ans += result;
    }
    cout << ans << endl;
    return 0;
}