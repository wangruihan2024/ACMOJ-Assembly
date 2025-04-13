#include <iostream>
#include <set>
using namespace std;
set<pair<int, int>> num;
int main() {
    int n;
    cin >> n;
    char c;
    while(n--) {
        cin >> c;
        if(c == 'A') {
            int l, r;
            cin >> l >> r;
            int cnt = 0;
            auto it = num.begin();
            // cout << it->first;
            while(it != num.end() && it->first <= r) {
                if(it->second >= l) {
                    // cout << it->first << endl;
                    cnt++;
                    it = num.erase(it);
                }else {
                    it++;
                }
            }

            cout << cnt << endl;
            num.insert({l, r});
        }else {
            cout << num.size() << endl;
        }
    }
    return 0;
}