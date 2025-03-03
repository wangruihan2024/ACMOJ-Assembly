#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int waysToSplitArray(vector<int>& nums) {
        int cnt = 0;
        int len = nums.size();
        // cout << "len:" << len << endl;
        vector<long long int> sum(len, 0);
        for(int i = 0; i < len; i++) {
            sum[i] = (i >= 1) ? sum[i - 1] + nums[i] : nums[0];
        }
        for(int i = 0; i < len - 1; i++)
            if(sum[i] >= sum[len - 1] - sum[i]) {
                cnt++;
                // cout << i << endl;
            }
                
        return cnt;
    }
};
int main() {
    Solution s;
    vector<int> a = {2, 3, 1, 0};
    cout << s.waysToSplitArray(a);
    return 0;
}