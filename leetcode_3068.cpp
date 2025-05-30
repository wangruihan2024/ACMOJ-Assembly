#include <vector>

using namespace std;

class Solution {
public:
    long long maximumValueSum(vector<int>& nums, int k, vector<vector<int>>& edges) {
        long long int ans = 0;
        for(auto num : nums)
            ans += num;
        vector<int> newnums;
        for(auto num : nums)
            newnums.push_back((num ^ k) - num);
        sort(newnums.begin(), newnums.end());
        reverse(newnums.begin(), newnums.end());
        for(int i = 0; i < newnums.size() - 1; i+= 2) {
            if(newnums[i] + newnums[i + 1] <= 0)
                break;
            else
                ans += newnums[i] + newnums[i + 1];
        }
        return ans;
    }
};