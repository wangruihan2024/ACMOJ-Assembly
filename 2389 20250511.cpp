#include <iostream>
#include <queue>
#include <unordered_map>
#include <climits>
#include <vector>
using namespace std;

struct pos {
    int x, y;
    int time;
    char lastPortal;
};
bool check(const char &c_) {
    if(c_ == '#' || c_ == '.' || c_ == '=' || c_ == '@')
        return false;
    return true;
}
int n, m;
vector<string> c;
int startX = -1, startY = -1;
int exitX = -1, exitY = -1;
unordered_map<char, vector<pair<int, int>>> door;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
int main() {
    cin >> n >> m;
    c.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
        for (int j = 0; j < m; ++j) {
            if (c[i][j] == '@') {
                startX = i;
                startY = j;
            } else if (c[i][j] == '=') {
                exitX = i;
                exitY = j;
            } else if (c[i][j] != '.' && c[i][j] != '#') {
                door[c[i][j]].emplace_back(i, j);
            }
        }
    }
    vector<vector<int>> visited(n, vector<int>(m, INT_MAX));
    queue<pos> q;
    q.push({startX, startY, 0, '\0'});
    visited[startX][startY] = 0;
    while(!q.empty()) {
        pos current = q.front();
        q.pop();
        if(current.x == exitX && current.y == exitY) {
            cout << current.time << endl;
            return 0;
        }
        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];
            if(nx >= 0 && nx < n && ny >= 0 && ny < m && c[nx][ny] != '#') {
                if(check(c[nx][ny])) {
                    char portal_ = c[nx][ny];
                    if (portal_ == current.lastPortal)
                        continue;
                    vector<pair<int, int>> portals = door[portal_];
                    pair<int, int> newPos;
                    if(portals[0].first == nx && portals[0].second == ny) {
                        newPos = portals[1];
                    }else {
                        newPos = portals[0];
                    }
                    if (visited[newPos.first][newPos.second] > current.time + 1) {
                        visited[newPos.first][newPos.second] = current.time + 1;
                        q.push({newPos.first, newPos.second, current.time + 1, portal_});
                    }
                } else {
                    if (visited[nx][ny] > current.time + 1) {
                        visited[nx][ny] = current.time + 1;
                        q.push({nx, ny, current.time + 1, '\0'});
                    }
                }
            }
        }
    }
    return 0;
}