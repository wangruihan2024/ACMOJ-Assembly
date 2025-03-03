#include <iostream>

using namespace std;
bool a[5][5];
int minnum = 10;
int temp_x, temp_y;
bool if_complete() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if(a[i][j] == false)
                return false;
        }
    }
    return true;
}
void inverse(int x, int y) {
    a[x][y] = !a[x][y];
    if(x >= 1)
        a[x - 1][y] = !a[x - 1][y];
    if(x <= 1)
        a[x + 1][y] = !a[x + 1][y];
    if(y >= 1)
        a[x][y - 1] = !a[x][y - 1];
    if(y <= 1)
        a[x][y + 1] = !a[x][y + 1];
}
void dfs(int x, int y, int num) {
    if(if_complete()) {
        minnum = min(minnum, num);
        return;
    }
    if(x == 3)
        return;
    inverse(x, y);
    if(y == 2)
        dfs(x + 1, 0, num + 1);
    else
        dfs(x, y + 1, num + 1);
    inverse(x, y);
    if(y == 2)
        dfs(x + 1, 0, num);
    else
        dfs(x, y + 1, num);
}
int main() {
    int input;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            cin >> input;
            a[i][j] = (input == 1);
        }
    dfs(0, 0, 0);
    cout << minnum << endl;
    return 0;
}