#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct ss {
    int id;
    int r, l;
};
vector<ss> more_left, more_right;
bool cmp_moreleft(ss a, ss b) {
    return a.r < b.r;
}
bool cmp_moreright(ss a, ss b) {
    return a.l > b.l;
}
int main() {
    int n;
    cin >> n;
    string s;
    for (int i = 1; i <= n; i++) {
        cin >> s;
        int left_right = 0, l_temp = 0, r_temp = 0;
        for (int j = 0; j < s.size(); j++) {
            if(s[j] == '(') {
                left_right++;
                l_temp++;
            }else if(s[j] == ')'){
                left_right--;
                if(l_temp != 0)
                    l_temp--;
                else
                    r_temp++;
            }
        }
        if(left_right >= 0)
            more_left.push_back({i, r_temp, l_temp});
        else
            more_right.push_back({i, r_temp, l_temp});
    }
    sort(more_left.begin(), more_left.end(), cmp_moreleft);
    sort(more_right.begin(), more_right.end(), cmp_moreright);
    /*cout << "test------" << endl;
    for (int i = 0; i < more_left.size(); i++)
        cout << more_left[i].id << "---" << more_left[i].l << "---" << more_left[i].r << endl;
    cout << "more left ends ------" << endl;
    cout << "end ------" << endl;*/
    int cnt = 0;
    bool ans = true;
    for (int i = 0; i < more_left.size(); i++) {
        cnt -= more_left[i].r;
        if(cnt < 0) {
            ans = false;
            break;
        }
        cnt += more_left[i].l;
    }
    for (int i = 0; i < more_right.size(); i++) {
        cnt -= more_right[i].r;
        if(cnt < 0) {
            ans = false;
            break;
        }
        cnt += more_right[i].l;
    }
    if(ans == false || cnt != 0) {
        cout << "impossible" << endl;
    }else {
        for (int i = 0; i < more_left.size(); i++)
            cout << more_left[i].id << endl;
        for (int i = 0; i < more_right.size(); i++)
            cout << more_right[i].id << endl;
    }
    return 0;
}