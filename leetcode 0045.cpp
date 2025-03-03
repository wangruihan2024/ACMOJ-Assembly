#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int jump(vector<int>& nums) {
        int MAX = 1e4 + 5;
        int n = nums.size();
        vector<int> dp(n, MAX); //从i出发到达n - 1最小的跳跃次数
        for (int i = 0; i < n; i++)
            if(i + nums[i] >= n - 1)
                dp[i] = 1;
        dp[n - 1] = 0;
        for (int i = n - 2; i >= 0; i--) {
            for (int stp = 1; stp <= nums[i] && i + stp < n; stp++)
                dp[i] = min(dp[i], dp[i + stp] + 1);
        }
        return dp[0];
    }
};

int main() {
    Solution s;
    vector<int> nums = {2, 1};
    cout << s.jump(nums) << endl;
}
