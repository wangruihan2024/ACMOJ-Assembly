#include <iostream>
#include <string>
#include <set>
#include <utility>
using namespace std;
const int mod1 = 1e9 + 7, mod2 = 1e9 + 9;
const int base1 = 103, base2 = 137;
int n, m;

int main() {
    cin >> n >> m;
    string s;
    cin >> s;
    long long hash_value1 = 0, hash_value2 = 0;
    long long temp_1 = 1, temp_2 = 1;
    for (int i = 0; i < m - 1; i++) {
        temp_1 = (temp_1 * base1) % mod1;
        temp_2 = (temp_2 * base2) % mod2;
    }
        for (int i = 0; i < m; ++i)
        {
            hash_value1 = (hash_value1 * base1 + s[i]) % mod1;
            hash_value2 = (hash_value2 * base2 + s[i]) % mod2;
        }
    set<pair<long long, long long>> value;
    value.insert({hash_value1, hash_value2});
    for (int i = m; i < n; ++i) {
        hash_value1 = (hash_value1 - s[i - m] * temp_1 % mod1 + mod1) % mod1;
        hash_value2 = (hash_value2 - s[i - m] * temp_2 % mod2 + mod2) % mod2;
        hash_value1 = (hash_value1 * base1 + s[i]) % mod1;
        hash_value2 = (hash_value2 * base2 + s[i]) % mod2;       
        value.insert({hash_value1, hash_value2});
    }
    cout << value.size() << endl;
    return 0;
}
