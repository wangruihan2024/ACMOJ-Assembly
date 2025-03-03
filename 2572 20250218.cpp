#include <iostream>
#include <cmath>
using namespace std;
int a, b, n;
int main() {
    scanf("%d%d%d", &a, &b, &n);
    int h1 = ceil(log2(n));
    int h2 = floor(log2(n));
    int num[1005][1005] = {};
    int sup[1005][1005][9] = {};
    int inf[1005][1005][9] = {};
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            scanf("%d", &num[i][j]);
            sup[i][j][0] = num[i][j];
            inf[i][j][0] = num[i][j];
        }
    }
    for(int k = 1; k <= h1; k++) {
        for(int i = 0; i + (1 << k) <= a; i++) {
            for(int j = 0; j + (1 << k) <= b; j++) {
                sup[i][j][k] = max(sup[i][j][k - 1], max(sup[i][j + (1 << (k - 1))][k - 1], max(sup[i + (1 << (k - 1))][j][k - 1], sup[i + (1 << (k - 1))][j + (1 << (k - 1))][k - 1])));
                inf[i][j][k] = min(inf[i][j][k - 1], min(inf[i][j + (1 << (k - 1))][k - 1], min(inf[i + (1 << (k - 1))][j][k - 1], inf[i + (1 << (k - 1))][j + (1 << (k - 1))][k - 1])));
            }
        }
    }
    // cout << "ceil is " << h1 << ", floor is " << h2 << endl;
    // for (int k = 0; k <= h2; k++) {
    //     cout << "k = " << k << endl;
    //     for(int i = 0; i + n - 1 < a; i++) {
    //         for(int j = 0; j + n - 1 < b; j++) {
    //             cout << sup[i][j][k] << "vs" << inf[i][j][k] << endl;
    //         }
    //     }
    // }
    int ans = 1e9 + 7;
    for(int i = 0; i + n - 1 < a; i++) {
        for (int j = 0; j + n - 1 < b; j++) {
            int tmp_min = min(inf[i][j][h2], min(inf[i + n - (1 << h2)][j][h2], min(inf[i][j + n - (1 << h2)][h2], inf[i + n - (1 << h2)][j + n - (1 << h2)][h2])));
            int tmp_max = max(sup[i][j][h2], max(sup[i + n - (1 << h2)][j][h2], max(sup[i][j + n - (1 << h2)][h2], sup[i + n - (1 << h2)][j + n - (1 << h2)][h2])));
            ans = min(ans, tmp_max - tmp_min);
        }
    }
    printf("%d\n", ans);
    return 0;
}