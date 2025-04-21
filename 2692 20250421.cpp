#include <iostream>
using namespace std;
constexpr int MAXN = 2e5 + 10;
int m, n;
struct treap_node {
    int ls, rs;
    int val;
    int siz;
    int lev;
}pool[MAXN];
int treap_tail = 0, root = 0;
int new_treap_node(int x) { // 返回编号
    treap_tail++;  
    pool[treap_tail] = {0, 0, x, 1, rand()};
    return treap_tail;
}
void push_up(int p) {
    pool[p].siz = pool[pool[p].ls].siz + pool[pool[p].rs].siz + 1;
}
void zig(int &p) { // 右旋
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
void insert(int &p, int pos, int x) {
    if(p == 0) {
        p = new_treap_node(x);
        return;
    }
    int leftSize = pool[pool[p].ls].siz;
    if (pos <= leftSize) {
        insert(pool[p].ls, pos, x);
        if (pool[pool[p].ls].lev > pool[p].lev)
            zig(p);
    } else {
        insert(pool[p].rs, pos - leftSize - 1, x);
        if (pool[pool[p].rs].lev > pool[p].lev)
            zag(p);
    }
    push_up(p);
}
void remove(int &p, int pos) {
    if (!p) return;
    
    int leftSize = pool[pool[p].ls].siz;
    if (pos < leftSize) {
        remove(pool[p].ls, pos);
        if (pool[p].ls && pool[pool[p].ls].lev > pool[p].lev)
            zig(p);
    } else if (pos > leftSize) {
        remove(pool[p].rs, pos - leftSize - 1);
        if (pool[p].rs && pool[pool[p].rs].lev > pool[p].lev)
            zag(p);
    } else {
        if (!pool[p].ls || !pool[p].rs) {
            p = pool[p].ls | pool[p].rs;
        } else {
            if (pool[pool[p].ls].lev > pool[pool[p].rs].lev) {
                zig(p);
                int newLeft = pool[pool[p].ls].siz;
                remove(pool[p].rs, pos - newLeft - 1);
            } else {
                zag(p);
                remove(pool[p].ls, pos);
            }
        }
    }
    if(p)
        push_up(p);
}
// int kth(int p, int x) {
//     while(true) {
//         if (x == pool[pool[p].ls].siz + 1) {
//             return pool[p].val;
//         } else if (x <= pool[pool[p].ls].siz) {
//             p = pool[p].ls;
//         } else {
//             x -= pool[pool[p].ls].siz + 1;
//             p = pool[p].rs;
//         }
//     }
        
// }
void inorder_print(int p) {
    if(p == 0)
        return;
    inorder_print(pool[p].ls);
    cout << pool[p].val << " ";
    inorder_print(pool[p].rs);
}
int main() {
    // srand(time(0));
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        insert(root, i, tmp);
    }
    for(int i = 0; i < m; i++) {
        int mode;
        cin >> mode;
        if(mode == 1) {
            int x, y;
            cin >> x >> y;
            insert(root, x, y);
            // cout << endl;
            // inorder_print(root);
        }else {
            int x;
            cin >> x;
            remove(root, x - 1);
            // cout << endl;
            // inorder_print(root);
        }
    }
    // cout << endl;
    // cout << "----";
    inorder_print(root);
    return 0;
}