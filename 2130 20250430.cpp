#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
constexpr int MAXN = 1e6 + 5;
int n, m;
int block_size;
long long distinct = 0;
vector<int> a;
int cnt[MAXN];
struct Query {
    int time, l, r, id;
};
struct Upd {
    int pos, old_val, new_val;
};
vector<Query> queries;
vector<Upd> updates;
bool cmp(const Query &q1, const Query &q2) {
    if(q1.l / block_size != q2.l / block_size)
        return q1.l / block_size < q2.l / block_size;
    if (q1.r / block_size != q2.r / block_size)
        return q1.r / block_size < q2.r / block_size;
    return q1.time < q2.time;
}
void add(int val) {
    if(!cnt[val])
        distinct++;
    cnt[val]++;
}
void remove(int val) {
    cnt[val]--;
    if(!cnt[val])
        distinct--;
}
void update(int pos, int val, int current_l, int current_r) {
    if (current_l <= pos && pos <= current_r) {
        remove(a[pos]);
        add(val);
    }
    a[pos] = val;
}
int main() {
    cin >> n >> m;
    a.resize(n);
    block_size = pow(n, 2.0 / 3.0);
    if (!block_size) block_size = 1;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    vector<int> backup = a;
    for (int i = 0; i < m; i++) {
        char cmd;
        cin >> cmd;
        if(cmd == 'Q') {
            int l, r;
            cin >> l >> r;
            queries.push_back({(int)updates.size(), l - 1, r - 1, (int)queries.size()});
        }else {
            int pos, val;
            cin >> pos >> val;
            updates.push_back({pos - 1, backup[pos - 1], val});
            backup[pos-1] = val;
        }
    }
    vector<long long> answer((int)queries.size(), 0);
    sort(queries.begin(), queries.end(), cmp);
    int current_l = 0, current_r = -1, current_time = 0;
    for(const auto &q : queries) { 
        while (current_time < q.time) {
            update(updates[current_time].pos, updates[current_time].new_val, current_l, current_r);
            current_time++;
        }
        while (current_time > q.time) {
            current_time--;
            update(updates[current_time].pos, updates[current_time].old_val, current_l, current_r);
        }
        while (current_l > q.l) {
            add(a[--current_l]);
        }
        while (current_r < q.r) {
            add(a[++current_r]);
        }
        while (current_l < q.l) {
            remove(a[current_l++]);
        }
        while (current_r > q.r) {
            remove(a[current_r--]);
        }
        answer[q.id] = distinct;
    }
    for(auto num : answer)
        cout << num << endl;
}