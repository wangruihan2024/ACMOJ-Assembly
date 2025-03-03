#include <iostream>
#include <vector>
using namespace std;
vector<int> num(28, 0);  // 1~27的下标
bool ans = false;
void dfs(int step) {
    if(step == 0) {
        ans = true;
        return;
    }
    for (int i = 1; i <= 27; i++) {
        if(num[i] >= 3) {
            num[i] -= 3;
            dfs(step - 3);
            num[i] += 3;
        }
    }
    for (int i = 1; i <= 25; i++) {
        if(i % 9 <= 7 && num[i] > 0 && num[i + 1] > 0 && num[i + 2] > 0) {
            num[i]--;
            num[i + 1]--;
            num[i + 2]--;
            dfs(step - 3);
            num[i]++;
            num[i + 1]++;
            num[i + 2]++;
        }
    }
        return;
}
int main() {
    for (int i = 1; i <= 14; i++) {
        string s;
        cin >> s;
        num[s[0] - '0' + (s[1] - 'A') * 9]++;
    }
    /*for (int i = 1; i <= 27; i++) {
        cout << num[i] << " - ";
    }
    cout << endl;*/
    for (int i = 1; i <= 27; i++)
    {
        if (num[i] >= 2)
        {
            num[i] -= 2;
            dfs(12);
            num[i] += 2;
        }
    }
    if(ans)
        cout << "True" << endl;
    else
        cout << "False" << endl;
    return 0;
}