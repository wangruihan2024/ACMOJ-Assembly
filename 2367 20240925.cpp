#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
	cin >> n;
	int m = n-1;
	char c = 'A';
	for(int i = 1 ; i <= n ; i++){
		for(int j = 1 ; j <= m ; j++)
			cout << " ";
		m--;
		for(int j = 2*i-1 ; j >= 1 ; j--){
			cout<<c;
			c = (c + 1 - 'A') % 26 + 'A';
		}
		cout<<endl;
	}
	return 0;
} 
