#include <iostream>
#include <deque>
#include <vector>
using namespace std;
int n;
int main() {
    cin >> n;
    vector<int> cost(n);
    vector<long long int> pre(n, 0);
    deque<int> right;
    right.push_back(0);
    vector<int> right_min(n, n), left_min(n, -1); 
    for(int i = 0; i < n; i++) {
        cin >> cost[i];
        pre[i] = (i == 0 ? cost[0] : pre[i - 1] + cost[i]);
        if(i) {
            while(!right.empty() && cost[i] < cost[right.back()]) {
                right_min[right.back()] = i;
                right.pop_back();
            }
            right.push_back(i);
        }
    }
    // for (int i = 0; i < n; i++)
    //     cout << i << " ";
    // cout << endl;
    // for (int i = 0; i < n; i++)
    //     cout << right_min[i] << " ";
    // cout << endl;
    deque<int> left;
    left.push_back(n - 1);
    for(int i = n - 2; i >= 0; i--) {
        while(!left.empty() && cost[i] < cost[left.back()]) {
            left_min[left.back()] = i;
            left.pop_back();
        }
        left.push_back(i);
    }
    // for (int i = 0; i < n; i++)
    //     cout << left_min[i] << " ";
    // cout << endl;
    long long int max_ans = -1;
    for(int i = 0; i < n; i++) {
        int l = left_min[i] + 1;
        int r = right_min[i] - 1;
        long long int cost_sum = pre[r] - ((l == 0) ? 0 : pre[l - 1]);
        max_ans = std::max(max_ans, cost[i] * cost_sum);
    }
    cout << max_ans << endl;
    return 0;
}