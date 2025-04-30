#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;
int n, Q;
long long res;
vector<int> a;
long long cnt[100005];
struct block {
    long long l, r, id;
};
long long doub(int x) {
    return x * x;
}
void add(int x, int add) {
    res -= doub(cnt[a[x]]);
    cnt[a[x]] += add;
    res += doub(cnt[a[x]]);
}
int main() {
    cin >> n >> Q;
    a.resize(n);
    int blockSize = sqrt(n) + 1;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<block> queries(Q);
    for (int i = 0; i < Q; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].l--; 
        queries[i].r--;
        queries[i].id = i;
    }
    auto cmp = [blockSize](const block &a, const block &b)
    {
        int block_a = a.l / blockSize;
        int block_b = b.l / blockSize;
        if(block_a != block_b)
            return block_a < block_b;
        else
            return (block_a % 2 == 0) ? (a.r < b.r) : (a.r > b.r);
    };
    sort(queries.begin(), queries.end(), cmp);
    vector<long long> ans(Q);
    int l = 0, r = -1;
    for(int i = 0; i < Q; i++) {
        while (r < queries[i].r) {
            r++;
            add(r, 1);
        }
        while (r > queries[i].r) {
            add(r, -1);
            r--;
        }
        while (l < queries[i].l) {
            add(l, -1);
            l++;
        }
        while (l > queries[i].l) {
            l--;
            add(l, 1);
        }
        // cout << "res :" << res << endl;
        ans[queries[i].id] = res;
    }
    for (int i = 0; i < Q; i++)
        cout << ans[i] << endl;
    return 0;
}