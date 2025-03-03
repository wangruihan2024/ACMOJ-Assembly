#include <iostream>
#include <vector>

using namespace std;
int n, W;
vector<long long int> w, v, c;
vector<long long int> nw, nv;
void rearrange(const int n, const vector<long long int>& w, const vector<long long int>& v, const vector<long long int>& c, vector<long long int>& nw, vector<long long int>& nv) {
    for (int i = 0; i < n; i++) {
        long long remaining = c[i];
        for (long long k = 1; k <= remaining; k *= 2) {
            nw.push_back(w[i] * k);
            nv.push_back(v[i] * k);
            remaining -= k;
        }
        if (remaining > 0) {  
            nw.push_back(w[i] * remaining);
            nv.push_back(v[i] * remaining);
        }
    }
}
int main() {
    scanf("%d%d", &n, &W);
    w.resize(n);
    v.resize(n);
    c.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%lld%lld%lld", &w[i], &v[i], &c[i]);
    rearrange(n, w, v, c, nw, nv);
    long long int size = nw.size();
    vector<long long int> dp(W + 1, 0);
    for (int i = 0; i < size; i++) {
        for (int j = W; j >= nw[i]; j--) {
            dp[j] = max(dp[j], dp[j - nw[i]] + nv[i]);
        }
    }
    printf("%lld\n", dp[W]);
    return 0;
}