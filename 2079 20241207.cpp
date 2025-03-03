#include <iostream>
#include <vector>
#include <map>
using namespace std;

const int MOD = 2;
const int MAX = 0x7fffffff;
int n, m;
int pivot = 0;
void elimination(vector<vector<int>>& a) {
    int col = 0, max_row;
    for (; col < n; col++) {
        max_row = pivot;
        for (int i = pivot + 1; i < n; i++) {
            if (a[i][col] > a[max_row][col]) {
                max_row = i;
            }
        }
        if (a[max_row][col] == 0) {
            continue;
        }
        if (max_row != pivot) {
            for (int i = 0; i <= n; i++) {
                swap(a[pivot][i], a[max_row][i]);
            }
        }
        for (int i = 0; i < n; i++) {
            if (i != pivot && a[i][col] != 0) {
                for (int j = col; j <= n; j++) {
                    a[i][j] ^= a[pivot][j]; 
                }
            }
        }

        pivot++;
    }
}

int min_operate(vector<vector<int>>& a) {
    map<int, int> pos;
    vector<int> free_column;
    vector<bool> flag(n, false);
    for (int row = 0; row < pivot; row++) {
        for (int i = 0; i < n; i++) {
            if(a[row][i] == 1) {
                pos.insert(make_pair(row, i));//第row行的主元位置是i
                flag[i] = true;
                break;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if(flag[i] == false) 
            free_column.push_back(i);
    }

    /*cout << "--this is the free column" << endl;
    for (auto it = free_column.begin(); it != free_column.end(); it++)
        cout << *it << " ";
    cout << endl;
    cout << "---free column end" << endl;*/

    int freeCount = free_column.size();//自由元个数
    int totalCombinations = (1 << freeCount);  
    int minOps = MAX;
    for (int state = 0; state < totalCombinations; state++) {
        vector<int> current(n, 0);
        int opCount_pre = 0;
        for (int i = 0; i < freeCount; i++) {
            current[free_column[i]] = (state >> i) & 1;
            if(current[free_column[i]] == 1)
                opCount_pre++;
        }
        /*cout << "---current数组如下：" << endl;
        for (int i = 0; i < n; i++)
            cout << current[i] << " ";
        cout << endl;
        cout << "---current ends" << endl;*/
        int opCount = 0;
        //bool valid = true;
        //cout << "the following is ans of each row" << endl;
        for (int i = 0; i < pivot; i++) {
            int ans = a[i][n];
            for (int j = 0; j < n; j++) 
                if (a[i][j] == 1 && j != pos[i]) 
                    ans ^= current[j];
            //cout << ans << " ";
            if (ans == 1) {
                opCount++;
            }
        }
        //cout << endl << "---the ans of each row end" << endl;
        // if(minOps == 20) {
        // cout << "2进制的和为：" << state << endl;
        // cout << "current中仅含自由元的解为" << endl;
        /*for (int i = 0; i < current.size(); i++)
            cout << current[i] << " ";
        cout << endl;*/
        //}
        minOps = min(minOps, opCount + opCount_pre); 
    }
    return minOps ;
}



int main() {
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(n + 1, 0));
    int u, v;
    while (m--) {
        cin >> u >> v;
        a[u - 1][v - 1] = 1;  
        a[v - 1][u - 1] = 1; 
    }
    for (int i = 0; i < n; i++) {
        a[i][n] = 1;  
        a[i][i] = 1;  
    }

    elimination(a); 
    /*cout << "---matrix after elimination" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
        cout << "---elimination ends" << endl;*/
    for (int i = pivot; i < n; i++) {
        if (a[i][n] != 0) {
            cout << -1 << endl; 
            return 0;
        }
    }
    if (pivot == n) {
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (a[i][n] == 1) {
                ans++;
            }
        }
        cout << ans << endl; 
        return 0;
    } else {
        cout << min_operate(a) << endl;  
    }

    return 0;
}
