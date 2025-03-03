#include <bits/stdc++.h>
using namespace std;
int N, M;
int a[1005][1005];
int vis[1005][1005];
int cnt, ans;
int dir[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
bool in(int x, int y) {
    if(x >= 0 && x < N && y >= 0 && y < M)
        return true;
    return false;
}
int dfs(int x, int y) {
    if(vis[x][y] != -1)
        return vis[x][y];
    vis[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        int x_temp = x + dir[i][0];
        int y_temp = y + dir[i][1];
        if(in(x_temp, y_temp) && a[x_temp][y_temp] > a[x][y])
            vis[x][y] = max(vis[x][y], 1 + dfs(x_temp, y_temp));
    }
    return vis[x][y];
}
int main() {
    cin >> N >> M;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++) {
            cin >> a[i][j];
            vis[i][j] = -1;
        }
    for (int i = 0; i < N; i++) 
        for (int j = 0; j < M; j++)
            ans = max(ans, dfs(i, j));
    cout << ans << endl;
    return 0;
}