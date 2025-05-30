#include <vector>
#include <algorithm>
#include <set>
using namespace std;

class Solution {
public:
    int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills, int strength) {
        int n = tasks.size(), m = workers.size();
        sort(tasks.begin(), tasks.end());
        sort(workers.begin(), workers.end());

        auto check = [&](int k) -> bool {
            multiset<int> availableWorkers;
            for (int i = m - k; i < m; ++i) {
                availableWorkers.insert(workers[i]);
            }
            int used = pills;
            for (int i = k - 1; i >= 0; --i) {
                int task = tasks[i];
                auto it = prev(availableWorkers.end());
                if (*it >= task) {
                    availableWorkers.erase(it);
                } else {
                    auto candidate = availableWorkers.lower_bound(task - strength);
                    if (candidate == availableWorkers.end() || used == 0)
                        return false;
                    availableWorkers.erase(candidate);
                    --used;
                }
            }
            return true;
        };
        int low = 0, high = min(n, m), ans = 0;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (check(mid)) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return ans;
    }
};
