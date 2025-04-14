#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
vector<int> pi(const string &s) {
    size_t length = s.size();
    vector<int> pi_(length, 0);
    // pi_[0] = 1;
    for (int i = 1; i < length; i++) {
        int j = pi_[i - 1];
        while(j > 0 && s[j] != s[i])
            j = pi_[j - 1];
        if(s[j] == s[i])
            j++;
        pi_[i] = j;
    }
    return pi_;
}
int main() {
    string s1, s2;
    cin >> s1 >> s2;
    vector<int> s2_pi = pi(s2);
    int j = 0;
    for (int i = 0; i < (int)s1.size(); i++) {
        while(s1[i] != s2[j] && j > 0) {
            j = s2_pi[j - 1];
        }
        if(s1[i] == s2[j])
            j++;
        if(j == (int)s2.size()) {
            cout << i - (int)s2.size() + 2 << endl;
            j = s2_pi[j - 1];
        }
    }
    for (int i = 0; i < (int)s2.size(); i++)
        cout << s2_pi[i] << " ";
    return 0;
}