#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxCoins(vector<int>& piles) {
        int len = piles.size();
        sort(piles.begin(), piles.end(), [](int a, int b) -> bool
             { return a > b; });
        int ans = 0;
        for (int i = 1; i < 2 * len / 3; i += 2) {
            // cout << i << ":" << piles[i] << endl;
            ans += piles[i];
        }
            
        return ans;
    }
};

int main() {
    Solution s;
    vector<int> a = {2, 4, 5};
    cout << s.maxCoins(a) << endl;
}
