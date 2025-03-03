#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> ans(n, vector<int> (n, 0));
        int cnt = 0; // 填到第几行
        int num = 1; // 填入到哪个数字
        while(cnt <= (n - 1) / 2) {
            int linedigit = n - 2 * cnt - 1;
            for (int i = 0; i < linedigit; i++) {
                ans[cnt][cnt + i] = num;
                num++;
            }
            for (int i = 0; i < linedigit; i++) {
                ans[cnt + i][n - cnt - 1] = num;
                num++;
            }
            for (int i = 0; i < linedigit; i++)
            {
                ans[n - cnt - 1][n - cnt - i - 1] = num;
                num++;
            }
            for (int i = 0; i < linedigit; i++)
            {
                ans[n - cnt - i - 1][cnt] = num;
                num++;
            }
            cnt++;
        }
        // cout << "num:" << num << endl;
        // cout << "cnt:" << cnt << endl;
        if(n % 2)
            ans[cnt - 1][cnt - 1] = num;
        return ans;
    }
};

int main() {
    Solution s;
    vector<vector<int>> a = s.generateMatrix(3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}
