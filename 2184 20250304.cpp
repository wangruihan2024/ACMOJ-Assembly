#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int INF = 1e9;
inline int read() {
    int c = getchar(), x = 0;
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x;
}
int n, m;
vector<int> h;
int sup[5000005 >> 2], tag[5000005 >> 2];
void push_up(int p) {
    sup[p] = max(sup[p << 1], sup[(p << 1) + 1]);
}
void push_down(int l, int r, int p) {
    if(tag[p] != INF) {  
        if (sup[p] <= tag[p]) {  
            tag[p] = INF;
            return;
        }   
        sup[p] = min(sup[p], tag[p]);
        if(l < r) {
            tag[p << 1] = min(tag[p << 1], tag[p]);
            tag[(p << 1) + 1] = min(tag[(p << 1) + 1], tag[p]);
        }
        tag[p] = INF;
    }  
}
void build(int l, int r, int p) {
    tag[p] = INF;
    if(l == r) {
        sup[p] = h[l];
        return;
    }
    int mid = l + (r - l >> 1);
    build(l, mid, p << 1);
    build(mid + 1, r, (p << 1) + 1);
    push_up(p);
}
void update(int gl, int gr, int l, int r, int p, int x) {
    push_down(l, r, p);
    if (sup[p] <= x) 
        return;
    if(gl <= l && gr >= r) {
        tag[p] = min(tag[p], x);
        push_down(l, r, p);
        return;
    }
    int mid = l + ((r - l) >> 1);
    if(gl <= mid)
        update(gl, gr, l, mid, p << 1, x);
    if(gr > mid)
        update(gl, gr, mid + 1, r, (p << 1) + 1, x);
    push_up(p);
}
void query(int l, int r, int p, vector<int>& ans) {
    push_down(l, r, p);
    if(l == r) {
        ans[l] = sup[p];
        return;
    }
    int mid = l + ((r - l) >> 1);
    query(l, mid, p << 1, ans);
    query(mid + 1, r, (p << 1) + 1, ans);
}
int main() {
    n = read(), m = read();
    h.resize(n);
    for (int i = 0; i < n; i++)
        cin >> h[i];
    build(0, n - 1, 1);
    vector<int> ans(n);
    int lt, rt, x;
    while(m--) {
        x = read(), lt = read(), rt = read();
        lt--, rt--;
        update(lt, rt, 0, n - 1, 1, x);
        // query(0, n - 1, 1, ans);
        // for (int i = 0; i < n; i++)
        //     cout << ans[i] << " ";
        // cout << endl;
    }
    query(0, n - 1, 1, ans);
    for (int i = 0; i < n; i++)
        cout << ans[i] << " ";
    cout << endl;
    return 0;
}