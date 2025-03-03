#include<bits/stdc++.h>
using namespace std;
int m , n , num , ans; //num 学生数量
int xd[905] , yd[905];//学生的行列
char st[35] , a[905];//a学生方向
bool beside[905];//行列有没有人
int main(){
    cin >> m >> n;
    for(int i = 0 ; i < m ; i++){
        cin >> st;
        for(int j = 0 ; j < n ; j++){
            if(st[j] != '.'){
                xd[num] = i;
                yd[num] = j;
                a[num] = st[j];
                num++;
            }
        }
    }
    for(int i = 0 ; i < num ; i++){
        for(int j = i + 1 ; j <  num; j++){
            if(xd[i] == xd[j] || yd[i] == yd[j]){
                beside[i] = true;
                beside[j] = true;
            }
        }
    }
    for(int i = 0 ; i < num ; i++){
        if(beside[i] == false){
            cout << "-1" << endl;
            return 0;
        }
    }
    for(int i = 0 ; i < num ; i++){
        int count = 1;
        for(int j = 0 ; j < num ; j++){
            if((a[i] == 'W' && yd[i] == yd[j] && xd[j] < xd[i])||(a[i] == 'A' && xd[i] == xd[j] && yd[j] < yd[i])||(a[i] == 'S' && yd[i] == yd[j] && xd[j] > xd[i])||(a[i] == 'D' && xd[i] == xd[j] && yd[j] > yd[i])){
                count = 0;
            }
        }
        ans += count;
    }
    cout << ans << endl;
    return 0;
}