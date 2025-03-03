#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;
// const long long MIN = LONG_LONG_MIN;
int n, m, s;
int main() {
    cin >> n >> m >> s;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) 
        cin >> a[i];
    vector<long long> dp(m + 1, -1); //0-m人
    vector<long long> pre(m + 1, -1);
    pre[0] = 0;
    for (int i = 1; i <= n; i++) {
        int end;
        if(i == 1)
            end = -1;
        else
            end = 0;
        deque<long long> dq;
//         dq.push_back(0);
        for (int j = 1; j <= m; j++) {
            long long end_inf = min(m, j + s - 1);
            long long begin_sup;
            if(i == 1)
                begin_sup = max(0, j - 1);
            else
                begin_sup = max(1, j - 1);
            for(int k = end + 1; k <= end_inf; k++) {
                if(pre[k] == -1)
                    continue;
                while (!dq.empty() && pre[dq.back()] <= pre[k]) 
                    dq.pop_back();
                dq.push_back(k);
            }
            end = end_inf;
            while (!dq.empty() && dq.front() < begin_sup)
                dq.pop_front();
               
            if(!dq.empty()) 
                dp[j] = pre[dq.front()] + a[i - 1] * j;     
            else
                dp[j] = -1;   
        }
        pre = dp; 
    }
    long long ans = -1;
    for(int i = 1; i <= m; i++) {
        ans = max(ans, dp[i]);
    }
    cout << ans << endl;
    return 0;
}
