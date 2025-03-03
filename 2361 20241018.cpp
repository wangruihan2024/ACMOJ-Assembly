#include <bits/stdc++.h>
using namespace std;
int n, Q, a[10005];
int main() {
    cin >> n >> Q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    while(Q--) {
        int inp;
        cin >> inp;
        if(inp == 1){
            int posit, altern;
            cin >> posit >> altern;
            a[posit - 1] = altern;
        }else{
            int posit, ans = 0;
            cin >> posit;
            for (int i = 0; i < n; i++) {
                if(a[i] < a[posit - 1] || (a[i] == a[posit - 1] && i <= posit - 1))
                    ans++;
            }
            cout << ans << endl;
        }
    }
    return 0;
}