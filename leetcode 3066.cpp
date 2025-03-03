#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        priority_queue<long long int, vector<long long int>, greater<long long int>> a;
        for (int i = 0; i < nums.size(); i++)
            a.push(nums[i]);
        int cnt = 0;
        while(a.top() < k) {
            long long int tmp1 = a.top();
            a.pop();
            long long int tmp2 = a.top();
            a.pop();
            a.push(2 * min(tmp1, tmp2) + max(tmp1, tmp2));
            cnt++;
        }
        return cnt;
    }
};
int main() {
    Solution s;
    vector<int> a = {1, 1, 2, 4, 9};
    int k = 20;
    cout << s.minOperations(a, k) << endl;
    return 0;
}