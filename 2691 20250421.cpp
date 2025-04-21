#include <iostream>
#include <queue>
using namespace std;
constexpr int MAXN = 3e5 + 10;
int m, n;
int add_num[MAXN], ask_tim[MAXN];
struct treap_node {
    int ls, rs;
    int val;
    int cnt, siz, lev;
}pool[MAXN];
int treap_tail = 0, root = 0;
int new_treap_node(int x) { // 返回编号
    treap_tail++;
    pool[treap_tail] = {0, 0, x, 1, 1, rand()};
    return treap_tail;
}
void push_up(int p) {
    pool[p].siz = pool[pool[p].ls].siz + pool[pool[p].rs].siz + pool[p].cnt;
}
void zig(int &p) { // 左旋
    int tmp = pool[p].ls;
    pool[p].ls = pool[tmp].rs;
    pool[tmp].rs = p;
    push_up(p);
    push_up(tmp);
    p = tmp;
}
void zag(int &p) {
    int tmp = pool[p].rs;
    pool[p].rs = pool[tmp].ls;
    pool[tmp].ls = p;
    push_up(p);
    push_up(tmp);
    p = tmp;
}
void insert(int &p, int x) {
    if(p == 0) {
        p = new_treap_node(x);
        return;
    }
    if(x == pool[p].val) {
        pool[p].cnt++;
    }else if(x < pool[p].val) {
        insert(pool[p].ls, x);
        if(pool[pool[p].ls].lev > pool[p].lev)
            zig(p);
    }else {
        insert(pool[p].rs, x);
        if(pool[pool[p].rs].lev > pool[p].lev)
            zag(p);
    }
    push_up(p);
}
int kth(int p, int x) {
    if(pool[pool[p].ls].siz >= x)
        return kth(pool[p].ls, x);
    x -= pool[pool[p].ls].siz;
    if(pool[p].cnt >= x) {
        return pool[p].val;
    }
    return kth(pool[p].rs, x - pool[p].cnt);
}
int main() {
    scanf("%d%d", &m, &n);
    for(int i = 0; i < m; i++)
        scanf("%d", &add_num[i]);
    for(int i = 0; i < n; i++)
        scanf("%d", &ask_tim[i]);
    int ask_idx =0, add_idx = 0, k = 1;
    while (add_idx < m || ask_idx < n) {
        if (add_idx < m && (ask_idx >= n || add_idx < ask_tim[ask_idx])) {
            insert(root, add_num[add_idx]);
            add_idx++;
        } else {
            while(ask_idx < n && (add_idx >= m || ask_tim[ask_idx] <= add_idx)) {
                printf("%d\n", kth(root, k++));
                ask_idx++;
            }
        }
    }
    return 0;
}