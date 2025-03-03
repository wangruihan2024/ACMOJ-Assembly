#include <iostream>
using namespace std;
int n, m;
long long int MAX, score;
int h[105][105], c[105][105];
long long int visit[105][105];
int dir[4][2] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
bool in(int x, int y){
    if(x >= 0 && x < n && y >= 0 && y < m)
        return true;
    return false;
}
void dfs(int x, int y) {
    if(visit[x][y] != -1)
        return;
    visit[x][y] = c[x][y];
    for (int i = 0; i < 4; i++) {
        int x1 = x + dir[i][0];
        int y1 = y + dir[i][1];
        if(in(x1, y1) && h[x1][y1] < h[x][y]) {
            if (visit[x1][y1] == -1) 
                dfs(x1, y1);
            visit[x][y] = max(visit[x][y], c[x][y] + visit[x1][y1]);
        }
    }
    MAX = max(MAX, visit[x][y]);
}
int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            visit[i][j] = -1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> h[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) 
            cin >> c[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if(visit[i][j] == -1)
                dfs(i, j);
    cout << MAX << endl;
}
            