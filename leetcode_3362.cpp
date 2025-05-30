#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int maxRemoval(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<int> effect(n + 1, 0); 
        vector<priority_queue<int>> q(n);
        for (auto& query : queries) 
            q[query[0]].push(query[1]);
        priority_queue<int> candidates; // 当前 i 时所有可用 query 的右端点堆
        int operation = 0; 
        for (int i = 0; i < n; ++i) {
            operation += effect[i];
            while (!q[i].empty()) {
                candidates.push(q[i].top());
                q[i].pop();
            }
            while (operation < nums[i]) {
                while (!candidates.empty() && candidates.top() < i) 
                    candidates.pop(); 
                if (candidates.empty()) 
                    return -1;
                int r = candidates.top(); 
                candidates.pop();
                operation++;
                effect[r + 1] -= 1; 
            }
        }
        int unused = 0;
        for (auto& heap : q) unused += heap.size();
        unused += candidates.size(); 
        return unused;
    }
};
