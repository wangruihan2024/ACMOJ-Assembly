#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxValueOfCoins(vector<vector<int>>& piles, int k) {
        vector<int> ans(k + 1, -1); // ans[i]记录操作i次的最大面值和
        ans[0] = 0;
        for(auto it = piles.begin(); it != piles.end(); it++) {
            for(int cnt = k; cnt > 0 ; cnt--) {
                int value = 0; // 前缀和
                int length = (*it).size();
                for(int i = 1; i <= min(length, cnt); i++) {
                    value += (*it)[i - 1];
                    if(ans[cnt - i] != -1)
                        ans[cnt] = max(ans[cnt], ans[cnt - i] + value);
                }
            }
        }
        return ans[k];
    }
private:
};

int main() {
    Solution s;
    vector<vector<int>> piles = {{1, 100, 3}, {7, 8, 9}};
    cout << s.maxValueOfCoins(piles, 2) << endl;
}
