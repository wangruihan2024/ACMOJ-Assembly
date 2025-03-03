#include <iostream>
#include <unordered_set>
#include <queue>

using namespace std;

int main() {
    int T;
    cin >> T;
    while(T--) {
        int n;
        cin >> n;
        long long int ans = 0;
        priority_queue<int> a;
        //unordered_set<int> pre_even;
        int temp;
        while(n--) {
            cin >> temp;
            if(temp % 2 == 0) {
                a.push(temp);
            }
        }
        if(a.empty()) {
            cout << 0 << endl;
            continue;
        }
        while(!a.empty()) {
            int f = a.top();
            while(a.top() == f && !a.empty())
                a.pop();
            ans++;
            f /= 2;
            if(f % 2 == 0)
                a.push(f);
        }
        cout << ans << endl;
    }
}