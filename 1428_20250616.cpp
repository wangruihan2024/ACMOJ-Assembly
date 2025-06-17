#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int n, m;
vector<int> parent;

struct edge {
    int u;
    int v;
    int w;
    bool operator<(const edge& other) const {
        return w < other.w;
    }
};
vector<edge> edges;
int find(const int& x) {
    if(x != parent[x])
        parent[x] = find(parent[x]);
    return parent[x];
}
bool unite(int x, int y) {
    int fa_x = find(x);
    int fa_y = find(y);
    if(fa_x == fa_y)
        return false;
    parent[fa_x] = fa_y;
    return true;
}
int main() {
    cin >> n >> m;
    parent.resize(n + 1);
    edges.resize(m);
    for(int i = 0; i < m; i++)     
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    for(int i = 1; i <= n; i++)
        parent[i] = i;
    sort(edges.begin(), edges.end());

    int cnt = 0;
    long long int weight = 0;
    for(const auto &e : edges) {
        if(unite(e.u, e.v)) {
            cnt++;
            weight += (long long)e.w;
            if(cnt == n - 1)
                break;
        }
    }
    cout << weight << endl;
    return 0;
}