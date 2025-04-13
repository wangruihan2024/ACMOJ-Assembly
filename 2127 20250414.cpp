#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;
constexpr int MOD = 1e9 + 7;
constexpr int MAXN = 1e5 + 5;
int n;
unordered_map<int, int> past;
long long price[MAXN];
long long sum[MAXN << 2], sum2[MAXN << 2], tag[MAXN << 2];
void push_down(int node, int l, int r) {
    if(tag[node] == 0)
        return;
    int mid = (l + r) >> 1;
    int left_len = mid - l + 1;
    int right_len = r - mid;
    sum2[node << 1] = (sum2[node << 1] + 2 * tag[node] * sum[node << 1] + tag[node] * tag[node] * left_len) % MOD;
    sum[node << 1] = (sum[node << 1] + tag[node] * left_len) % MOD;
    tag[node << 1] += tag[node];
    sum2[(node << 1) + 1] = (sum2[(node << 1) + 1] + 2 * tag[node] * sum[(node << 1) + 1] + tag[node] * tag[node] * right_len) % MOD;
    sum[(node << 1) + 1] = (sum[(node << 1) + 1] + tag[node] * right_len) % MOD;
    tag[(node << 1) + 1] += tag[node];
    tag[node] = 0;
}
void update(int a, int b, long long val, int node, int l, int r) {
    if(a > r || b < l)
        return;
    if(a <= l && r <= b) {
        sum2[node] += 2 * val * sum[node] + val * val * (r - l + 1);
        sum[node] += val * (r - l + 1);
        tag[node] += val;
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) >> 1;
    update(a, b, val, node << 1, l, mid);
    update(a, b, val, (node << 1) + 1, mid + 1, r);
    sum[node] = sum[node << 1] + sum[(node << 1) + 1];
    sum2[node] = (sum2[node << 1] + sum2[(node << 1) + 1]) % MOD;
}
long long square(int a, int b, int node, int l, int r) {
    if(a > r || b < l)
        return 0;
    if(a <= l && b >= r)
        return sum2[node];
    push_down(node, l, r);
    int mid = (l + r) >> 1;
    return (square(a, b, node << 1, l, mid) + square(a, b, (node << 1) + 1, mid + 1, r)) % MOD;
}
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) 
        cin >> price[i];
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        int prev;
        if(past.count(price[i]))
            prev = past[price[i]];
        else
            prev = -1;
        update(prev + 1, i, 1, 1, 0, n - 1);
        ans = (ans + square(0, i, 1, 0, n - 1)) % MOD;
        past[price[i]] = i;
    }
    cout << ans << endl;
}