#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;
constexpr int SIZE = 1e3 + 5;

int n, k, totalcnt = 1;
int dp[SIZE][SIZE];

struct Node {
  int son[4];
  int fail;
  int idx;
  int score;
  Node() {
      fail = score = idx = 0;
      memset(son, 0, sizeof(son));
  } 
} tr[SIZE];

void insert(const string &s, int v) {
  int u = 0;
  for (int i = 0; i < (int)s.size(); i++) {
    if (!tr[u].son[s[i] - 'A']) {
        tr[u].son[s[i] - 'A'] = totalcnt++;
    }
    u = tr[u].son[s[i] - 'A'];
  }
  tr[u].score += v;
}

void build() {
  queue<int> q;
  for (int i = 0; i < 4; i++)
    if (tr[0].son[i]) {
        tr[tr[0].son[i]].fail = 0;
        q.push(tr[0].son[i]);
    }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = 0; i < 4; i++) {
        if (tr[u].son[i]) {
            int v = tr[u].son[i];
            int f = tr[u].fail;
            while (f && !tr[f].son[i]) 
                f = tr[f].fail;
            if (tr[f].son[i]) 
                tr[v].fail = tr[f].son[i];
            else 
                tr[v].fail = 0;
            tr[v].score += tr[tr[v].fail].score;
            q.push(v);
        }
    }
  }
}

int main() {
    cin >> n >> k;
    string p;
    int v;
    for (int i = 1; i <= n; i++)
    {
        cin >> p >> v;
        insert(p, v);
    }
    build();
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j < totalcnt; j++) {
            dp[i][j] = INT_MIN;
        }
    }
    //不可以用memset！！！
    dp[0][0] = 0;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < totalcnt; j++) {
            if(dp[i][j] == INT_MIN)
                continue;
            for (int dir = 0; dir < 4; dir++) {
                if (tr[j].son[dir]) {
                    dp[i + 1][tr[j].son[dir]] = max(dp[i + 1][tr[j].son[dir]], dp[i][j] + tr[tr[j].son[dir]].score);
                } else {
                    int failNode = tr[j].fail;
                    while (failNode && !tr[failNode].son[dir]) failNode = tr[failNode].fail;
                    if (tr[failNode].son[dir]) {
                        tr[j].son[dir] = tr[failNode].son[dir];
                        dp[i + 1][tr[j].son[dir]] = max(dp[i + 1][tr[j].son[dir]], dp[i][j] + tr[tr[j].son[dir]].score);
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int j = 0; j < totalcnt; j++) {
        ans = max(ans, dp[k][j]);
    }
    cout << ans << endl;
    return 0;
}
