#include <iostream>
#include <vector>
using namespace std;
int count = 0;
/*bool if_check(const int n, const vector<int> &a) {
    for (int i = 1; i <= n; i++) {
        if(a[i] == 0)
            return false;
    }
    return true;
}*/
void binary_search(int &l, int &r, const int n, vector<int> &a) {
    if(l >= r) {
        cout << -1 << endl;
        return;
    }
    if(count > 100) {
        cout << -1 << endl;
        return;
    }
    int mid = (l + r)/2;
    if(a[mid - 1] == 0) {
        if(mid - 1 >= 1) {
            cout << 0 << " " << mid - 1 << endl;
            cin >> a[mid - 1];
            count++;
        }else {
            a[mid - 1] = n + 1;
        }
    }
    if(a[mid] == 0) {
        cout << 0 << " " << mid << endl;
        cin >> a[mid];
        count++;
    }
    if(a[mid + 1] == 0) {
        if(mid + 1 <= n) {
            cout << 0 << " " << mid + 1 << endl;
            cin >> a[mid + 1];
            count++;
        }else {
            a[mid + 1] = n + 1;
        }        
    }
    if(a[mid] < a[mid + 1] && a[mid] < a[mid - 1]) {
        cout << 1 << " " << mid << endl;
        return;
    }else if(a[mid] > a[mid + 1]) {
        l = mid;
        binary_search(l, r, n, a);
    }else if(a[mid] > a[mid - 1]) {
        r = mid;
        binary_search(l, r, n, a);
    }
}
int main() {
    int n;
    cin >> n;
    vector<int> a(n + 2, 0);
    int l = 1, r = n;
    binary_search(l, r, n, a);

    return 0;
}
