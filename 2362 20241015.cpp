#include <bits/stdc++.h>
using namespace std;
int n, a[105],tag = 1;
bool cmp(string a, string b) {
    if(a.size() != b.size())
        return a.size() < b.size();
    return a < b;
}
int main() {
    cin >> n;
    string ans;
    cin >> ans;
    for (int i = 2; i <= n; i++) {
        string num;
        cin >> num;
        if(cmp(ans, num)){
            ans = num;
            tag = i;
        }
    }
    int len = ans.size();
    for (int j = 0; j < len; j++) {
        a[j] = ans[len - j - 1] - '0';
    }
    cout << tag << endl;
    for (int i = len - 1; i >= 0;i--) {
        cout << a[i];
    }
    cout << endl;
}