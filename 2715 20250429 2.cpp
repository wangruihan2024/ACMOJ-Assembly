#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
constexpr int MAXN = 1e5 + 5;
struct Query {
    int l, r, idx;
};
int block_size;
vector<int> a;
vector<int> cnt;
long long current_ans;
vector<long long> answers;
bool compare(Query q1, Query q2) {
    if (q1.l / block_size != q2.l / block_size) {
        return q1.l / block_size < q2.l / block_size;
    }
    return q1.r < q2.r;
}
void add(int idx) {
    int num = a[idx];
    current_ans -= 1LL * cnt[num] * cnt[num];
    cnt[num]++;
    current_ans += 1LL * cnt[num] * cnt[num];
}
void remove(int idx) {
    int num = a[idx];
    current_ans -= 1LL * cnt[num] * cnt[num];
    cnt[num]--;
    current_ans += 1LL * cnt[num] * cnt[num];
}
void solve(vector<Query>& queries) {
    sort(queries.begin(), queries.end(), compare);
    int cur_l = 0, cur_r = -1;
    current_ans = 0;
    cnt.assign(MAXN, 0);
    for (Query q : queries) {
        while (cur_l > q.l) {
            cur_l--;
            add(cur_l);
        }
        while (cur_r < q.r) {
            cur_r++;
            add(cur_r);
        }
        while (cur_l < q.l) {
            remove(cur_l);
            cur_l++;
        }
        while (cur_r > q.r) {
            remove(cur_r);
            cur_r--;
        }
        answers[q.idx] = current_ans;
    }
}

int main() {
    int N, Q;
    cin >> N >> Q;
    a.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> a[i];
    }
    block_size = sqrt(N);
    vector<Query> queries(Q);
    for (int i = 0; i < Q; ++i) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].l--; 
        queries[i].r--;
        queries[i].idx = i;
    }
    answers.resize(Q);
    solve(queries);
	for (int i = 0; i < Q; i++)
		cout << answers[i] << endl;
	return 0;
}