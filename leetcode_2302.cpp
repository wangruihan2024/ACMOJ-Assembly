#include <vector>
using namespace std;

class Solution {
public:
    long long countSubarrays(vector<int>& nums, long long k) {
        int n = nums.size();
        vector<long long> prev(n, 0);
        prev[0] = nums[0];
        if(n > 1)
            for(int i = 1; i < n; i++)
                prev[i] = prev[i - 1] + nums[i];
        long long cnt = 0, sum = 0;
        int l, r;
        for(l = 0; l < n; l++) {
            r = n - 1;
            sum = prev[n - 1] - (l == 0 ? 0 : prev[l - 1]);
            while(r >= l && (r - l + 1) * sum >= k) {
                sum -= nums[r];
                r--;
            }
            cnt += (r - l + 1);
        }
        return cnt;
    }
};

class Solution {
public:
    long long countSubarrays(vector<int>& nums, long long k) {
        int n = nums.size();
        long long cnt = 0, sum = 0;
        int l = 0, r = 0;
        for(r = 0; r < n; r++) {
            sum += nums[r];
            while(l <= r && sum * (r - l + 1) >= k) {
                sum -= nums[l];
                l++;
            }
            cnt += (r - l + 1);
        }
        return cnt;
    }
};