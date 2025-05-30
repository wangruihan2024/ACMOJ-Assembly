#include <unordered_map>
#include <vector>
using namespace std;
class Solution {
    static const int MOD = 1e9 + 7;
public:
    int colorTheGrid(int m, int n) {
        int m_ = std::min(m, n), n_ = std::max(m, n); // 行列统一为 m_ 行 n_ 列
        unordered_map<int, vector<int>> colors;
        int num = pow(3, m_);
        for (int i = 0; i < num; i++) {
            vector<int> color;
            int i_ = i;
            bool flag = false;
            for (int j = 0; j < m_; j++) {
                color.push_back(i_ % 3);
                i_ /= 3;
                if (j && color[j] == color[j - 1]) {
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                colors[i] = color;
            }
        }
        unordered_map<int, vector<int>> adj;
        for (auto& [num1, color1] : colors) {
            for (auto& [num2, color2] : colors) {
                bool flag = false;
                for (int i = 0; i < m_; i++) {
                    if (color1[i] == color2[i]) {
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    adj[num1].push_back(num2);
                }
            }
        }
        vector<int> prev(num, 0);
        for (auto& [i, _] : colors) {
            prev[i] = 1;
        }
        vector<int> aft(num, 0);
        for (int i = 1; i < n_; i++) {
            fill(aft.begin(), aft.end(), 0); // ← 清空 aft
            for (auto& [num2, _] : colors) {
                for (int num1 : adj[num2]) {
                    aft[num2] = (aft[num2] + prev[num1]) % MOD;
                }
            }
            prev = aft; 
        }
        int ans = 0;
        for (int cnt : prev) {
            ans = (ans + cnt) % MOD;
        }
        return ans;
    }
};
