#include<bits/stdc++.h>
using namespace std;
int p,i;
int a[100];
int main(){
    cout<<"program starts here"<<endl;
	while(cin>>p){
		a[i]=p;
		i++;
	}
	for(int j=0;j<i;j++){
		cout<<a[i-1-j]<<endl;
	}
	return 0;
}
