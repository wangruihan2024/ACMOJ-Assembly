#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    long long countGoodIntegers(int n, int k) {
        // 提前计算阶乘
        vector<long long> factorial(n + 1, 1);
        long long ans = 0;
        for (int i = 1; i <= n; i++) {
            factorial[i] = factorial[i - 1] * i;
        }
        unordered_set<string> ss;
        // base指的是回文串前一半的部分
        int base = pow(10, (n - 1) / 2);
        // skip = 1时n是奇数
        int skip = n & 1;
        for (int i = base; i < base * 10; i++) {
            string s = to_string(i);
            s += string(s.rbegin() + skip, s.rend());
            long long current = stoll(s);
            if (current % k == 0) {
                sort(s.begin(), s.end());
                ss.emplace(s);
            }
        }
        for (const string &s : ss) {
            vector<int> cnt(10);
            for (char c : s) {
                cnt[c - '0']++;
            }
            long long tmp = (n - cnt[0]) * factorial[n - 1];
            for (int x : cnt) {
                tmp /= factorial[x];
            }
            ans += tmp;
        }
        return ans;
    }
};