#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int n, m;
int main() {
    scanf("%d%d", &n, &m);
    vector<int> a(n + 1, 0), onecount(n + 1, 0);
    vector<vector<int>> st(n + 1, vector<int>(ceil(log2(n)) + 1, 0));
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        if(a[i])
            onecount[i] = onecount[i - 1] + 1;
        else
            onecount[i] = onecount[i - 1];
        st[i][0] = i - 2 * onecount[i];
    }
    for(int i = 1; i <= floor(log2(n)); i++) {
        for(int j = 0; j + (1 << i) - 1 <= n; j++) {
            st[j][i] = max(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
        }
    }
    // for (int i = 0; i < 3; i++)
    //     cout << st[1][i] << " ";
    // cout << endl;
    while (m--)
    {
        int mode, l, r;
        scanf("%d%d%d", &mode, &l, &r);
        if (mode == 1)
        { // 不下降
            int length = log2(r - l + 2);
            int inf = max(st[l - 1][length], st[r + 1 - (1 << length)][length]);
            int ans = inf + onecount[l - 1] + onecount[r] - (l - 1);
            printf("%d\n", ans);
        }
        else
        { // 上升
            if((onecount[r] - onecount[l - 1]) == 0 || (onecount[r] - onecount[l - 1]) == (r - l + 1))
                printf("%d\n", 1);
            else {
                for (int i = r; i >= l; i--)
                {
                    if (onecount[i] - onecount[i - 1])
                    { // a[i] = 1
                        if ((onecount[i - 1] - onecount[l - 1]) < (i - l))
                        {
                            printf("%d\n", 2);
                            break;
                        }
                        else
                        {
                            printf("%d\n", 1);
                            break;
                        }
                    }
                }
            }
            
        }
        }
        return 0;
}