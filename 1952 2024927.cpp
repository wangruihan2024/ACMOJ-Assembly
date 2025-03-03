#include<bits/stdc++.h>
using namespace std;
int n;
int a[1005][1005];
int flag=0;//flag=0 向上 flag=1向下
int c=1;//从1开始
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        if(flag == 0){
            int j = i;
            int k = n;
            while(j >= 1){
                a[j][k] = c;
                j--;
                k--;
                c++;
            }
            flag = 1- flag;
        }else{
            int j = 1;
            int k = n - i + 1;
            while(k <= n){
                a[j][k] = c;
                j++;
                k++;
                c++;
            }
            flag = 1- flag;
        }
    }
    for(int i = 2 ; i <= n ; i++){
        if(flag == 0){
            int j = n;
            int k = n + 1 -i;
            while(k >= 1){
                a[j][k] = c;
                j--;
                k--;
                c++;
            }
            flag = 1- flag;
        }else{
            int j = i;
            int k = 1;
            while(j <= n){
                a[j][k] = c;
                j++;
                k++;
                c++;
            }
            flag = 1- flag;
        }
    }
    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j <= n ; j++)
            printf("%9d" , a[i][j]);
        //    printf("%9d" , a[i][j]);
        cout<<endl;
    }
    return 0;
}
