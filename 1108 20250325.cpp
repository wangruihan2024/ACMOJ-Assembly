#include <iostream>
#include <cstring>
#include <unordered_map>
#include <algorithm>
using namespace std;
unordered_map<char, int> idx;
bool find_(const string &s, const char &c) {
    for (int i = 0; i < s.size(); i++)
        if(s[i] == c)
            return true;
    return false;
}
string preorder(const string &in, const string &layer) {
    if(in.empty() || layer.empty())
        return "";
    char root = layer[0];
    // cout << "root:" << root << endl;
    int root_idx = idx[root];
    // cout << "root index :" << root_idx << endl;
    string in_pre = in.substr(0, root_idx - idx[in[0]]);
    string in_aft = ((root_idx - idx[in[0]] + 1) < in.length()) ? in.substr(root_idx - idx[in[0]] + 1) : "";
    // cout << "in_aft:" << in_aft << endl;
    string layer_pre = "", layer_aft = "";
    for (int i = 1; i < layer.size(); i++) {
        if(idx[layer[i]] < root_idx)
            layer_pre += layer[i];
        else
            layer_aft += layer[i];
    }
    // cout << "layer_aft:" << layer_aft << endl;
    string ans_left = preorder(in_pre, layer_pre);
    string ans_right = preorder(in_aft, layer_aft);
    return string(1, root) + ans_left + ans_right;
}
int main() {
    string s1, s2; // s1是中序遍历，s2是层遍历
    cin >> s1 >> s2;
    for (int i = 0; i < s1.size(); i++)
        idx[s1[i]] = i;
    string ans = preorder(s1, s2);
    cout << ans << endl;
}