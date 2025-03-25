#include <iostream>
#include <vector>
#include <queue>
using namespace std;
constexpr int SIZE = 1e6 + 5;
vector<std::pair<int, int>> children;
int main() {
    int N;
    cin >> N;
    children.resize(SIZE, {-1, -1});
    int fa;
    for (int i = 1; i <= N - 1; i++) {
        cin >> fa;
        if(children[fa].first == -1)
            children[fa].first = i;
        else
            children[fa].second = i;
    }
    queue<int> q;
    q.push(0);
    while(!q.empty()) {
        int tmp = q.front();
        q.pop();
        cout << tmp << " ";
        int left = children[tmp].first, right = children[tmp].second;
        if(left != -1)
            q.push(left);
        if(right != -1)
            q.push(right);
    }
    return 0;
}
