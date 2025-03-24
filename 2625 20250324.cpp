#include <iostream>
#include <vector>
#include <climits>
using namespace std;
int n;
vector<long long> w, t, wt;
vector<long long> t_pre, w_pre;
vector<vector<long long>> dp;
long long x(int j1, int j2) {
    return w_pre[j2] - w_pre[j1];
}
long long y(int j1, int j2) {
    return wt[j2] - wt[j1] + dp[j2][0] - dp[j1][0];
}
long double k_(int j1, int j2) {
    return (long double)y(j1, j2) / x(j1, j2);
}
int main() {
    cin >> n;
    w.resize(n, 0), t.resize(n, 0), wt.resize(n, 0), t_pre.resize(n, 0), w_pre.resize(n, 0);
    dp.resize(n, vector<long long>(2, 0));
    for (int i = 0; i < n; i++)
        cin >> w[i] >> t[i];
    w_pre[0] = w[0];
    for (int i = 1; i < n; i++) {
        t_pre[i] = t_pre[i - 1] + t[i - 1]; // 记录第i个人开工的时间
        w_pre[i] = w_pre[i - 1] + w[i]; // 0-i的w的和
    }
    for (int i = 1; i < n; i++) 
        wt[i] = wt[i - 1] + w[i] * t_pre[i];
    for (int i = 1; i < n; i++)
        dp[i][0] = t_pre[i] * w_pre[i] - wt[i]; //在编号i的人开始的时候第一个断点的价值 
    long long ans = LONG_LONG_MAX;
    long long idx[20005];
    idx[0] = 0;
    int head = 0;
    int tail = 1;
    for (int k = 1; k < n; k++) { // 后一个节点
        long double K = (long double)(t_pre[k]);
        while(k_(idx[head], idx[head + 1]) <= K && head + 1 < tail)
            head++;
        dp[k][1] = dp[idx[head]][0] + t_pre[k] * (w_pre[k] - w_pre[idx[head]]) - wt[k] + wt[idx[head]];
        while(head + 1 < tail && k_(idx[tail - 2], idx[tail - 1]) > k_(idx[tail - 1], k))
            tail--;
        idx[tail++] = k;
    }
    for (int k = 1; k < n; k++) {
        long long tmp = dp[k][1] + (t_pre[n - 1] + t[n - 1]) * (w_pre[n - 1] - w_pre[k]) - wt[n - 1] + wt[k];
        // cout << "tmp:" << tmp << endl;
        ans = min(ans, tmp);
    }
    // for (int i = 0; i < n; i++) {
    //     cout << dp[i][1] << "--";
    // }
    // cout << endl;
    cout << ans << endl;
}