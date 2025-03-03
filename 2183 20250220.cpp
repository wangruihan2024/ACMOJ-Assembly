#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <utility>
#include <algorithm>
using namespace std;
int n, m;
int main() {
    scanf("%d%d", &n, &m);
    vector<int> a(n);
    unordered_map<int, int> location; // 上一次出现的最大位置
    vector<int> pre(n + 1, 0); // 以i为右端点最长可以到达哪里
    vector<vector<int>> st(n, vector<int>(ceil(log2(n)), 0));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        if(location.find(a[i]) != location.end()) { //已经存在
            if(i > 0)
                pre[i] = max(location[a[i]] + 1, pre[i - 1]);
            location[a[i]] = i;
            st[i][0] = i - pre[i] + 1;
        }
        else {
            if(i > 0)
                pre[i] = pre[i - 1];
            st[i][0] = i - pre[i] + 1;
            location.insert(make_pair(a[i], i));
        }
    }
    // for (int i = 0; i < n; i++)
    //     cout << pre[i];
    // cout << endl;
    for (int i = 1; i <= floor(log2(n)); i++)
    {
        for (int j = 0; j + (1 << i) - 1 < n; j++)
        {
            st[j][i] = max(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
        }
        }
    while(m--) {
        int l, r;
        scanf("%d%d", &l, &r);
        auto bound = upper_bound(pre.begin() + l, pre.begin() + r + 1, l); // 大于l的第一个
        // cout << "bound quals" << bound - pre.begin() << endl;
        if(bound == pre.begin() + r + 1) {
            printf("%d\n", r - l + 1);
        }else {
            int bound_location = bound - pre.begin() - 1; // l~bound_location均为前半段
            // cout << "bound_location equals" << bound_location << endl;
            int ans = bound_location - l + 1;
            int max_length = r - bound_location;
            int binary_length = log2(max_length);
            int st_ans = max(st[bound_location + 1][binary_length], st[r - (1 << binary_length) + 1][binary_length]);
            ans = max(ans, st_ans);
            printf("%d\n", ans);
        }
    }
    return 0;
}