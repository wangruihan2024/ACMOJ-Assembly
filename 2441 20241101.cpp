#include <iostream>
#include <map>
#include <vector>
using namespace std;
map<string, int> a;
int n, m, p, q;
string inverse(string a) {
    string b;
    b.resize(m);
    for (int i = 0; i < m; i++) {//要改
        if(a[i] == 'N')
            b[i] = 'Y';
        else
            b[i] = 'N';
    }
    return b;
}
string dfs(string x, int digit) {//max指的是所有位均为Y的字符串
    if(!a.count(x) && !a.count(inverse(x))) 
        return x;
    if(x == string(m, 'Y'))
        return "-1";
    if(digit == 0)
        return "-1";
    x[digit] = 'N';
    if(dfs(x, digit - 1) != "-1")
        return dfs(x, digit - 1);
    else{
        x[digit] = 'Y';
        return dfs(x, digit - 1);
    }
    
}
int main() {
    cin >> n >> m >> p >> q;
    for (int i = 0; i < n; i++) {
        string input;
        cin >> input;
        if(a.count(input))
            a[input]++;
        else
            a.insert(make_pair(input, 1));
    }
    if(p + q > n) {
        cout << -1;
        return 0;
    }
    if(p != 0 || q != 0) {
        vector<string> right;
        vector<string> wrong;
        bool r = true, w = true;//r是存不存在p个相同的串
        for (map<string, int>::iterator it = a.begin(); it != a.end(); it++) {
            if(it -> second == p) {
                r = false;
                right.push_back(it->first);
            }else if(it -> second == q) {
                w = false;
                wrong.push_back(it->first);
            }
        }
        if(p != 0 && q != 0) {
            if(r || w) {
                cout << -1;
                return 0;
            }
            for (int i = 0; i < right.size(); i++) {//p个人全对q个人全错
                if(!a.count(inverse(right[i])))
                    continue;
                else if(a[inverse(right[i])] != q)
                    continue;
                else {
                    cout << right[i];
                    return 0;
                }
            }
        }else if(p == 0) {//不存在全对的人
//            for (int i = wrong.size() - 1; i >= 0; i--) {
//                cout << wrong[i] << endl;
//            }
//            cout << wrong[0] << endl << inverse(wrong[0]) << endl << "-" << endl;
            if (w == true)
            {
                cout << -1;
                return 0;
                }
                else
                {
                    for (int i = wrong.size() - 1; i >= 0; i--)
                    {
                        if (!a.count(inverse(wrong[i])))
                        {
                            cout << inverse(wrong[i]);
                            return 0;
                        }
                    }
                }
        }else {//q=0不存在全错的人
            if(r == true) {
                cout << -1;
                return 0;
            }else {
                for (int i = 0; i < right.size(); i++) {
                    if(!a.count(inverse(right[i]))) {
                        cout << right[i];
                        return 0;
                    }
                }
            }
        }
    }else {
        if(dfs(string(m, 'N'), 0) == string(m, 'Y')) {
            cout << -1;
            return 0;
        }else{
            if(dfs(string(m, 'N'), m - 1) != "-1")
                cout << dfs(string(m, 'N'), m - 1);
            else
                cout << -1;
            return 0;
        }
        return 0;
    }

        return 0;
}