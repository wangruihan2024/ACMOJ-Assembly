#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;
const long long MOD = 10000007;
long long n;
vector<long long> a;
unordered_map<long long, long long> m;
void push_up(vector<long long> &tr, long long p) {
    tr[p] = (tr[p << 1] + tr[(p << 1) + 1]) % MOD;
}
void build(long long l, long long r, long long p, vector<long long> &tree) {
    if (l == r) {
        tree[p] = 0;
        return;
    }
    long long mid = l + ((r - l) >> 1);
    build(l, mid, p << 1, tree);
    build(mid + 1, r, (p << 1) + 1, tree);
    push_up(tree, p);
}
long long query(long long l, long long r, long long gl, long long gr, vector<long long> &tree, long long p) {
    if (gl > gr || gr < l || r < gl) 
        return 0;  
    if (gl <= l && r <= gr) 
        return tree[p] % MOD;
    long long mid = l + ((r - l) >> 1);
    long long ans = 0;
    if (gl <= mid) 
        ans = (ans + query(l, mid, gl, gr, tree, p << 1)) % MOD;
    if (mid < gr) 
        ans = (ans + query(mid + 1, r, gl, gr, tree, (p << 1) + 1)) % MOD;
    return ans % MOD;
}
void update_tree(vector<long long> &tree, long long num, long long st, long long add) {
    long long p = st + m[num]; 
    tree[p] = (tree[p] + add + MOD) % MOD;
    while (p > 1) {
        p /= 2;
        push_up(tree, p);
    }
}
int main() {
    cin >> n;
    a.resize(n);
    for (long long i = 0; i < n; i++) 
        cin >> a[i];
    vector<long long> b = a;
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    long long s = b.size();
    long long st = 1;
    while (st < s) 
        st *= 2;  
    for (long long i = 0; i < s; i++) 
        m[b[i]] = i;
    vector<long long> ltree(2 * st, 0), rtree(2 * st, 0);
    build(0, st - 1, 1, ltree);
    build(0, st - 1, 1, rtree);
    for (long long i = 0; i < n; i++) 
        update_tree(rtree, a[i], st, a[i]);
    long long sum = 0;
    for (long long i = 0; i < n; i++) {
        long long rank = m[a[i]];
        long long sum_left = (rank > 0) ? query(0, st - 1, 0, rank - 1, ltree, 1) : 0;
        long long sum_right = (rank + 1 < s) ? query(0, st - 1, rank + 1, s - 1, rtree, 1) : 0;
        long long contri = ((a[i] % MOD) * (sum_left % MOD) % MOD) * (sum_right % MOD) % MOD;
        sum = (sum + contri) % MOD;
        update_tree(rtree, a[i], st, -a[i]);  
        update_tree(ltree, a[i], st, a[i]); 
    }
    cout << (sum + MOD) % MOD << endl;
    return 0;
}