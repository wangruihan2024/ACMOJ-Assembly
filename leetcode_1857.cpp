#include <vector>
#include <cstring>
#include <queue>
using namespace std;

class Solution {
public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        int n = colors.size();
        vector<vector<int>> g(n);
        vector<int> indegree(n);
        for(auto edge : edges) {
            indegree[edge[1]]++;
            g[edge[0]].push_back(edge[1]);
        }
        int cnt = 0;
        queue<int> q;
        vector<vector<int>> dp(n, vector<int>(26)); // 因为是小写字母至多26个
        for(int i = 0; i < n; i++) {
            if(indegree[i] == 0)
                q.push(i);
        }
        while(!q.empty()) {
            cnt++;
            int tmp = q.front();
            q.pop();
            dp[tmp][colors[tmp] - 'a']++;
            for(auto neighbor : g[tmp]) {
                for(int c = 0; c < 26; c++)
                    dp[neighbor][c] = std::max(dp[neighbor][c], dp[tmp][c]);
                --indegree[neighbor];
                if(indegree[neighbor] == 0)
                    q.push(neighbor);
            }
        }
        if(cnt != n)
            return -1;
        else {
            int ans = 0;
            for(int i = 0; i < n; i++) 
                for(int j = 0; j < 26; j++)
                    ans = std::max(dp[i][j], ans);
            return ans;
        }
    }
};