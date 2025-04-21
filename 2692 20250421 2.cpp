#include <iostream>
#include <vector>
using namespace std;
int n, m;
const int MAXN = 2e5 + 10; 
struct Node {
    int ls, rs;
    int val;
    int siz;
    int lev;
}pool[MAXN];
int root, treap_tail;
int new_treap_node(int val) {
    treap_tail++;
    pool[treap_tail].ls = pool[treap_tail].rs = 0;
    pool[treap_tail].val = val;
    pool[treap_tail].siz = 1;
    pool[treap_tail].lev = rand();
    return treap_tail;
}
void push_up(int u) {
    pool[u].siz = pool[pool[u].ls].siz + pool[pool[u].rs].siz + 1;
}
void split(int u, int pos, int &ls, int &rs, int add = 0) {
    if (!u) {
        ls = rs = 0;
        return;
    }
    int currentPos = add + pool[pool[u].ls].siz;
    if (currentPos < pos) {
        split(pool[u].rs, pos, pool[u].rs, rs, currentPos + 1);
        ls = u;
    } else {
        split(pool[u].ls, pos, ls, pool[u].ls, add);
        rs = u;
    }
    push_up(u);
}
int merge(int ls, int rs) {
    if (!ls) 
        return rs;
    if (!rs) 
        return ls;
    if (pool[ls].lev > pool[rs].lev) {
        pool[ls].rs = merge(pool[ls].rs, rs);
        push_up(ls);
        return ls;
    } else {
        pool[rs].ls = merge(ls, pool[rs].ls);
        push_up(rs);
        return rs;
    }
}
void insert(int pos, int val) {
    int ls, rs;
    split(root, pos, ls, rs);
    int new_node = new_treap_node(val);
    root = merge(merge(ls, new_node), rs);
}
void remove(int pos) {
    int ls, mid, rs;
    split(root, pos, ls, rs);
    split(rs, 1, mid, rs);
    root = merge(ls, rs);
}
void inorder(int u, vector<int> &res) {
    if (!u) 
        return;
    inorder(pool[u].ls, res);
    res.push_back(pool[u].val);
    inorder(pool[u].rs, res);
}
int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        insert(i, num);
    }
    for (int i = 0; i < m; ++i) {
        int mode;
        cin >> mode;
        if (mode == 1) {
            int x, y;
            cin >> x >> y;
            insert(x, y);
        } else if (mode == 2) {
            int x;
            cin >> x;
            remove(x - 1); 
        }
    }
    vector<int> result;
    inorder(root, result);
    for(int i = 0; i < result.size(); i++)
        cout << result[i] << " ";
    return 0;
}