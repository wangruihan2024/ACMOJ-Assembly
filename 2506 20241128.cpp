#include <iostream>
#include <vector>

using namespace std;
const unsigned long long MAXN = 1e18;

int main() {
    int N;
    cin >> N;
    vector<unsigned long long> w(N + 1, 0);
    for (int i = 0; i <= N; i++)
        cin >> w[i];
    vector<vector<unsigned long long>> dp(N + 1, vector<unsigned long long>(N + 1, 0));
    for (int length = 2; length <= N; length++) {
        for (int r = 0; r <= N - length; r++) {
            int l = r + length - 1;
            dp[r][l] = MAXN;
            for (int d = r; d < l; d++) {
                dp[r][l] = min(dp[r][l], dp[r][d] + dp[d + 1][l] + w[r] * w[d + 1] * w[l + 1]);
            }
        }
    }
    cout << dp[0][N - 1] << endl;
    return 0;
}