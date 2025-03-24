#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
constexpr long long MOD = 1000000007;
long long ans(string s) {
    long long ans_ = 1;
    vector<long long> pi((int)s.size(), 0);
    vector<long long> num_s((int)s.size(), 0);
    num_s[1] = 1;
    long long j = 0;
    for (int i = 1; i < (int)s.size(); i++) {
        while(s[j] != s[i] && j > 0)
            j = pi[j];
        if(s[i] == s[j])
            j++;
        pi[i + 1] = j;
        num_s[i + 1] = num_s[j] + 1;
        // cout << "pi[" << i << "] equals" << j << endl;
    }
    // for (int i = 1; i < (int)s.size(); i++) {
    //     if (pi[i] > 0) 
    //         num_s[i] = num_s[pi[i] - 1] + 1;
    // }
    j = 0;
    for (int i = 1; i < (int)s.size(); i++) {
        while(j > 0 && s[i] != s[j])
            j = pi[j];
        if(s[i] == s[j])
            j++;
        while(j * 2 > (i + 1))
            j = pi[j];
        ans_ = ans_ * ((num_s[j] + 1) % MOD) % MOD;
    }
    // cout << "pi" << endl;
    // for(int i = 0; i < (int)s.size(); i++)
    //     cout << pi[i] << " ";
    // cout << endl << "num_s" << endl;
    // for(int i = 0; i < (int)s.size(); i++)
    //     cout << num_s[i] << " ";
    // cout << endl;
    return ans_;
}
int main() {
    int n;
    cin >> n;
    string s_;
    while(n--) {
        cin >> s_;
        cout << ans(s_) << endl;
    }
    return 0;
}