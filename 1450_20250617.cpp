#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool bpm(const vector<vector<bool>>& graph, int u, vector<bool>& seen, vector<int>& vis) {
    int n = graph.size();
    for (int v = 0; v < n; ++v) {
        if (graph[u][v] && !seen[v]) {
            seen[v] = true;
            if (vis[v] < 0 || bpm(graph, vis[v], seen, vis)) {
                vis[v] = u;
                return true;
            }
        }
    }
    return false;
}
bool match(const vector<vector<bool>>& graph) {
    int n = graph.size();
    vector<int> vis(n, -1);
    for (int u = 0; u < n; u++) {
        vector<bool> seen(n, false);
        if (!bpm(graph, u, seen, vis))
            return false;
    }
    return true;
}
vector<vector<int>> solv(const vector<vector<bool>>& graph) {
    int n = graph.size();
    vector<int> vis(n, -1);
    for (int u = 0; u < n; ++u) {
        vector<bool> seen(n, false);
        bpm(graph, u, seen, vis);
    }
    vector<vector<int>> result(n, vector<int>(n, 0));
    for (int v = 0; v < n; v++) {
        if (vis[v] != -1)
            result[vis[v]][v] = 1;
    }
    return result;
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> A(n, vector<int>(n));
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++) 
            cin >> A[i][j];
    vector<vector<bool>> graph(n, vector<bool>(n, false));
    for (int i = 0; i < n; ++i) 
        for (int j = 0; j < n; ++j) 
            if (A[i][j] == 1) 
                graph[i][j] = true;
    if (match(graph)) {
        vector<vector<int>> solution = solv(graph);
        cout << "Yes" << endl;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                cout << solution[i][j] << " ";
            cout << endl;
        }
    } else
        cout << "No" << endl;
    return 0;
}