#include <iostream>
#include <map>
#include <utility>
typedef long long ll;
std::map<std::pair<ll, ll>, int> A;
ll h[50005], w[50005];
ll num;
ll h2, w2, k;
int main() {
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> h[i] >> w[i];
        std::pair<ll, ll> s = std::make_pair(h[i], w[i]);
        A[s]++;
    }
    std::cin >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= k; j++) {
            h2 = j ^ h[i];
            w2 = (k - j) ^ w[i];
            std::pair<ll, ll> s2 = std::make_pair(h2, w2);
            num += A[s2];
        }
    }
    if(k == 0)
        num -= n;
    std::cout << num / 2;
    return 0;
}