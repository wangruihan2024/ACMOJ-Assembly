#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;
constexpr int MAXN = 5005;
int n, k;
pair<long long, long long> card[MAXN];
long long dp[MAXN][MAXN];
int main() {
    cin >> n >> k;
    for (int i = 0; i < n; i++)
        cin >> card[i].first >> card[i].second;
    sort(card, card + n, [](const auto& x, const auto& y) {
        return x.second < y.second;
    });
    for (int i = 0; i < n; i++) {
        dp[i + 1][1] = max(dp[i][1], card[i].first + card[i].second);
    }
    for (int i = 2; i <= k; i++)
    {
        for (int j = i - 1; j < n; j++)
        {
            dp[j + 1][i] = max(dp[j][i], dp[j][i - 1] + card[j].first);
        }
    }
    long long ans = LONG_LONG_MIN;
    for(int i = k - 1; i < n; i++) {
        ans = max(ans, dp[i + 1][k] - card[i].second);
    }
    cout << ans << endl;
    return 0;
}