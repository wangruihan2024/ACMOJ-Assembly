#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n + 1), f(n + 1), p(n + 1), b(n + 1, 0);
    
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        p[a[i]] = i;
    }
    for (int i = 1; i <= n; i++)
        cin >> f[i];
    b[1] = 1;
    int l = n + 5, r = -1;
    for (int i = 1; i <= n; i++) {
        l = min(l, p[i]);
        r = max(r, p[i]);
        b[r - l + 1]++;
    }
    for (int i = 1; i <= n; i++) {
        b[i] += b[i - 1];
        if(f[i] < b[i]) {
            cout << i << endl;
            return 0;
        }
    }
    cout << 0;
    return 0;
}
