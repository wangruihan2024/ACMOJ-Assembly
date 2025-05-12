#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cstring>
using namespace std;
constexpr int MAXN = 1e5 + 5;
vector<int> adj[MAXN];
int disc[MAXN], low[MAXN], parent[MAXN];
bool isX[MAXN], isY[MAXN];  
int countX[MAXN], countY[MAXN]; 
int totalX, totalY;        
int timeCount;
set<pair<int, int>> bridges; 
void tarjan(int u) {
    disc[u] = low[u] = ++timeCount;
    countX[u] = isX[u];
    countY[u] = isY[u];
    for (int v : adj[u]) {
        if (disc[v] == 0) {
            parent[v] = u;
            tarjan(v);
            low[u] = min(low[u], low[v]);
            countX[u] += countX[v];
            countY[u] += countY[v];
            if (low[v] > disc[u]) {
                if ((countX[v] == 0 || countY[v] == 0) || 
                    (countX[v] == totalX || countY[v] == totalY)) {
                    int a = min(u, v);
                    int b = max(u, v);
                    bridges.insert({a, b});
                }
            }
        } else if (v != parent[u]) {
            low[u] = min(low[u], disc[v]);
        }
    }
}
int main() {
    int N, M, K, L;
    cin >> N >> M >> K >> L;
    for (int i = 0; i < K; ++i) {
        int x;
        cin >> x;
        isX[x] = true;
        totalX++;
    }
    for (int i = 0; i < L; ++i) {
        int y;
        cin >> y;
        isY[y] = true;
        totalY++;
    }
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }   
    timeCount = 0;
    memset(disc, 0, sizeof(disc));
    memset(low, 0, sizeof(low));
    memset(parent, -1, sizeof(parent));
    bridges.clear();
    tarjan(1);
    cout << bridges.size() << endl;
    for (auto edge : bridges) {
        cout << edge.first << " " << edge.second << endl;
    }    
    return 0;
}