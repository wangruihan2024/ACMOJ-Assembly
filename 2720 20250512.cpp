#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <climits>
#include <algorithm>
using namespace std;
struct Edge {
    int neighbor;
    int weight;
};
struct State {
    long long total;
    long long alt;  
};
int n, k;
vector<vector<Edge>> graph;
vector<State> dp;
State dfs(int node, int parent) {
    long long base = 0;
    vector<long long> gains;
    for (const Edge& conn : graph[node]) {
        int child = conn.neighbor;
        if (child == parent) continue;
        State childState = dfs(child, node);
        base += childState.total;
        long long gain = childState.alt + conn.weight - childState.total;
        if (gain > 0) gains.push_back(gain);
    }
    sort(gains.begin(), gains.end(), greater<long long>());
    long long topK = base;
    for (int i = 0; i < min(k, (int)gains.size()); ++i) {
        topK += gains[i];
    }
    long long topKMinus1 = base;
    for (int i = 0; i < min(k - 1, (int)gains.size()); ++i) {
        topKMinus1 += gains[i];
    }   
    return dp[node] = {topK, topKMinus1};
}
int main() {
    cin >> n >> k;
    graph.resize(n);
    dp.resize(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }
    State result = dfs(0, -1);
    cout << result.total << endl;
    return 0;
}