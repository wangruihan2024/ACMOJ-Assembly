#include <iostream>
#include <vector>
using namespace std;
vector<vector<int>> adj; 
vector<int> subtreeSize;  
vector<long long> totalSubtreeSum; 
int n;
void dfs1(int node, int parent) {
    subtreeSize[node] = 1;  
    for (int neighbor : adj[node]) {
        if (neighbor != parent) {
            dfs1(neighbor, node);
            subtreeSize[node] += subtreeSize[neighbor];
        }
    }
}
void dfs2(int node, int parent) {
    for (int neighbor : adj[node]) {
        if (neighbor != parent) {
            totalSubtreeSum[neighbor] = totalSubtreeSum[node] + (n - 2 * subtreeSize[neighbor]);
            dfs2(neighbor, node);
        }
    }
}
void init() {
    for(int i = 0; i < n; i++)
        totalSubtreeSum[0] += subtreeSize[i];
}
int main() {
    cin >> n;
    adj.resize(n);
    subtreeSize.resize(n, 0);  
    totalSubtreeSum.resize(n, 0); 
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; 
        v--;  
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(0, -1);
    init();
    dfs2(0, -1);  
    for (int i = 0; i < n; i++) 
        cout << totalSubtreeSum[i] << endl;
    return 0;
}
