#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class BipartiteMatcher {
private:
    vector<vector<int>> graph;
    vector<int> match_to;
    vector<bool> visited;

    bool bpm(int u) {
        for (int v : graph[u]) {
            if (!visited[v]) {
                visited[v] = true;
                if (match_to[v] == -1 || bpm(match_to[v])) {
                    match_to[v] = u;
                    return true;
                }
            }
        }
        return false;
    }

public:
    BipartiteMatcher(int n) : graph(n), match_to(n, -1), visited(n) {}

    void add_edge(int u, int v) {
        graph[u].push_back(v);
    }

    int max_matching() {
        int result = 0;
        for (int u = 0; u < graph.size(); ++u) {
            fill(visited.begin(), visited.end(), false);
            if (bpm(u)) {
                result++;
            }
        }
        return result;
    }

    vector<int> get_matching() {
        return match_to;
    }
};

int main() {
    int n;
    cin >> n;
    vector<int> A(n), B(n);
    for (int i = 0; i < n; ++i) {
        cin >> A[i] >> B[i];
    }

    vector<bool> matched_A(n, false);
    vector<bool> matched_B(n, false);
    int zero_cost_matches = 0;

    // Step 1: Match all zero-cost edges (A_i >= B_i)
    for (int i = 0; i < n; ++i) {
        if (A[i] >= B[i] && !matched_A[i] && !matched_B[i]) {
            matched_A[i] = true;
            matched_B[i] = true;
            zero_cost_matches++;
        }
    }

    // Step 2: Build bipartite graph for remaining nodes
    vector<int> remaining_A, remaining_B;
    for (int i = 0; i < n; ++i) {
        if (!matched_A[i]) {
            remaining_A.push_back(i);
        }
        if (!matched_B[i]) {
            remaining_B.push_back(i);
        }
    }

    int m = remaining_A.size();
    int k = remaining_B.size();
    BipartiteMatcher bm(m);

    for (int i = 0; i < m; ++i) {
        int a_idx = remaining_A[i];
        for (int j = 0; j < k; ++j) {
            int b_idx = remaining_B[j];
            if (A[a_idx] >= B[b_idx]) {
                bm.add_edge(i, j);
            }
        }
    }

    int one_cost_matches = bm.max_matching();

    // Step 3: Check if perfect matching exists
    if (zero_cost_matches + one_cost_matches != n) {
        cout << -1 << endl;
    } else {
        cout << zero_cost_matches << endl;
    }

    return 0;
}