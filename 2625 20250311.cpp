#include <iostream>
#include <vector>
#include <climits>
using namespace std;
int n;
vector<long long> w, t, pre_w, pre_t, wt;
long double k(int b0, int b1, int b2) {
    long long dx = pre_w[b1] - pre_w[b2];
    long long dy = pre_t[b1] * (pre_w[b1] - pre_w[b0]) - pre_t[b2] * (pre_w[b2] - pre_w[b0]);
    return (long double) dy / dx;
}
int main() {
    cin >> n;
    w.resize(n + 1, 0), t.resize(n + 1, 0), pre_w.resize(n + 1, 0), pre_t.resize(n + 1, 0), wt.resize(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> w[i] >> t[i];
        pre_t[i] = pre_t[i - 1] + t[i - 1];
        pre_w[i] = pre_w[i - 1] + w[i];
    }
    for (int i = 1; i <= n; i++) {
        wt[i] = wt[i - 1] + w[i] * pre_t[i];
    }
    long double K = (long double)pre_t[n] + t[n];
    long long ans = LONG_LONG_MAX;
    for (int i = 1; i < n; i++) {
        int j = i + 1;
        while(j < n && k(i, j, j + 1) <= K)
            j++;
        long long vice = pre_t[i] * pre_w[i] + pre_t[j] * (pre_w[j] - pre_w[i]) + K * (pre_w[n] - pre_w[j]);
        ans = min(ans, vice);
    }
    cout << ans - wt[n] << endl;
    return 0;
}