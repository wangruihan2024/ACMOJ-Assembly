#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <cmath>
using namespace std;
int n;
vector<long long> w, t, t_pre, w_pre;
int main() {
    cin >> n;
    w.resize(n + 1), t.resize(n + 1), t_pre.resize(n + 1, 0), w_pre.resize(n + 1, 0); // pre记录开工的时间
    vector<long long> wt(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> w[i] >> t[i];
        if(i >= 2)
            t_pre[i] = t_pre[i - 1] + t[i - 1];
        w_pre[i] = w_pre[i - 1] + w[i];
    }
    for (int i = 1; i <= n; i++)
        wt[i] = wt[i - 1] + w[i] * t_pre[i];
    long long ans = LONG_LONG_MAX;
    for (int i = 1; i <= n; i++) { // 枚举第二次休息的时间
        for (int j = 1; j <= i; j++) {
            long long vice_ans = t_pre[j] * w_pre[j] + t_pre[i] * (w_pre[i] - w_pre[j]) + (t_pre[n] + t[n]) * (w_pre[n] - w_pre[i]) - wt[n];
            ans = std::min(ans, vice_ans);
        }
            
    }
    cout << ans << endl;
    return 0;
}