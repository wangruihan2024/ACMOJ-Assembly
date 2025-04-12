#include <iostream>
using namespace std;
constexpr int MOD = 1e9 + 7;
long long dp[1005];
int main() {
    int n;
    cin >> n;
    dp[0] = 1, dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        for(int j = 0; j < i; j++) {
            dp[i] = ((dp[j] * dp[i - 1 - j] % MOD) + dp[i]) % MOD;
        }
    }
    cout << dp[n] % MOD << endl;
    return 0;
}