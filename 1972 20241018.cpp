#include <bits/stdc++.h>
using namespace std;
int a[270], result[10], ans;
int main() {
    for (int i = 0; i < 256; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= 255; i++) {
        for (int j = 0; j < 8; j++) {
            if(i & (1 << j))
                result[j] ^= a[i];
        }
    }
    for (int i = 0; i < 8; i++) {
        if(result[i]) {
            ans += (1 << i);
        }
    }
    cout << ans << endl;
    return 0;
}