#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v;
    long long w;
};

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    if(n == 1) {
        if(edges[0].w < 0)
            cout << "Yes" << endl << 1 << endl << edges[0].u << endl;
        else
            cout << "No" << endl;
        return 0;
    }
    vector<long long> dist(n + 1, 0);
    vector<int> predecessor(n + 1, -1);
    int last_updated_vertex = -1;
    for (int i = 0; i < n; ++i) {
        last_updated_vertex = -1;
        for (const Edge& e : edges) {
            if (dist[e.v] > dist[e.u] + e.w) {
                dist[e.v] = dist[e.u] + e.w;
                predecessor[e.v] = e.u;
                last_updated_vertex = e.v;
            }
        }
    }
    if (last_updated_vertex == -1) {
        cout << "No" << endl;
        return 0;
    }
    int vertex_in_cycle = last_updated_vertex;
    for (int i = 0; i < n; ++i) {
        vertex_in_cycle = predecessor[vertex_in_cycle];
    }
    vector<int> cycle;
    for (int v = vertex_in_cycle; ; v = predecessor[v]) {
        if (v == vertex_in_cycle && cycle.size() > 1) {
            break;
        }
        cycle.push_back(v);
        /*if (cycle.size() > n) {
            cycle.resize(n);
            break;
        }*/
    }
    reverse(cycle.begin(), cycle.end());
    cout << "Yes" << endl;
    cout << cycle.size() << endl;
    for (int v : cycle) {
        cout << v << " ";
    }
    cout << endl;
    
    return 0;
}