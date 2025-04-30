#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
struct Query {
    int time, l, r, idx;
};
struct Update {
    int pos, old_val, new_val;
};
int block_size;
vector<int> arr;
vector<int> cnt;
long long res = 0;
bool cmp(const Query &a, const Query &b) {
    if (a.l / block_size != b.l / block_size)
        return a.l / block_size < b.l / block_size;
    if (a.r / block_size != b.r / block_size)
        return a.r / block_size < b.r / block_size;
    return a.time < b.time;
}
void add(int val) {
    res += 2 * cnt[val] + 1;
    cnt[val]++;
}
void remove(int val) {
    res -= 2 * cnt[val] - 1;
    cnt[val]--;
}
void apply_update(int pos, int val, int current_l, int current_r) {
    if (current_l <= pos && pos <= current_r) {
        remove(arr[pos]);
        add(val);
    }
    arr[pos] = val;
}
int main() {
    int N, M;
    cin >> N >> M;
    arr.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> arr[i];
    }
    vector<int> backup = arr;
    vector<Query> queries;
    vector<Update> updates;
    for (int i = 0; i < M; ++i) {
        char cmd;
        cin >> cmd;
        if (cmd == 'Q') {
            int L, R;
            cin >> L >> R;
            queries.push_back({(int)updates.size(), L-1, R-1, (int)queries.size()});
        } else {
            int P, X;
            cin >> P >> X;
            updates.push_back({P-1, backup[P-1], X});
            backup[P-1] = X;
        }
    }
    block_size = pow(N, 2.0/3.0);
    if (block_size == 0) block_size = 1;
    sort(queries.begin(), queries.end(), cmp);
    int current_l = 0, current_r = -1, current_time = 0;
    int max_val = *max_element(arr.begin(), arr.end());
    cnt.assign(max_val + 1, 0);
    vector<long long> ans(queries.size());
    for (const auto &q : queries) {
        while (current_time < q.time) {
            apply_update(updates[current_time].pos, updates[current_time].new_val, current_l, current_r);
            current_time++;
        }
        while (current_time > q.time) {
            current_time--;
            apply_update(updates[current_time].pos, updates[current_time].old_val, current_l, current_r);
        }
        while (current_l > q.l) {
            add(arr[--current_l]);
        }
        while (current_r < q.r) {
            add(arr[++current_r]);
        }
        while (current_l < q.l) {
            remove(arr[current_l++]);
        }
        while (current_r > q.r) {
            remove(arr[current_r--]);
        }
        ans[q.idx] = res;
    }
    for (auto num : ans) {
        cout << num << '\n';
    }
    return 0;
}