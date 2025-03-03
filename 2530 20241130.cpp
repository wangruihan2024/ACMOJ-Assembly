#include <iostream>
#include <vector>

using namespace std;
const int MOD = 1000007;
int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        vector<int> prefix(m + 1, 0); // dp[i - 1][[0] 到 dp[i - 1][m] 的加和
        for (int j = 0; j <= m; j++) {
            prefix[j] = dp[i - 1][j];
            if(j > 0)
                prefix[j] = (prefix[j] + prefix[j - 1]) % MOD;
        }
        for (int j = 0; j <= m; j++) {
            if(j <= a[i - 1]) {
                dp[i][j] = prefix[j];
            }else {
                dp[i][j] = (prefix[j] - prefix[j - a[i - 1] - 1] + MOD) % MOD;
            }
        }
    }
    cout << dp[n][m] << endl;
    return 0;
}