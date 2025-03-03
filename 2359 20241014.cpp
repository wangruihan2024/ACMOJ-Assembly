#include <bits/stdc++.h>
using namespace std;
const int maxn = 500005;
int n;
long long a[maxn], num;//a original
long long change[maxn];
//long long count[maxn], right[maxn];
void merge(int l, int r) {
    int mid = (l + r) / 2;
    int i = l, j = mid + 1, k = l;
    while(i <= mid && j <= r) {
        if(a[i] <= a[j]) {
            change[k++] = a[i++];
        }else {
            change[k++] = a[j++];
            num += mid - i + 1;
        }
    }
    while(i <= mid) {
        change[k++] = a[i++];
    }
    while(j <= r) {
        change[k++] = a[j++];
    }
    for (int i = l; i <= r; i++) {
        a[i] = change[i];
    }
}
void merge_sort(int l, int r) {
    if(l == r)
        return;
    int mid = (l + r) / 2;
    merge_sort(l, mid);
    merge_sort(mid + 1, r);
    merge(l, r);
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    merge_sort(1, n);
    cout << num << endl;
    return 0;
}