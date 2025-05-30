class Solution {
public:
    int differenceOfSums(int n, int m) {
        int cnt = n / m;
        long long int sum = n * (n + 1) / 2;
        long long int sum_ = m * cnt * (cnt + 1) / 2;
        return sum - 2 * sum_;
    }
};