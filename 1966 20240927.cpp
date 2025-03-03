#include<bits/stdc++.h>
using namespace std;
int read(){
    char ch = 0;
    int res =0;
    while(ch < '0' || ch > '9')
        ch = getchar();
    while(ch >= '0' && ch <= '9'){
        res = res * 10 + ch - '0';
        ch = getchar();
    }
    return res;
}
bool year(int y){//闰年1 平年0
    if((y % 4 ==0 && y % 100 != 0) || y % 400 ==0 )
        return true;
    return false;
}
int daysfrombegin(int y, int m, int d){//当前日期到1，1的日子
    int day = 0;
    int mon[20] = {0, 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31};
    for(int i = 1 ; i <= m-1 ; i++){
        day += mon[i];
    }
    day += d;
    if(year(y) && ((m >= 3) || (m == 2 && d == 29))) 
        day += 1;
    return day;
}
int year(int a , int b){//两年之间差的天数
    int day = 0;
    for(int i = a ; i <= b-1 ; i++){
        day += 365;
        if(year(i))
            day++;
    }
    return day;
}
int main(){
//    char s1 , s2;
    int T;
    cin >> T;
    while(T--){
//        int y1,y2,m1,m2,d1,d2;
//        scanf("%d-%d-%d" , y1 , m1 , d1);
//        scanf("%d-%d-%d" , y2 , m2 , d2);
        
        int y1 = read();
        int m1 = read();
        int d1 = read();
        int y2 = read();
        int m2 = read();
        int d2 = read();
        if(y1 > y2){
            swap(y1 , y2);
            swap(m1 , m2);
            swap(d1 , d2);
        }else if(y1 == y2 && m1 > m2){
            swap(m1 , m2);
            swap(d1 , d2);
        }else if(y1 == y2 && m1 == m2 && d1 > d2){
            swap(d1 , d2);
        }
        int day1 = daysfrombegin(y1 , m1 , d1);
        int day2 = daysfrombegin(y2 , m2 , d2);
      // if(m1 == m2 && y1 == y2)
            cout << year(y1 , y2) - day1 + day2 << endl;
   //    else 
   //        cout << year(y1 , y2) - day1 + day2-1;
    }
    return 0;
}