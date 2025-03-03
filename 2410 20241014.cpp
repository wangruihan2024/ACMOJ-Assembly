#include <iostream>
#include <algorithm>
using ull = unsigned long long;
ull p[64], y;
void insert(ull x) {
    for (int i = 63; i >= 0; i--) {
        if(!(x >> i))
            continue;
        if(!p[i]) {
            p[i] = x;
            break;
        }
        x ^= p[i];
    }
}
int main() {
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> y;
        insert(y);
    }
    ull ans = 0;
    for (int i = 63; i >= 0; i--) {
        ans = std::max(ans, ans ^ p[i]);
    }
    std::cout << ans << std::endl;
}