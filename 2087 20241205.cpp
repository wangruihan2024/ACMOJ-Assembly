#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
const long long int MOD = 998244353;
int n;
long long int a[305][305];
long long int find_pow(long long int base, long long int exp) {
    long long int result = 1;
    base = base % MOD;
    while(exp >= 1) {
        if(exp % 2 == 1) {
            result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
        exp /= 2;
    }
    return result;
}
int main() {
    cin >> n; 
    for (int i = 0; i < n; i++)
        for(int j = 0; j <= n; j++)
            cin >> a[i][j];
    int col = 0, pivot = 0;
    int max_row;
    for (; col < n; col++) {
        max_row = pivot;
        for (int j = pivot + 1; j < n; j++) 
            if(abs(a[max_row][col]) < abs(a[j][col]))
                max_row = j;
        if(a[max_row][col] == 0)
            continue;
        if(max_row != pivot) 
            for (int j = col; j <= n; j++)
                swap(a[max_row][j], a[pivot][j]);
        long long int inverse_pow = find_pow(a[pivot][col], MOD - 2);
        for (int j = col; j <= n; j++)
            a[pivot][j] = (a[pivot][j] * inverse_pow) % MOD;
        for(int i = 0; i < n; i++) 
            if(i != pivot) {
                int factor = a[i][col];
                for(int j = col ; j <= n; j++)
                    a[i][j] = (a[i][j] - factor * a[pivot][j] % MOD + MOD) % MOD;
            }
        pivot++;
    }
    for (int i = pivot; i < n; i++)
        if(abs(a[i][n]) != 0) {
            cout << "No Solution" << endl;
            return 0;
        }
    if(pivot != n) {
        cout << "No Unique Solution" << endl;
        return 0;
    }
    for (int i = 0; i < n; i++)
        cout << a[i][n] << " ";
    return 0;
}