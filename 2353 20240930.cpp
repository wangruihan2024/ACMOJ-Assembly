#include<bits/stdc++.h>
using namespace std;
int m;
int search(int n){//找n的最小的大于1的约数
    if(n==1)
        return 1;
    else
    for(int i=2;i<=n;i++){
        if(n%i==0){
            return i;
            break;
        }
    }
}
bool odd(int n){//剩余偶数个mio有必胜 返回true
    if(n%2==0)
        return true;
    return false;
}
bool judge(int n){//质数返回false
    if(search(n)==n)
        return false;
    return true;
}
int re(int n,int i){//取n/i的剩余选项
    int remain=n/i;
    if(remain%i==0)
        return n-remain;
    return n-remain-1;
}
int main(){
    cin>>m;
    while(m--){
        bool res=false;
        int n;
        cin>>n;
        int n1=n;
        while(judge(n1)){
            int i=search(n1);
            while(n1%i==0)
                n1/=i;
            if(odd(re(n,i))){
                res=true;
                break;
            }
        }
        if(res)
            cout<<"Mio"<<endl;
        else
            cout<<"Noah"<<endl;
    }
    return 0;
}