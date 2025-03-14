#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int length = nums.size();
        if(length == 1)
            return nums[0] == target;
        int l = 0, r = length - 1;
        while(l <= r) {
            int mid = (l + r) / 2;
            if(nums[mid] == target)
                return true;
            if(nums[l] == nums[mid] && nums[mid] == nums[r]) {
                l++;
                r--;
            }else if(nums[mid] >= nums[l]) {
                if(nums[mid] > target && nums[l] <= target)
                        r = mid - 1;
                else
                    l = mid + 1;
            }else{
                if(nums[mid] < target && nums[length - 1] >= target)
                    l = mid + 1;
                else
                    r = mid - 1;
            }
        }
        return false;
    }
};

int main() {
    Solution s;
    vector<int> a = {1, 0, 1, 1, 1};
    cout << s.search(a, 0) << endl;
}
