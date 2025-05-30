#include <vector>
using namespace std;
class Solution {
public:
    int countSubarrays(vector<int>& nums) {
        int res = 0;
        int n = nums.size();
        for (int i = 0; i + 2 < n; ++i) {
            int a = nums[i], b = nums[i + 1], c = nums[i + 2];
            if (b % 2 == 0 && a + c == b / 2) {
                res++;
            }
        }
        return res;
    }
};
