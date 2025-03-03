#include<bits/stdc++.h>
using namespace std;
int n,m,ans = 0;//n个同学 ，m个位置，ans是泄露的次数
int a[2005] , b[2005] , s[2005][6];//m[i][0]是座位空闲的最早时间点 1是正在占用的人的ai，3是是否被加倍过
int main(){
    cin >> n >> m;
    for(int i = 0 ; i < n ; i++){
        cin >> a[i] >> b[i];
    }
    for(int i = 0 ; i < n ; i++){//安排第i个人
        int flag = 0;
        if(s[1][0] < a[i] && s[0][0] < a[i]){
            s[0][0] = b[i];
            s[0][1] = a[i];
            s[0][3] = 0;
            flag = 1;
        }
        if(flag == 0)
        for(int j = 1 ; j <= m-2 ; j++){
            if(s[j][0] < a[i] && s[j-1][0] < a[i] && s[j+1][0] < a[i]){//左右位置都没人
                    s[j][0] = b[i];
                    s[j][1] = a[i];
                    s[j][3] = 0;
                    break;
                    flag = 1;
            }
        }
        if(flag == 0)
        if(s[m-2][0] < a[i] && s[m-1][0] < a[i]){
            s[m-1][0] = b[i];
            s[m-1][1] = a[i];
            s[m-1][3] = 0;
            flag = 1;
        }
        if(flag == 0){//不存在两边都没人的位置
            for(int j = 0 ; j <= m-1 ; j++){
                if(s[j][0] < a[i]){
                    s[j][0] = b[i];
                    s[j][1] = a[i];
                    s[j][3] = 0;
                    if((j >=1 && s[j-1][0] >= a[i]) || (j <= (m-2) && s[j+1][0] >= a[i])){
                        s[j][0] = 2*s[j][0] - s[j][1];
                    }
                    if(j>= 1 && s[j-1][0] >= a[i] && s[j-1][3] == 0){
                        s[j-1][3] = 1;
                        s[j-1][0] = 2*s[j-1][0] - s[j-1][1];
                    }
                    if(j <= (m-2) && s[j+1][0] >= a[i] && s[j+1][3] == 0){
                        s[j+1][3] = 1;
                        s[j+1][0] = 2*s[j+1][0] - s[j+1][1];
                    }
                    flag = 1;
                    break;
                }
            }
        }
        if(flag == 0){
            ans++;
        }
    }
    cout << ans << endl;
    return 0;
}