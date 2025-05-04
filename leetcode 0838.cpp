#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string pushDominoes(string dominoes) {
        int length = (int)dominoes.size();
        vector<int> leftR(length, INT_MAX); // 左边最近的R
        int R = INT_MAX;
        for (int i = 0; i < length; i++) {
            if(dominoes[i] == 'R')
                R = i;
            else if(dominoes[i] == 'L')
                R = INT_MAX;
            else
                leftR[i] = (R == INT_MAX ? INT_MAX : i - R);
        }
        vector<int> rightL(length); // 右边最近的L
        int L = INT_MAX;
        for (int i = length - 1; i >= 0; i--) {
            if(dominoes[i] == 'R')
                L = INT_MAX;
            else if(dominoes[i] == 'L')
                L = i;
            else
                rightL[i] = (L == INT_MAX ? INT_MAX : L - i);
        }
        for (int i = 0; i < length; i++) {
            if(dominoes[i] == '.') {
                if(leftR[i] != rightL[i])
                    dominoes[i] = leftR[i] > rightL[i] ? 'L' : 'R';
            }
        }
        return dominoes;
    }
};

int main() {
    Solution s;
    cout << s.pushDominoes(".L.R...LR..L..") << endl;
    return 0;
}
