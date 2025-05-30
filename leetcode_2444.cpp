#include <vector>
using namespace std;

class Solution {
public:
    long long countSubarrays(vector<int>& nums, int minK, int maxK) {
        int n = nums.size();
        int lastMin = -1, lastMax = -1, lastInvalid = -1;
        long long res = 0;
        for (int i = 0; i < n; ++i) {
            if (nums[i] < minK || nums[i] > maxK)
                lastInvalid = i;
            if (nums[i] == minK)
                lastMin = i;
            if (nums[i] == maxK)
                lastMax = i;
            int bound = min(lastMin, lastMax);
            if (bound > lastInvalid)
                res += bound - lastInvalid;
        }
        return res;
    }
};
