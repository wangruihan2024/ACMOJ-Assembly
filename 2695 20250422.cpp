#include <iostream>

using namespace std;
constexpr int MAXN = 1e5 + 10;
int n, m;
int treap_tail, root;
struct treap_node{
    int ls, rs;
    int siz, val, key;
    int tag;
} node[MAXN];
int new_node(int p) {
    node[++treap_tail].val = p;
    node[treap_tail].key = rand();
    node[treap_tail].siz = 1;
    return treap_tail;
}
void push_up(int u) {
    node[u].siz = node[node[u].ls].siz + node[node[u].rs].siz + 1;
}
void push_down(int u) {
    if(!node[u].tag)
        return;
    swap(node[u].ls, node[u].rs);
    node[node[u].ls].tag ^= 1;
    node[node[u].rs].tag ^= 1;
    node[u].tag = 0;
}
void split(int u, int &l, int &r, int k) {
    if(!u) {
        l = r = 0;
        return;
    }
    push_down(u);
    if(node[node[u].ls].siz + 1 <= k) {
        l = u;
        split(node[u].rs, node[u].rs, r, k - node[node[u].ls].siz - 1);
    }else {
        r = u;
        split(node[u].ls, l, node[u].ls, k);
    }
    push_up(u);
}
int merge(int x, int y) {
    if(!x || !y)
        return x | y;
        if(node[x].key < node[y].key) {
            push_down(x);
            node[x].rs = merge(node[x].rs, y);
            push_up(x);
            return x;
        }else {
            push_down(y);
            node[y].ls = merge(x, node[y].ls);
            push_up(y);
            return y;
        }
}
void inorder(int p) {
    if(!p)
        return;
    push_down(p); // 调用p下一层的时候需要push_down
    inorder(node[p].ls);
    printf("%d ", node[p].val);
    inorder(node[p].rs);
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        root = merge(root, new_node(i));
    }
    while (m--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        int x, y, z;
        split(root, x, y, r);
        split(x, x, z, l - 1);
        node[z].tag ^= 1;
        root = merge(merge(x, z), y);
    }
    inorder(root);
    return 0;
}