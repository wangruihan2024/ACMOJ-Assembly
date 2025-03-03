#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> a, dp, step; // dp[i]记录长度=i时最小的a， step记录每一步走的下标;
int length;
int binary_search(vector<int> &dp, int num) {
    int l = 1, r = dp.size() - 1, ans = 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (dp[mid] <= num) { 
            ans = mid; 
            l = mid + 1; 
        } else {
            r = mid - 1;
        }
    }
    return ans; 
}
void binary_dp(int &n, vector<int> &a, vector<int> &dp, vector<int> &step, vector<int> &local_prev, int &length) {
    dp.push_back(0);
    dp.push_back(a[1]);
    step.push_back(0);
    step.push_back(1);
    local_prev.resize(n + 1, 0);
    length++;
    for (int i = 2; i <= n; i++) {
        int digit = binary_search(dp, a[i]);
        if(digit == length) {
            dp.push_back(a[i]);
            length++;
            step.push_back(i);
        }else {
            dp[digit + 1] = a[i];
            step[digit + 1] = i;
        }
        local_prev[i] = step[digit];
    }

    // cout << "prev array after DP: ";
    // for (int i = 1; i <= n; i++) {
    //     cout << local_prev[i] << " ";
    // }
    // cout << endl;

}
void cout_path(vector<int> &step, vector<int> &local_prev, int length) {
    vector<int> path;
    int temp = step[length];
    while(temp != 0) {
        path.push_back(temp);
        temp = local_prev[temp];
    }
    reverse(path.begin(), path.end());
    for (auto it = path.begin(); it != path.end(); it++)
        cout << *it << " ";
}
int main() {
    int n;
    cin >> n;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    vector<int> previous;
    binary_dp(n, a, dp, step, previous, length);
    cout << length << endl;
    cout_path(step, previous, length);
    cout << endl;
}