#include <iostream>
#include <vector>
#include <set>
using namespace std;
int n;
string c;
vector<int> pi;
vector<int> find_pi(string &c) {
    vector<int> pi_(n, 0);
    for (int i = 1; i < n; i++) {
        int j = pi_[i - 1];
        while(j > 0 && c[j] != c[i])
            j = pi_[j - 1];
        if(c[j] == c[i])
            j++;
        pi_[i] = j;
    }
    return pi_;
}
int main() {
    cin >> n;
    cin >> c;
    pi = find_pi(c);
    for(int i = 0; i < n; i++) {
        int len = i + 1; 
        int p = len - pi[i];
        if(p != len && len % p == 0)
            printf("%d\n", 0);
        else
            printf("%d\n", p - len % p);
    }
    return 0;
}