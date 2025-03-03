#include <iostream>
#include <vector>
using namespace std;
int V, N;
vector<int> w, v;
int main() {
    cin >> V >> N;
    w.resize(N, 0), v.resize(N, 0);
    vector<int> dp(V + 1, 0);
    for (int i = 0; i < N; i++) {
        cin >> w[i] >> v[i];
    }
    for (int i = 0; i < N; i++) {
        for (int j = w[i]; j <= V; j++) {
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }
    cout << dp[V] << endl;
}