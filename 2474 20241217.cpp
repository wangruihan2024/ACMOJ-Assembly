#include <iostream>
#include <algorithm>
using namespace std;
int n;
bool zero_num = false, positive = true;
long long int ans;
int main() {
    cin >> n;
    long long int temp;
    while(n--) {
        cin >> temp;
        if(temp == 0) {
            zero_num = true;
            ans++;
        }
        else if(temp > 0) {
            ans += abs(temp - 1);
        } else {
            ans += abs(temp + 1);
            if(positive)
                positive = false;
            else
                positive = true;
        }
    }
    if(zero_num || positive)
        cout << ans << endl;
    else
        cout << ans + 2 << endl;
}