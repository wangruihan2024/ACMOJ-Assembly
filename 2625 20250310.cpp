#include <iostream>
#include <deque>
#include <vector>

using namespace std;
using ll = long long;

struct Worker {
    ll w, t;
};

double slope(pair<ll, ll> a, pair<ll, ll> b) {
    return (double)(b.second - a.second) / (b.first - a.first);
}

int main() {
    int n;
    cin >> n;
    vector<Worker> workers(n + 1);
    vector<ll> S(n + 1, 0), dp(n + 1, 0), W(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        cin >> workers[i].w >> workers[i].t;
        S[i] = S[i - 1] + workers[i - 1].t;
        W[i] = W[i - 1] + workers[i].w;
    }

    deque<pair<ll, ll>> hull;  // 维护下凸包 (S[i], dp[i])

    for (int i = 1; i <= n; i++) {
        // 斜率优化：找到最优的 j
        while (hull.size() >= 2 && slope(hull[0], hull[1]) <= W[i]) {
            hull.pop_front();
        }

        // 计算 dp[i]
        if (!hull.empty()) {
            int j = hull.front().first;
            dp[i] = dp[j] + W[i] * (S[i] - S[j]);
        }

        // 维护凸包，保证新插入的点不会被旧点覆盖
        pair<ll, ll> newLine(S[i], dp[i]);
        while (hull.size() >= 2 && slope(hull[hull.size() - 2], hull.back()) >= slope(hull.back(), newLine)) {
            hull.pop_back();
        }
        hull.push_back(newLine);
    }

    cout << dp[n] << endl;  // 输出最优解
    return 0;
}
