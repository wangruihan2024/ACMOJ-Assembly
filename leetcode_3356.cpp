#include <vector>
using namespace std;

class Solution {
public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        int m = queries.size();
        auto check = [&](int k) -> bool {
            vector<long long> diff(n + 2, 0);
            for (int i = 0; i < k; ++i) {
                int l = queries[i][0];
                int r = queries[i][1];
                int val = queries[i][2];
                diff[l] += val;
                diff[r + 1] -= val;
            }
            long long acc = 0;
            for (int i = 0; i < n; ++i) {
                acc += diff[i];
                if (acc < nums[i]) 
                    return false; 
            }
            return true;
        };
        int left = 0, right = m, ans = -1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (check(mid)) {
                ans = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return ans;
    }
};
