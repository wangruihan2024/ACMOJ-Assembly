#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int MOD = 1e9 + 7;
    int countTexts(string pressedKeys) {
        int len = pressedKeys.size();
        vector<int> dp(len + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= len; i++) {
            dp[i] = dp[i - 1];
            if (i > 1 && pressedKeys[i - 1] == pressedKeys[i - 2])
                dp[i] = (dp[i] + dp[i - 2]) % MOD;
            if (i > 2 && pressedKeys[i - 1] == pressedKeys[i - 2] && pressedKeys[i - 1] == pressedKeys[i - 3])
                dp[i] = (dp[i] + dp[i - 3]) % MOD;
            if ((pressedKeys[i - 1] == '7' || pressedKeys[i - 1] == '9') && i > 3 && pressedKeys[i - 1] == pressedKeys[i - 2] && pressedKeys[i - 1] == pressedKeys[i - 3] && pressedKeys[i - 1] == pressedKeys[i - 4])
                dp[i] = (dp[i] + dp[i - 4]) % MOD;
        }
        return dp[len];
    }
};

int main() {
    Solution sol;
    string pressedKeys;
    cin >> pressedKeys;
    cout << sol.countTexts(pressedKeys) << endl;
    return 0;
}
