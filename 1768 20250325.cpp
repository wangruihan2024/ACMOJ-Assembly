#include <iostream>
#include <vector>
#include <utility>
using namespace std;
int n, Q;
vector<vector<pair<int, int>>> node;
vector<bool> vis;
vector<int> val;
void dfs(const int &idx, const int &ans) {
    vis[idx] = true;
    val[idx] = ans;
    for (auto& [n_, w_] : node[idx]) {
        if(!vis[n_])
            dfs(n_, ans ^ w_);
    }
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    cin >> n >> Q;
    node.resize(n + 1), vis.resize(n + 1, false), val.resize(n + 1, 0);
    int x, y, w;
    for (int i = 1; i <= n - 1; i++) {
        cin >> x >> y >> w;
        node[x].push_back({y, w});
        node[y].push_back({x, w});
    }
    dfs(1, 0);
    while(Q--) {
        cin >> x >> y;
        cout << (val[x] ^ val[y]) << '\n';
    }
    return 0;
}