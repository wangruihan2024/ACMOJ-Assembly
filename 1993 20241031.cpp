#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int N, sum;
vector<int> a;
vector<bool> visit;
bool cmp(int p, int q) {
    return p > q;
}
bool dfs(int to_sum, int cnt, int temp_sum, vector<int>& a, vector<bool>& visit, int start) {
    if(cnt == 0)
        return true;
    if(temp_sum == to_sum)
        return dfs(to_sum, cnt - 1, 0, a, visit, 0);
    for (int j = start; j < N; j++) {
        if(visit[j] == false && temp_sum + a[j] <= to_sum) {
            visit[j] = true;
            if(dfs(to_sum, cnt, temp_sum + a[j], a, visit, j + 1))
                return true;
            visit[j] = false;
            if(temp_sum == 0 || temp_sum + a[j] == to_sum)
                return false;
            int k = j + 1;
            while(a[k] == a[j] && (k + 1) < N)
                k++;
            j = k;
        }
    }
    return false;
}
int main() {
    cin >> N;
    a.resize(N);
    visit.resize(N, false);
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        if(a[i] > 50) {
            cout << -1;
            return 0;
        }
        sum += a[i];
    }
    sort(a.begin(), a.end(), cmp);
    for (int i = a[0]; i <= sum; i++) {
        if(sum % i == 0) {
            int cnt = sum / i;//拼好后小木棒的总根数
            if(dfs(i, cnt, 0, a, visit, 0)) {
                cout << i;
                return 0;
            }

        }
    }
        return 0;
}