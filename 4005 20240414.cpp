#include <iostream>
#include <cmath>
using namespace std;
struct extendedEuclid {
    long long x_, y_, r_;
};
pair<long long, long long> factorize(long long n) {
    for (long long p = 2; p * p <= n; ++p) {
        if (n % p == 0) 
            return {p, n / p};
    }
    // cout << "n cannot be factorized" << endl;
}
// a*x + b*y = r = gcd(a, b)
extendedEuclid extended_Euclid(long long a, long long b) {
    if (b == 0) 
        return {1, 0, a};
    extendedEuclid result = extended_Euclid(b, a % b);
    return {result.y_, result.x_ - (a / b) * result.y_, result.r_};
}
long long modPow(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) 
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return result;
}

int main() {
    long long y, n, e, flag;
    cin >> y >> n >> e >> flag;
    pair<long long, long long> f_ = factorize(n);
    long long phi = (f_.first - 1) * (f_.second - 1);
    extendedEuclid result = extended_Euclid(e, phi);
    long long d = result.x_;
    d = (d % phi + phi) % phi; //注意负数！！！
    long long x_result = modPow(y, d, n);
    if (flag == 0) {
        cout << x_result << endl;
    } else {
        cout << x_result << " " << d << endl;
    }
    return 0;
}