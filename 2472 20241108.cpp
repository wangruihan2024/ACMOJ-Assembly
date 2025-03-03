#include <iostream>
#include <set>

using namespace std;
int n, m;
multiset<int> a;
multiset<int> b;
int main() {
    cin >> n >> m;
    int temp;
    for (int i = 0; i < n; i++)
    {
        cin >> temp;
        a.insert(temp);
    }
    for (int i = 0; i < m; i++)
    {
        cin >> temp;
        b.insert(temp);
    }
    if(n < m) {
        cout << -1;
        return 0;
    }
    long long sum = 0;
    for (auto i = b.begin(); i != b.end(); i++)
    {
        auto it = a.lower_bound(*i);
        if(it == a.end()) {
            cout << -1;
            return 0;
        }
        sum += *it;
        a.erase(it);
    }
    cout << sum;
}