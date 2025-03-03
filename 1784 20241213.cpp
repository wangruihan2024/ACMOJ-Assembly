#include <iostream>

using namespace std;
int a[11][11], b[11][11];
bool suit(int x, int y, int num) {
    for (int i = 1; i <= 9; i++)
        if(i != x && b[i][y] == num)
            return false;
    for (int i = 1; i <= 9; i++)
        if(i != y && b[x][i] == num)
            return false;
    int x_region, y_region;
    if(1 <= x && x <= 3)
        x_region = 1;
    else if(4 <= x && x <= 6)
        x_region = 2;
    else
        x_region = 3;
    if(1 <= y && y <= 3)
        y_region = 1;
    else if(4 <= y && y <= 6)
        y_region = 2;
    else
        y_region = 3;
    for (int i = 3 * x_region - 2; i <= 3 * x_region; i++)
        for (int j = 3 * y_region - 2; j <= 3 * y_region; j++)
            if((i != x || j != y) && b[i][j] == num)
                return false;
    return true;
}
void dfs(int row, int col, int remain) {
    if(remain == 0) {
        for (int i = 1; i <= 9; i++) {
            for (int j = 1; j <= 9; j++)
                cout << b[i][j] << " ";
            cout << endl;
        }
        return;
    }else {
        if(a[row][col] != 0) {
            if(col == 9)
                dfs(row + 1, 1, remain);
            else
                dfs(row, col + 1, remain);
        }else {
            for (int i = 1; i <= 9; i++) {
                if(suit(row, col, i)) {
                    b[row][col] = i;
                    remain--;
                    if(col == 9)
                        dfs(row + 1, 1, remain);
                    else
                        dfs(row, col + 1, remain);
                    remain++;
                    b[row][col] = 0;
                }
            }
        }
    }
}
int main() {
    int remain = 0;
    for (int i = 1; i <= 9; i++)
        for (int j = 1; j <= 9; j++) {
            cin >> a[i][j];
            b[i][j] = a[i][j];
            if(a[i][j] == 0)
                remain++;
        }
    dfs(1, 1, remain);
    return 0;
}