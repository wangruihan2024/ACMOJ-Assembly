#include <iostream>
#include <vector>
using namespace std;
long long a[100005];
long long tr[100005 << 2];
long long tag[100005 << 2];
void push_up(int p) {
    tr[p] = tr[p << 1] + tr[(p << 1) + 1];
}
void push_down(int l, int r, int p) {
    if(tag[p] != 0) {
        int mid = l + ((r - l) >> 1);
        if(l != r && tag[p] != 0) {
            tag[p << 1] += tag[p];
            tag[(p << 1) + 1] += tag[p];
            tr[p << 1] += tag[p] * (mid - l + 1);
            tr[(p << 1) + 1] += tag[p] * (r - mid);
            tag[p] = 0;
        }
    }
}
void build(int l, int r, int p) {
    tag[p] = 0;
    if(l == r) {
        tr[p] = a[l];
        return;
    }
    int mid = l + ((r - l) >> 1);
    build(l, mid, p << 1);
    build(mid + 1, r, (p << 1) + 1);
    push_up(p);
}
void add(int gl, int gr, int l, int r, int p, long long k) {
    if(gl <= l && gr >= r) {
        tr[p] += k * (r - l + 1);
        tag[p] += k;
        return;
    }
    int mid = l + ((r - l) >> 1);
    push_down(l, r, p);
    if(gl <= mid)
        add(gl, gr, l, mid, p << 1, k);
    if(gr > mid)
        add(gl, gr, mid + 1, r, (p << 1) + 1, k);
    push_up(p);
}
long long sum(int gl, int gr, int l, int r, int p) {
    if(gl <= l && gr >= r)
        return tr[p];
    int mid = l + ((r - l) >> 1);
    long long ans = 0;
    push_down(l, r, p);
    if(gl <= mid)
        ans += sum(gl, gr, l, mid, p << 1);
    if(gr > mid)
        ans += sum(gl, gr, mid + 1, r, (p << 1) + 1);
    return ans;
}
int main() {
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n; i++) 
        cin >> a[i];
    build(0, n - 1, 1);
    int mode, x, y;
    long long k;
    while(m--) {
        cin >> mode;
        if(mode == 1) { // 区间加k
            cin >> x >> y >> k;
            x--, y--;
            add(x, y, 0, n - 1, 1, k);
        }else { // sum
            cin >> x >> y;
            x--, y--;
            cout << sum(x, y, 0, n - 1, 1) << endl;
        }
    }
    return 0;
}