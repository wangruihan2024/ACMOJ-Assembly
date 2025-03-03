#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
using namespace std;
int n, c;
vector<long long> t;
vector<long long> pre;
vector<long long> dp;
long long y(long long a) {
    return dp[a] + a * a + pre[a] * pre[a] + 2 * a * pre[a];
}
long long x(long long a) {
    return a + pre[a];
}
long double k(long long a, long long b) {
    if(x(a) == x(b))
        return LLONG_MAX;
    return (long double)(y(a) - y(b)) / (x(a) - x(b));
}
bool inf_equal(long double k1, long double k2) {
    return k1 <= k2 + 1e-7;
}
bool inf(long double k1, long double k2)
{
    return k1 < k2 + 1e-7;
}
int main() {
    cin >> n >> c;
    t.resize(n + 1, 0), pre.resize(n + 1, 0), dp.resize(n + 1, 0);
    vector<long long> digit(n + 1, 0);
    // digit[1] = 1;
    for(int i = 1; i <= n; i++) {
        cin >> t[i];
        pre[i] = pre[i - 1] + t[i];
    }
    long long int head = 0, tail = 1;
    for(int i = 1; i <= n; i++) {
        long double K = 2 * (i - c + pre[i]);
        while(head + 1 < tail && inf_equal(k(digit[head], digit[head + 1]), K))
            head++;
        long long j = digit[head];
        dp[i] = dp[j] + (i - c - j + pre[i] - pre[j] - 1) * (i - c - j + pre[i] - pre[j] - 1);
      //  if(tail >= 2)
            while(head < tail - 1 && inf_equal(k(digit[tail - 1] , i), k(digit[tail - 2] , digit[tail - 1])))
                tail--;
        digit[tail++] = i;
    }
    cout << dp[n] << endl;
    return 0;
}