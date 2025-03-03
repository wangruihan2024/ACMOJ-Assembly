#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxValue(vector<int>& nums, int k) {
        int len = nums.size();
        vector<unordered_set<int>> Bfr = findOR(nums, k);
        vector<unordered_set<int>> Aft = findOR(vector<int>(nums.rbegin(), nums.rend()), k);
        int tmp = 0;
        for (size_t i = k - 1; i < len - k; ++i) 
            for (int a : Bfr[i]) 
                for (int b : Aft[len - i - 2]) 
                    tmp = max(tmp, a ^ b);
        return tmp;
    }

private:
    vector<unordered_set<int>> findOR(const vector<int>& nums, int k) {
        int len = nums.size(); 
        vector<unordered_set<int>> dp;
        vector<unordered_set<int>> pre(k + 1);
        pre[0].insert(0);
        for (int i = 0; i < len; ++i) {
            for (int j = min(k - 1, i + 1); j >= 0; --j) 
                for (int x : pre[j]) 
                    pre[j + 1].insert(x | nums[i]);
            dp.push_back(pre[k]);
        }
        return dp;
    }
};

int main() {
    Solution s;
    vector<int> a = {4, 2, 5, 6, 7};
    int k = 2;
    cout << s.maxValue(a, k) << endl;
}
