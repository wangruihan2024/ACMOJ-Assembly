#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    int minimumSubarrayLength(vector<int>& nums, int k) {
        int n = nums.size();
        int cans = n + 1;
        vector<int> bitcount(32, 0);
        for(int left = 0, right = 0; right < n; right++) {
            for(int i = 0; i < 32; i++) 
                bitcount[i] += (nums[right] >> i) & 1;
            if(cnt(bitcount, k)) {
                while(left <= right && cnt(bitcount, k)) {
                    cans = min(cans, right - left + 1);
                    // cout << "这是bitcount判断的结果" << cnt(bitcount, k) << endl;
                    // cout << "left:" << left << "right:" << right << endl;
                    for(int i = 0; i < 32; i++) 
                        bitcount[i] -= (nums[left] >> i) & 1;
                    left++;
                }
                // cout << "upd-cans:" << cans << endl;
            }
        }
        return ((cans < n + 1) ? cans:-1);
    }
private:
    bool cnt(vector<int> &bitcount, int k) {
        int ans = 0;
        for(int i = 0; i < 32; i++)
            if(bitcount[i])
                ans += (1 << i);
        //cout << " this is the value of bitcount：" << ans << endl;
        return (ans >= k);
    }
};
int main() {
    vector<int> nums = {1, 2};
    int k = 0;
    Solution sol;
    cout << sol.minimumSubarrayLength(nums, k);
    return 0;
}
