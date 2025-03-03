#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const long long int MOD = 1e9 + 7;
int n, m;
int pivot;// 主元的个数
long long int scalar; 
long long int find_mod(long long int divisor, long long int exp) { // 要计算/divisor <=> * divisor^(mod - 2)
    long long int result = 1;
    divisor %= MOD;
    while(exp >= 1) {
        if(exp % 2 == 1)
            result = (result * divisor) % MOD;
        divisor = divisor * divisor % MOD;
        exp /= 2;
    }
    return result;
}
int elimination(vector<vector<long long int>> &p) {
    pivot = 0;
    scalar = 1;
    int col = 0, max_row;
    for (; col < m; col++) {
        max_row = pivot;
        for (int i = pivot + 1; i < m; i++)
            if(abs(p[i][col]) > abs(p[max_row][col]))
                max_row = i;
        if(p[max_row][col] == 0)
            continue;
        if(max_row != pivot) {
            if(abs(max_row - pivot) % 2 == 1)
                scalar = -scalar;
            for (int i = col; i < m; i++)
                swap(p[pivot][i], p[max_row][i]);
        }    
        long long int inverse_mod = find_mod(p[pivot][col], MOD - 2);
        scalar = scalar * inverse_mod % MOD;
        for (int i = col; i < m; i++)
            p[pivot][i] = p[pivot][i] * inverse_mod % MOD;
        for (int i = 0; i < m; i++) {
            if(i != pivot) {
                long long int factor = p[i][col];
                for (int j = col; j < m; j++)
                    p[i][j] = (p[i][j] - factor * p[pivot][j] % MOD + MOD) % MOD;
            }
        }
        pivot++;
    }
    return pivot;
}
/*long long int determinant(vector<vector<long long int>> &p) {
    elimination(p);
    if(pivot != m)
        return 0;
    for (int i = 0; i < m; i++)
        scalar = scalar * p[i][i] % MOD;
    return scalar;
}*/
int main() {
    cin >> n >> m;
    vector<vector<vector<long long int>>> a(n, vector<vector<long long int>>(m, vector<long long int>(m, 0)));
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < m; j++) 
            for (int k = 0; k < m; k++) 
                cin >> a[i][j][k];
    vector<int> num(n);
    for (int i = 0; i < n; i++) {
        num[i] = i + 1;
        
    }
        
    /*elimination(a[0]);
    cout << "---matrix after elimination of 1" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            cout << a[0][i][j] << " ";
        }
        cout << endl;
    }
    cout << "---elimination ends" << endl;*/
    /*cout << "---cout the determinant of each matrix" << endl;
    for (int i = 0; i < n; i++)
        cout << i << " : " << elimination(a[i]) << endl;
    cout << "---determinant ends" << endl;*/
    auto it = std::unique(num.begin(), num.end(), [&](int i, int j)
                          { return elimination(a[i - 1]) == elimination(a[j - 1]); });
    num.erase(it, num.end());
    cout << num.size() << endl;
    for (auto it = num.begin(); it != num.end(); it++)
        cout << *it << " ";
    cout << endl;
}