#include <iostream>
#include <cmath>
using namespace std;
constexpr int MAXN = 5e4 + 5;
int n, m;
int a[MAXN << 2];
int tag[MAXN << 2];
int left_node[MAXN << 2], right_node[MAXN << 2];
int left_len[MAXN << 2], right_len[MAXN << 2];
int len[MAXN << 2];
void push_up(int node) {
    left_len[node] = left_len[node << 1];
    if(left_len[node << 1] == right_node[node << 1] - left_node[node << 1] + 1)
        left_len[node] += left_len[(node << 1) + 1];
    right_len[node] = right_len[(node << 1) + 1];
    if(right_len[(node << 1) + 1] == right_node[(node << 1) + 1] - left_node[(node << 1) + 1] + 1)
        right_len[node] += right_len[node << 1];
    len[node] = max(max(len[node << 1], len[(node << 1) + 1]), right_len[node << 1] + left_len[(node << 1) + 1]);
}
void push_down(int node) {
    if(tag[node] != -1) {
        tag[node << 1] = tag[node];
        tag[(node << 1) + 1] = tag[node];
        if(tag[node] == 0) {
            int left_range = right_node[node << 1] - left_node[node << 1] + 1;
            len[node << 1] = left_len[node << 1] = right_len[node << 1] = left_range;
            
            int right_range = right_node[(node << 1) + 1] - left_node[(node << 1) + 1] + 1;
            len[(node << 1) + 1] = left_len[(node << 1) + 1] = right_len[(node << 1) + 1] = right_range;
        }else {
            len[node << 1] = left_len[node << 1] = right_len[node << 1] = 0;
            len[(node << 1) + 1] = left_len[(node << 1) + 1] = right_len[(node << 1) + 1] = 0;
        }
        tag[node] = -1;
    }
}
void build(int node, int l, int r){
    left_node[node] = l;
    right_node[node] = r;
    tag[node] = -1;
    len[node] = left_len[node] = right_len[node] = r - l + 1;
    if(l == r)
        return;
    int mid = (l + r) >> 1;
    build(node << 1, l, mid);
    build((node << 1) + 1, mid + 1, r);
}
void update(int node, int l, int r, int val) {
    if(left_node[node] > r || right_node[node] < l)
        return;
    if(l <= left_node[node] && right_node[node] <= r) {
        tag[node] = val;
        if(val == 1) {
            len[node] = left_len[node] = right_len[node] = 0;
        }else {
            len[node] = left_len[node] = right_len[node] = right_node[node] - left_node[node] + 1;
        }
        return;
    }
    push_down(node);
    update(node << 1, l, r, val);
    update((node << 1) + 1, l, r, val);
    push_up(node);
}
int query(int node, int D) {
    if(len[node] < D)
        return 0;
    if(left_node[node] == right_node[node])
        return left_node[node];
    push_down(node);
    if(len[node << 1] >= D)
        return query(node << 1, D);
    if(right_len[node << 1] + left_len[(node << 1) + 1] >= D)
        return right_node[node << 1] - right_len[node << 1] + 1;
    if(len[(node << 1) + 1] >= D)
        return query((node << 1) + 1, D);
    
    return 0;
}
int main() {
    cin >> n >> m;
    build(1, 1, n);
    while(m--) {
        int type;
        cin >> type;
        if(type == 1) {
            int D;
            cin >> D;
            int ans = query(1, D);
            if(ans != 0)
                update(1, ans, ans + D - 1, 1);
            cout << ans << endl;
        }else {
            int x, y;
            cin >> x >> y;
            update(1, x, x + y - 1, 0);
        }
    }
    return 0;
}