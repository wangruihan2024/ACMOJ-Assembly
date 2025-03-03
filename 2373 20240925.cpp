#include<bits/stdc++.h>
using namespace std;
long long n,ans[100005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int x ,y;
		char z;
		cin >> z >> x >> y;
		if(z == '*'){
			 ans[i] = x*y;
		}else{
			 ans[i] = x+y;
		}
	}
	for(int i=1;i<=n;i++){
		cout<<ans[i]<<endl;
	}
} 
