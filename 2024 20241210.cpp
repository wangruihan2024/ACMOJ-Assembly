#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int n, s;
vector<long long> a, t;
bool judge(long long current_time) {
    long long space_max = 0, sum = 0;
    for (int i = 1; i <= n; i++) {
        if(current_time > t[i]) {
            long long space_max2 = (current_time - t[i]) * a[i];
            space_max = max(space_max, space_max2);
            sum += (current_time - t[i]) * a[i];
        }
    }
    if(sum - space_max <= s)
        return true;
    //cout << current_time << "is not available by sum = " << sum << "max_space " << space_max << endl;
    return false;
}
long long bi_search(long long l, long long r) {
    while(l < r) {
           long long mid = l + (r - l) / 2;
            if (judge(mid)) {
                l = mid + 1;
            } else {
                r = mid;
            }
            if (l + 1 == r) break;
    }
    if(!judge(l))
        return l;
    return r;
}
int main() {
    cin >> n >> s;
    int cnt = 0;
    a.resize(n + 1, 0);
    t.resize(n + 1, 0);
    long long t_max = -1;
    long long int a_min = 2 * 1e10;
    for (int i = 1; i <= n; i++) {
        cin >> t[i] >> a[i];
        if(a[i] == 0)
            cnt++;
        if(a[i] > 0) {
            a_min = min(a_min, a[i]);
            t_max = max(t_max, t[i]);
        }
        
    }
    t_max = s / a_min + t_max + 1;
    if(cnt >= n - 1) {
        cout << -1 << endl;
        return 0;
    }
    cout << bi_search(0LL, t_max) << endl;
}