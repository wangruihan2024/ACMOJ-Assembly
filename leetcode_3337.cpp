#include <vector>
using namespace std;
static const int MOD = 1e9 + 7;
static const int total_size = 26;
class Solution {
public:
    int lengthAfterTransformations(string s, int t, vector<int>& nums) {
        if (t == 0)
            return s.length() % MOD;
        vector<long long> freq(total_size, 0);
        for (char& c : s) 
            freq[c - 'a']++;
        // 建系数矩阵
        vector<vector<long long>> M(total_size, vector<long long>(total_size, 0));
        for (int c = 0; c < total_size; ++c) {
            for (int i = 1; i <= nums[c]; ++i) {
                int d = (c + i) % total_size;
                M[c][d]++;
            }
        }
        // 矩阵乘法
        auto multiply = [](const vector<vector<long long>>& a, const vector<vector<long long>>& b) {
            vector<vector<long long>> res(total_size, vector<long long>(total_size, 0));
            for (int i = 0; i < total_size; ++i) {
                for (int k = 0; k < total_size; ++k) {
                    if (a[i][k]) {
                        for (int j = 0; j < total_size; ++j) {
                            res[i][j] = (res[i][j] + a[i][k] * b[k][j]) % MOD;
                        }
                    }
                }
            }
            return res;
        };
        
        // 快速幂
        auto power = [&multiply](vector<vector<long long>> mat, int p) {
            vector<vector<long long>> result(total_size, vector<long long>(total_size, 0));
            for (int i = 0; i < total_size; ++i) {
                result[i][i] = 1; // Identity matrix
            }
            while (p > 0) {
                if (p % 2 == 1) {
                    result = multiply(result, mat);
                }
                mat = multiply(mat, mat);
                p /= 2;
            }
            return result;
        };
        vector<vector<long long>> M_pow = power(M, t - 1);
        vector<long long> freq_(total_size, 0); // t-1操作之后每一个字母出现的频率
        for (int d = 0; d < total_size; ++d) {
            for (int c = 0; c < total_size; ++c) {
                freq_[d] = (freq_[d] + freq[c] * M_pow[c][d]) % MOD;
            }
        }
        long long length = 0;
        for (int c = 0; c < total_size; ++c) {
            length = (length + freq_[c] * nums[c]) % MOD;
        }
        return static_cast<int>(length);
    }
};