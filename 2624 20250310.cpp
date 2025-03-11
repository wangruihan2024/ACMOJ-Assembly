#include <bits/stdc++.h>
#include <vector>
using namespace std;
int read(){
    char ch=0;
    int w=1,num=0;
    while(ch<'0' or ch>'9'){
        if(ch=='-') w=-1;
        ch=getchar();
    }
    while(ch>='0' and ch<='9'){
        num=num*10+(ch-'0');
        ch=getchar();
    }
    return num*w;
}
void write(int num){
    int top=0;
    int sta[65];
    do{
        sta[top++]=num%10;
        num/=10;
    }while(num);
    while(top) putchar(sta[--top]+'0');
}
int n, m;
int main() {
    n = read(), m = read();
    vector<int> arr(n + 1, 0), onecount(n + 1, 0);
    vector<vector<int>> st(n + 1, vector<int>(ceil(log2(n)) + 1, 0));
    for(int i = 1; i <= n; i++) {
        arr[i] = read();
        if(arr[i])
            onecount[i] = onecount[i - 1] + 1;
        else
            onecount[i] = onecount[i - 1];
        st[i][0] = i - 2 * onecount[i];
    }
    for(int i = 1; i <= floor(log2(n)); i++) {
        for(int j = 0; j + (1 << i) - 1 <= n; j++) {
            st[j][i] = max(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
        }
    }
    int l, r;
    for(int i = 1; i <= m; i++) {
        l = read(), r = read();
        int length = log2(r - l + 2);
            int inf = max(st[l - 1][length], st[r + 1 - (1 << length)][length]);
            int ans = inf + onecount[l - 1] + onecount[r] - (l - 1);
            write(ans);
        putchar('\n');
    }
    return 0;
}