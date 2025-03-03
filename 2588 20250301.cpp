#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, m, s;
    cin >> n >> m >> s;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) 
        cin >> a[i];
    
    vector<long long> dp(m + 1, 0); // dp[j]表示当前内阁中有j人时的最大支持度
    
    for (int i = 0; i < n; i++) {
        vector<long long> pre(m + 1, 0); // pre[j]表示在第i年加入大臣后，内阁中有j人时的最大支持度
        deque<long long> dq;
        
        for (int j = 0; j <= m; j++) {
            // 维护dq，确保队列中的状态是有效的
            while (!dq.empty() && dq.front() < j - s)
                dq.pop_front();
            
            // 维护dq，确保队列中的状态是单调递减的
            while (!dq.empty() && dp[dq.back()] <= dp[j])
                dq.pop_back();
            
            dq.push_back(j);
            
            // 计算pre[j]
            pre[j] = dp[dq.front()] + a[i] * j;
        }
        
        // 更新dp数组
        dp = pre;
    }
    
    // 找出dp数组中的最大值
    long long ans = *max_element(dp.begin(), dp.end());
    cout << ans << endl;
    
    return 0;
}