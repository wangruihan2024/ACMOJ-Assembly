#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[0][0] = 1;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if(obstacleGrid[i][j] == 1)
                    dp[i][j] = 0;
                else if(i > 0 && j > 0)
                    dp[i][j] = dp[i][j - 1] + dp[i - 1][j];
                else if(i == 0 && j != 0)
                    dp[i][j] = dp[i][j - 1];
                else if(i != 0 && j == 0)
                    dp[i][j] = dp[i - 1][j];
                else
                    dp[0][0] = 1;
            }
        }
        return dp[m - 1][n - 1];
    }
};

int main() {
    Solution s;
    vector<vector<int>> a = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    cout << s.uniquePathsWithObstacles(a) << endl;
}
