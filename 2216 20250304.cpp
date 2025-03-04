#include <iostream>
#include <vector>
using namespace std;
int n, q;
long long m;
vector<long long> a;
long long mul_tag[100005 << 2], add_tag[100005 << 2], sum[100005 << 2];
void push_up(long long p) {
    sum[p] = sum[p << 1] + sum[(p << 1) + 1];
    sum[p] = sum[p] % m;
}
void push_down(int l, int r, int p) {
    int mid = l + ((r - l) >> 1), ls = p << 1, rs = ls + 1;
    if(mul_tag[p] != 1) {
        mul_tag[ls] = mul_tag[ls] * mul_tag[p] % m;
        mul_tag[rs] = mul_tag[rs] * mul_tag[p] % m;
        add_tag[ls] = add_tag[ls] * mul_tag[p] % m;
        add_tag[rs] = add_tag[rs] * mul_tag[p] % m;
        sum[ls] = sum[ls] * mul_tag[p] % m;
        sum[rs] = sum[rs] * mul_tag[p] % m;
        mul_tag[p] = 1;
    }
    if(add_tag[p]) {
        add_tag[ls] = (add_tag[ls] + add_tag[p]) % m;
        add_tag[rs] = (add_tag[rs] + add_tag[p]) % m;
        sum[ls] = (sum[ls] + add_tag[p] * (mid - l + 1) % m) % m;
        sum[rs] = (sum[rs] + add_tag[p] * (r - mid) % m) % m;
        add_tag[p] = 0;
    }
    return;
}
void build(int l, int r, int p) {
    mul_tag[p] = 1;
    if(l == r) {
        sum[p] = a[l];
        return;
    }
    int mid = l + ((r - l) >> 1);
    build(l, mid, p << 1);
    build(mid + 1, r, (p << 1) + 1);
    push_up(p);
}
void add(int lg, int rg, int l, int r, int p, long long k) {
    if(lg <= l && rg >= r) {
        sum[p] = (sum[p] + k * (r - l + 1)) % m;
        add_tag[p] = (add_tag[p] + k) % m;
        return;
    }
    int mid = l + ((r - l) >> 1);
    push_down(l, r, p);
    if(lg <= mid)
        add(lg, rg, l, mid, (p << 1), k);
    if(mid < rg)
        add(lg, rg, mid + 1, r, (p << 1) + 1, k);
    push_up(p);
}
void multiply(int lg, int rg, int l, int r, int p, long long k) {
    if(lg <= l && rg >= r) {
        sum[p] = sum[p] * k % m;
        add_tag[p] = add_tag[p] * k % m;
        mul_tag[p] = mul_tag[p] * k % m;
        return;
    }
    push_down(l, r, p);
    int mid = l + ((r - l) >> 1);
    if(lg <= mid)
        multiply(lg, rg, l, mid, p << 1, k);
    if(mid < rg)
        multiply(lg, rg, mid + 1, r, (p << 1) + 1, k);
    push_up(p);
}
long long getsum(int lg, int rg, int l, int r, int p) {
    if(lg <= l && rg >= r) {
        return sum[p] % m;
    }
    int mid = l + ((r - l) >> 1);
    long long ans = 0;
    push_down(l, r, p);
    if(lg <= mid)
        ans = (ans + getsum(lg, rg, l, mid, p << 1)) % m;
    if(mid < rg)
        ans = (ans + getsum(lg, rg, mid + 1, r, (p << 1) + 1)) % m;
    return ans % m;
}
int main() {
    cin >> n >> q >> m;
    a.resize(n);
    for (int i = 0; i < n; i++) 
        cin >> a[i];
    int mode, x, y;
    long long k;
    build(0, n - 1, 1);
    while(q--) {
        cin >> mode;
        switch(mode) {
            case 1:
                cin >> x >> y >> k;
                x--;
                y--;
                multiply(x, y, 0, n - 1, 1, k);
                break;
            case 2:
                cin >> x >> y >> k;
                x--;
                y--;
                add(x, y, 0, n - 1, 1, k);
                break;
            case 3:
                cin >> x >> y;
                x--;
                y--;
                cout << getsum(x, y, 0, n - 1, 1) << endl;
                break;
        }
    }
        return 0;
}