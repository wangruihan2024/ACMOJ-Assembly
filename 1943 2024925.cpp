#include<bits/stdc++.h>
using namespace std;
int p,i;
int a[100005];
int main(){
	while(cin>>p){
		a[i]=p;
		i++;
	}
	for(int j=0;j<i;j++){
		cout<<a[i-1-j]<<endl;
	}
	return 0;
}
