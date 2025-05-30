#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

class Solution {
public:
    long long numberOfPowerfulInt(long long start, long long finish, int limit, string s) {
        return calculate(finish, limit, s) - calculate(start - 1, limit, s);
    }
private:
    long long dp[20][2][2]; // 第一位表示计算到了哪一位，第二位表示是否达到limit值，第三位表示是否满足后缀
    string upper, suffix;   // upper是上限数字的字符串， suffix是后缀
    int limit;         
    int n, m; //upper的位数，后缀的位数
    long long calculate(long long num, int limit_, const string &s) {
        upper = to_string(num);
        suffix = s;
        limit = limit_;
        n = upper.size();
        m = suffix.size();
        if (n < m)
            return 0;
        memset(dp, -1, sizeof(dp));
        return dfs(0, true, true);
    }
    long long dfs(int pos, bool tight, bool match) {
        if (pos == n) 
            return match ? 1 : 0;
        if (dp[pos][tight][match] != -1)
            return dp[pos][tight][match];
        long long res = 0;
        int max_digit = tight ? (upper[pos] - '0') : 9;
        max_digit = min(max_digit, limit);
        for (int d = 0; d <= max_digit; ++d) {
            bool new_tight = tight && (d == (upper[pos] - '0'));
            bool new_match = false;
            if (match) {
                if (pos >= n - m) {
                    int s_pos = m - (n - pos);
                    if (d == (suffix[s_pos] - '0'))
                        new_match = true;
                } else {
                    new_match = true;
                }
            } else {
                if (pos >= n - m) {
                    int s_pos = m - (n - pos);
                    if (d == (suffix[s_pos] - '0'))
                        new_match = false;
                    else
                        continue;
                }
            }
            res += dfs(pos + 1, new_tight, new_match);
        }
        return dp[pos][tight][match] = res;
    }
};