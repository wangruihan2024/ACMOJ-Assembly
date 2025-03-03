#include <iostream>
using namespace std;
char *p1,*p2,buf[100000];
#define nc() (p1==p2 && (p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
int read()
{
    int x=0,f=1;
    char ch=nc();
    while(ch<48||ch>57)
    {
        if(ch=='-')
            f=-1;
        ch=nc();
    }
    while(ch>=48&&ch<=57)
        x=x*10+ch-48,ch=nc();
    return x*f;
}
int ans(int n) {
    int lower_bit = 0, upper_bit = 0, read_in, mid;
    for (int i = 0; i < n; i++) {
        read_in = read();
        upper_bit ^= (lower_bit & read_in);
        lower_bit ^= read_in;
        mid = upper_bit & lower_bit;
        upper_bit &= ~mid;
        lower_bit &= ~mid;
    }
    return lower_bit & ~upper_bit;
}
int main() {
    int n;
    n = read();
    cout << ans(n) << endl;
    return 0;
}