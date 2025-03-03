#include <iostream>
#include <map>
using namespace std;
map<long long int, long long int> num;
long long int cnt = 0;
int main() {
    long long int a, b, c, d, temp;
    cin >> a >> b >> c >> d;
    for (int i = 1; i <= 1000; i++) {
        for (int j = 1; j <= 1000; j++) {
            temp = c * i * i + d * j * j;
            if(num.count(temp))
                num[temp]++;
            else
                num.insert(make_pair(temp, 1));
        }
    }
    for (int i = 1; i <= 1000; i++) {
        for (int j = 1; j <= 1000; j++) {
            temp = a * i * i + b * j * j;
            if(num.count(-temp))
                cnt += num[-temp];
        }
    }
    cout << cnt * 16 << endl;
}