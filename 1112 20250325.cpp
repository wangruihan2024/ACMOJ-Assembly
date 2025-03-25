#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int N;
vector<vector<int>> node;
vector<int> sum;
vector<bool> vis;
vector<int> parent;
void dfs(const int &n) {
    vis[n] = true;
    sum[n] = 1;
    for(int i = 0; i < node[n].size(); i++) {
        if(!vis[node[n][i]]) {
            parent[node[n][i]] = n;
            dfs(node[n][i]);
            sum[n] += sum[node[n][i]];
        }
    }
}
bool check(const int &n) {
    // if(sum[n] <= N / 2)
    //     return true;
    if (N - sum[n] > N / 2) 
        return false;
    for(int i = 0; i < node[n].size(); i++) {
        if(sum[node[n][i]] > N / 2 && node[n][i] != parent[n])
            return false;
    }
    return true;
}
int main() {
    cin >> N;
    node.resize(N + 1), sum.resize(N + 1, 0), vis.resize(N + 1, false), parent.resize(N + 1, -1); // sum记录有多少个下面的节点
    int x, y;
    for (int i = 1; i <= N - 1; i++) {
        cin >> x >> y;
        node[x].push_back(y);
        node[y].push_back(x);
    }
    // cout << "dfs" << endl;
    dfs(1);
    // cout << "aftdfs" << endl;
    // for (int i = 1; i <= N; i++)
    //     cout << sum[i] << endl;
    for (int i = 1; i <= N; i++)
        if (check(i))
            cout << i << endl;
    return 0;
}