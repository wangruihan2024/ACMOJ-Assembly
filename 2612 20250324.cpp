#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;
constexpr int SIZE = 3e4 + 5;

int totalcnt, n;
bool ex[SIZE], vis[SIZE];

struct Node {
  int son[2];
  int fail;
  bool last;
} tr[SIZE];

void insert(string s) {
  int u = 0;
  for (int i = 0; i < (int)s.size(); i++) {
    int &son = tr[u].son[s[i] - 48];
    if (!tr[u].son[s[i] - 48]) {
        tr[u].son[s[i] - 48] = ++totalcnt;
        u = totalcnt;
    }else
        u = tr[u].son[s[i] - 48];
    
  }
  tr[u].last = true;
}

void build() {
  queue<int> q;
  for (int i = 0; i < 2; i++)
    if (tr[0].son[i]) {
      q.push(tr[0].son[i]);
    }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = 0; i < 2; i++) {
      if (tr[u].son[i]) { 
        q.push(tr[u].son[i]);
        int tmp = tr[u].fail;
        while(tmp > 0 && tr[tmp].son[i] <= 0)
            tmp = tr[tmp].fail;
        if(tr[tmp].son[i] <= 0)
            tr[tr[u].son[i]].fail = 0;
        else {
            tr[tr[u].son[i]].fail = tr[tmp].son[i];
            if(tr[tr[tmp].son[i]].last)
                tr[tr[u].son[i]].last = true;
        }
      } else
        tr[u].son[i] = tr[tr[u].fail].son[i];
    }
  }
}

void dfs(int u) {
    ex[u] = true;
    for (int i = 0; i < 2; i++) {
        if(ex[tr[u].son[i]]) {
            cout << "YES" << endl;
            exit(0);
        }else if(!tr[tr[u].son[i]].last && !vis[tr[u].son[i]]) {
            vis[tr[u].son[i]] = true;
            dfs(tr[u].son[i]);
        }
    }
    ex[u] = false;
}

int main() {
    cin >> n;
    string p;
    for (int i = 1; i <= n; i++)
    {
        cin >> p;
        insert(p);
    }
    build();
    dfs(0);
    cout << "NO" << endl;
    return 0;
}
