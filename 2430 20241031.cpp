#include <iostream>
#include <vector>
using namespace std;
int n;
long long int k;
vector<int> nxt;
int main() {
    cin >> n >> k;
    nxt.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> nxt[i];
    }
    vector<vector<int>> dp(n + 1, vector<int>(32, 0));
    for (int i = 1; i <= n; i++) {
        dp[i][0] = nxt[i];
    }
    for (int i = 1; i < 32; i++) {
        for (int j = 1; j <= n; j++) {
            dp[j][i] = dp[dp[j][i - 1]][i - 1];
        }
    }
    for (int i = 1; i <= n; i++) {
        int temp = i;
        for (int j = 0; j < 32; j++) {
            if(k & (1LL << j)) {
                temp = dp[temp][j];
            }
        }
        cout << temp << " ";
    }
        return 0;
}