#include <iostream>
using namespace std;
long long n, num;
bool jud(long long n) {  // 是2的次方
    if ((n & (n - 1)) == 0)
        return true;
    return false;
}
int low_dig(long long n) {
    if(n == 1)
        return 1;
    else
    for (int i = 50; i >= 1; i--) {
        if (n >= (1LL << i)) {
            return i;
        }
    }
}
long long cal(long long n) {
    if (n == 1) {
        return 1;
    } else if (jud(n) == true) {
        long long a = low_dig(n);
        return a * n / 2 + 1;
    } else {
        long long a = low_dig(n);
        a = 1LL << a;
   /*     if (n < a) {
            cout << "Why" << endl;
        }*/
        return cal(n - a) + n - a + cal(a);
    }
}
int main() {
    cin >> n;
    cout << cal(n) << endl;
    return 0;
}