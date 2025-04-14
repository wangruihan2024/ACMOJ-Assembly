#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
constexpr int MAXN = 1e6 + 5;
inline void read(int &x) {
    char ch = getchar();
    int f = 1;
    x = 0;
    while (!isdigit(ch) && ch != '-') ch = getchar();
    if (ch == '-') f = -1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
    x *= f;
}
int n, m;
vector<int> a;
vector<pair<pair<int, int>, int>> queries; // 问题的编号<->问题
vector<int> answer; // 问题的编号 <-> 答案
vector<int> bit; // 包含的最后一个的个数 （树状数组）
void update(int idx, int val) {
    while (idx <= n) {
        bit[idx] += val;
        idx += idx & -idx;
    }
}
int query(int idx) {
    int sum = 0;
    while (idx > 0) {
        sum += bit[idx];
        idx -= idx & -idx;
    }
    return sum;
}

int main() {
    read(n);
    a.resize(n + 1);  
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    read(m);
    queries.resize(m);
    answer.resize(m);
    for (int i = 0; i < m; i++) {
        int l, r;
        read(l);
        read(r);
        queries[i] = {{l, r}, i};
    }
    sort(queries.begin(), queries.end(), [](const auto &a, const auto &b) {
        return a.first.second < b.first.second;
    });
    bit.resize(n + 2, 0);
    map<int, int> last_pos; 
    int current_r = 0;
    int query_ptr = 0;
    for (int i = 1; i <= n && query_ptr < m; i++) {
        if (last_pos.count(a[i])) {
            update(last_pos[a[i]], -1);
        }
        update(i, 1);
        last_pos[a[i]] = i;
        while (query_ptr < m && queries[query_ptr].first.second == i) {
            int l = queries[query_ptr].first.first;
            int r = queries[query_ptr].first.second;
            int idx = queries[query_ptr].second;
            answer[idx] = query(r) - query(l - 1);
            query_ptr++;
        }
    }

    for (int i = 0; i < m; i++) {
        printf("%d\n", answer[i]);
    }
    return 0;
}