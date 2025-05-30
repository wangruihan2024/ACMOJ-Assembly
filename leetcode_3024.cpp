#include <vector>
using namespace std;

class Solution {
public:
    string triangleType(vector<int>& nums) {
        sort(nums.begin(), nums.end()); 
        int a = nums[0], b = nums[1], c = nums[2];
        if (a + b <= c)
            return "none";
        else if (a == b && b == c)
            return "equilateral";
        else if (a == b || b == c || a == c)
            return "isosceles";
        else
            return "scalene";
    }
};