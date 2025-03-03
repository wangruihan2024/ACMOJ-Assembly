#include <bits/stdc++.h>
using namespace std;
int n, k;
int a[100005];
void exchange(int l, int r) {
    if(k == 0)
        return ;
    if(k > 0 && l < (r - 1)) {
        int mid = (l + r) / 2;
//        cout << mid << endl;
        swap(a[mid - 1] , a[mid]);//调换一次中间+2次
        k--;
        exchange(l, mid);
        exchange(mid, r);
    }
}
int main() {
    cin >> n >> k;
    if((k % 2 == 0) || k > (2 * n - 1)) {
        cout << -1;
        return 0;
    }else {
        k--;
        k /= 2;
        for (int i = 0; i < n; i++)
            a[i] = i + 1;
        
        //        cout << k << endl;
        exchange(0, n);
        for (int i = 0; i < n - 1; i++)
            cout << a[i] << " ";
        cout << a[n - 1];
    }
    return 0;
}