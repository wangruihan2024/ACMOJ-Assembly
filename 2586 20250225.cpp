#include <iostream>
#include <vector>
#include <deque>
using namespace std;
int n, k;
int main() {
    cin >> n >> k;
    vector<int> a(2*n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i + n] = a[i];
    }
    deque<int> sup(k, 0);
    vector<int> ans(n, 0);
    for(int i = 0; i < k; i++) {
        while(!sup.empty() && a[i] >= a[sup.back()])
            sup.pop_back();
        sup.push_back(i);
    }
    for(int i = k; i < 2 * n; i++) {
        while(!sup.empty() && a[i] >= a[sup.back()])
            sup.pop_back();
        sup.push_back(i);
        if(sup.front() <= i - k)
            sup.pop_front();
        ans[(i - k) % n] = a[sup.front()];
    }
    cout << ans[n - 1] << " ";
    for (int i = 0; i < n - 1; i++)
        cout << ans[i] << " ";
    cout << endl;
    return 0;
}