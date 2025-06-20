#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

long long count(const string &n_str, const vector<int> &validDigits) {
    int len = n_str.size();
    vector<vector<long long>> dp(len + 1, vector<long long>(2, 0));  // dp[i][isTight]
    dp[len][0] = dp[len][1] = 1;
    for (int i = len - 1; i >= 0; i--) {
        int limit = n_str[i] - '0';
        dp[i][0] = (long long)validDigits.size() * dp[i + 1][0];
        for (int d : validDigits) {
            if (d < limit) {
                dp[i][1] += dp[i + 1][0];
            } else if (d == limit) {
                dp[i][1] += dp[i + 1][1];
            }
        }
    }
    long long cnt = dp[0][1];
    long long multiplier = validDigits.size();
    for (int i = 1; i < len; ++i) {
        cnt += multiplier;
        multiplier *= validDigits.size();
    }
    return cnt;
}
string find(const string &bound, const vector<int> &allowed) {
    string res = bound;
    bool relaxed = false;
    int len = bound.length();
    for (int i = 0; i < len; ++i) {
        int currentDigit = bound[i] - '0';
        if (relaxed) {
            res[i] = '0' + allowed.back();
            continue;
        }
        auto itr = lower_bound(allowed.begin(), allowed.end(), currentDigit);
        if (itr != allowed.end() && *itr == currentDigit) {
            res[i] = '0' + currentDigit;
        } else if (itr != allowed.begin()) {
            --itr;
            res[i] = '0' + *itr;
            relaxed = true;
        } else {
            int backtrack = i - 1;
            while (backtrack >= 0) {
                int prevDigit = res[backtrack] - '0';
                auto it2 = lower_bound(allowed.begin(), allowed.end(), prevDigit);
                if (it2 != allowed.begin()) {
                    --it2;
                    res[backtrack] = '0' + *it2;
                    for (int j = backtrack + 1; j < len; ++j)
                        res[j] = '0' + allowed.back();
                    relaxed = true;
                    break;
                }
                --backtrack;
            }
            if (backtrack < 0) {
                string alt(len - 1, '0' + allowed.back());
                return alt.empty() ? "0" : alt;
            }
            break;
        }
    }
    int firstNonZero = 0;
    while (firstNonZero < res.size() - 1 && res[firstNonZero] == '0') {
        ++firstNonZero;
    }
    return res.substr(firstNonZero);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q, T;
    cin >> q >> T;
    while (T--) {
        int m;
        string n;
        cin >> m >> n;
        vector<int> digits(m);
        for (int i = 0; i < m; ++i)
            cin >> digits[i];
        sort(digits.begin(), digits.end());
        if (q == 1) {
            cout << count(n, digits) << endl;
        } else {
            cout << find(n, digits) << endl;
        }
    }
    return 0;
}