#include <iostream>
#include <vector>
using namespace std;
vector<unsigned long long> A;
vector<unsigned long long> B;
int n, m;
unsigned long long uppernum(unsigned long long a, unsigned long long b) {
    if(a % b == 0)
        return a / b;
    return (a / b + 1);
}
bool if_min(vector<unsigned long long> &A, vector<unsigned long long> &B, const int m, const unsigned long long mid) {
    unsigned long long spare = 0, extra = 0;
    for (int i = 1; i <= n; i++) {
        if(A[i] >= B[i]) {//上课效率高
            if(m * A[i] >= mid) {//只上课就可以
                spare += (m - uppernum(mid, A[i]));
            }else {
                unsigned long long rest = mid - m * A[i];
                extra += uppernum(rest, B[i]);
            }
        }else {//翘课听这个课效率高
            if(m * B[i] >= mid) {//只翘自己的课就可以
                spare += (m - uppernum(mid, B[i]));
            }else {
                unsigned long long rest = mid - m * B[i];
                extra += uppernum(rest, B[i]);
            }
        }
    }
    if(extra > spare)
        return false;
    return true;
}
unsigned long long binary_search(unsigned long long &l, unsigned long long &r, unsigned long long &ans) {
    while(l <= r) {
        unsigned long long mid = (l + r) / 2;
        if (if_min(A, B, m, mid)) {
            ans = mid;
            l = mid + 1; 
        } else {
            r = mid - 1; 
        }
    }
    return ans;
}
int main() {
    cin >> n >> m;//n门课 m weeks
    A.resize(n + 1, 0);
    B.resize(n + 1, 0);
    unsigned long long A_max = -1, B_max = -1;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
        A_max = max(A[i], A_max);
    }
    for (int i = 1; i <= n; i++) {
        cin >> B[i];
        B_max = max(B[i], B_max);
    }
    unsigned long long l = 0, r, ans = -1;
    r = m * max(A_max, B_max);
    cout << binary_search(l, r, ans) << endl;
    return 0;
}