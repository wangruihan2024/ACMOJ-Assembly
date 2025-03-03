#include <iostream>
#include <vector>
using namespace std;
int n, m;
vector<long long int> l;
vector<long long int> l_pre;
vector<long long int> l_af;
int main() {
    cin >> n >> m;
    l.resize(m);
    l_pre.resize(m);
    l_af.resize(m);
    cin >> l[0];
    l_pre[0] = l[0];
    long long int sum = l[0];
    for (int i = 1; i < m; i++) {
        cin >> l[i];
        l_pre[i] = l_pre[i - 1] + l[i];
        sum += l[i];
    }
    l_af[0] = sum;
    for (int i = 1; i < m; i++) {
        l_af[i] = sum - l_pre[i - 1];
    }
    // for (int i = 0; i < m; i++)
    //     cout << l_af[i] << "-";
    // cout << endl;
    if (sum < n || (m - 1 + l[m - 1]) > n)
    {
        cout << -1;
        return 0;
    }
    vector<long long int> p(m);
    p[0] = 1;
    for (int i = 1; i < m; i++) {
        p[i] = max(p[i - 1] + 1, n - l_af[i] + 1);
    }
    for (int i = 0; i < m; i++)
        cout << p[i] << " ";
    return 0;
}