#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
const int MOD = 1e9 + 7;
int n;
int main() {
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    unordered_map<int, long long> sum, cnt;
    for (int i = 0; i < n; i++) {
        long long c = (cnt[a[i] - 1] + cnt[a[i] + 1] + 1) % MOD;
        cnt[a[i]] = (c + cnt[a[i]]) % MOD;
        sum[a[i]] = (a[i] * c + sum[a[i]] + sum[a[i] - 1] + sum[a[i] + 1]) % MOD;

    }
    long long ans = 0;
    for(auto it = sum.begin(); it != sum.end(); it++)
        ans = (ans + it->second) % MOD;
    cout << ans << endl;
    return 0;
}