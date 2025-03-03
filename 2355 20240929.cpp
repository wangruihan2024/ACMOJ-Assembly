#include<bits/stdc++.h>
using namespace std;
//double moment;
//double min=0.00000001;
int m,times;//time to make question
double tim,D,E,F;//the time of question
double qu[500],point[50];//point指截止到ci的sum point[0]=H0
int c[50],a[50];
/*int fo(int j){
    if(j%1==0)
        return j-1;
    else
        return j/1;
}*/
int main(){
    cin>>m>>point[0]>>D>>E>>F;
    c[0]=0;
    for(int i=1;i<=m+1;i++){
        cin>>a[i]>>c[i];
    }
    if(point[0]<=F || point[0]>D || D<=F){
        cout<<"GIVEUP"<<endl;
        return 0;
    }
    for(int i=1;i<=m+1;i++){
        point[i]=point[i-1]+a[i]*(c[i]-c[i-1]);
        if(point[i]<=F){
            cout<<"GIVEUP"<<endl;
            return 0;
        }
        if(point[i]<=D && point[i]>F)
            continue;
        tim=(double)c[i-1]+(D-point[i-1])/a[i];
        while(point[i]>D){
            point[i]-=E;
            if(point[i]<=F){
                cout<<"GIVEUP"<<endl;
                return 0;
            }
            qu[times]=tim;
            tim+=E/a[i];
            times++;
        }
    }
//    cout<<sum;
/*   if(H0>D || D<=F || D<=(E+F) || sum<=E+F){
        cout<<"GIVEUP"<<endl;
        return 0;
    }*/
        cout<<"KEEPUP"<<endl;
        cout<<times<<endl;
        for(int i=0;i<times;i++)
            cout<<qu[i]<<endl;
    return 0;
}