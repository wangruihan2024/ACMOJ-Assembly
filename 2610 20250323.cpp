#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;
constexpr int SIZE = 2e5 + 6;
int m;
struct Node {
  int son[26];
  int ans;
  int fail;
  int idx;
  void init() {
    memset(son, 0, sizeof(son));
    ans = idx = 0;
  }
} tr[SIZE];

int totalcnt;
int ans[SIZE], pidx;

vector<int> fialtr[SIZE]; 

void init() {
  totalcnt = pidx = 0;
  tr[0].init();
}

void insert(string s, int &idx) {
  int u = 0;
  for (int i = 0; s[i]; i++) {
    int &son = tr[u].son[s[i] - 'a'];
    if (!son) son = ++totalcnt, tr[son].init();
    u = son;
  }
  if (!tr[u].idx) tr[u].idx = ++pidx;  
  idx = tr[u].idx;
}

void build() {
  queue<int> q;
  for (int i = 0; i < 26; i++)
    if (tr[0].son[i]) {
      q.push(tr[0].son[i]);
      fialtr[0].push_back(tr[0].son[i]);  
    }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = 0; i < 26; i++) {
      if (tr[u].son[i]) {
        tr[tr[u].son[i]].fail = tr[tr[u].fail].son[i];
        fialtr[tr[tr[u].fail].son[i]].push_back(tr[u].son[i]);  
        q.push(tr[u].son[i]);
      } else
        tr[u].son[i] = tr[tr[u].fail].son[i];
    }
  }
}

void query(const string t) {
  int u = 0;
  for (char ch : t) {
    u = tr[u].son[ch - 'a'];
    tr[u].ans++;
  }
}

void dfs(int u) {
  for (int v : fialtr[u]) {
    dfs(v);
    tr[u].ans += tr[v].ans;
  }
  ans[tr[u].idx] = tr[u].ans;
}

string s;
int idx[SIZE];

int main() {
  init();
  cin >> s;
  cin >> m;
  for (int i = 1; i <= m; i++) {
    string p;
    cin >> p;
    insert(p, idx[i]);
    ans[i] = 0;
  }
  build();
  query(s);
  dfs(0);
  for (int i = 1; i <= m; i++) 
    cout << ans[idx[i]] << endl;
  return 0;
}
