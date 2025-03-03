#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;
int m, n, k;
vector<vector<int>> sit; 
vector<vector<vector<int>>> dp; // 状态压缩 DP
vector<vector<bool>> bad; 
// 检查当前行状态 mask 是否合法（不能在破损格子放马）
bool valid(int mask, int row) {
    for (int i = 0; i < n; i++) {
        if ((mask & (1 << i)) && bad[row][i]) 
            return false;  
    }
    return true;
}
// 判断当前行 `cur` 和前一行 `p` 是否兼容
bool compatible_prev(int cur, int p) {
    for (int i = 0; i < n; i++) {  
        if (cur & (1 << i)) {  
            if (i - 2 >= 0 && (p & (1 << (i - 2)))) 
                return false;  
            if (i + 2 < n && (p & (1 << (i + 2)))) 
                return false;  
        }
    }
    return true; 
}
// 判断当前行 `cur` 和前前行 `pp` 是否兼容
bool compatible_prevprev(int cur, int pp) {
    for (int i = 0; i < n; i++) {  
        if (cur & (1 << i)) {  
            if (i - 1 >= 0 && (pp & (1 << (i - 1)))) 
                return false;
            if (i + 1 < n && (pp & (1 << (i + 1)))) 
                return false;
        }
    }
    return true;
}
int count_way() {
    for(int mask_tmp = 0; mask_tmp < (1 << n); mask_tmp++)
        if(valid(mask_tmp, 0))
            dp[0][0][mask_tmp] = 1;
    for(int mask_tmp = 0; mask_tmp < (1 << n); mask_tmp++) {
        if(!valid(mask_tmp, 1))
            continue;
        else {
            for(int mask_prev = 0; mask_prev < (1 << n); mask_prev++) {
                if(valid(mask_prev, 0) && compatible_prev(mask_tmp, mask_prev))
                    dp[1][mask_prev][mask_tmp] = (dp[1][mask_prev][mask_tmp] + dp[0][0][mask_prev]) % MOD;
            }
        }
    }
    for(int i = 2; i < m; i++) {
        for(int mask_tmp = 0; mask_tmp < (1 << n); mask_tmp++) {
            if(!valid(mask_tmp, i))
                continue;
            else {
                for(int mask_prev = 0; mask_prev < (1 << n); mask_prev++) {
                    if(!compatible_prev(mask_prev, mask_tmp) || !valid(mask_prev, i - 1))
                        continue;
                    else {
                        for(int mask_prevprev = 0; mask_prevprev < (1 << n); mask_prevprev++) {
                            if(!compatible_prevprev(mask_prevprev, mask_tmp) || !dp[i - 1][mask_prevprev][mask_prev] || !valid(mask_prevprev, i - 2))
                                continue;
                            else
                                dp[i][mask_prev][mask_tmp] = (dp[i][mask_prev][mask_tmp] + dp[i - 1][mask_prevprev][mask_prev]) % MOD;
                        }
                    }
                }
            }
        }
    }
    int ans = 0;
    for(int mask_prev = 0; mask_prev < (1 << n); mask_prev++)
        for(int mask_tmp = 0; mask_tmp < (1 << n); mask_tmp++)
            ans = (ans + dp[m - 1][mask_prev][mask_tmp]) % MOD;
    return ans;
}
int main() {
    cin >> m >> n >> k;
    bad.resize(m, vector<bool>(n, false));
    dp.resize(m, vector<vector<int>>(1 << n, vector<int>(1 << n, 0)));
    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        bad[x - 1][y - 1] = true;  
    }
    cout << count_way() << endl;
    return 0;
}
