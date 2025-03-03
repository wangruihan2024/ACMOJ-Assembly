#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

// 存储类模板的信息
struct TemplateClass {
    string name;  // 类模板名
    vector<string> params;  // 模板参数
    vector<pair<vector<string>, vector<string>>> friends;  // 友元模板（模板参数， 实例化参数）
};

// 判断两个模板参数是否一致
bool isMatchingParams(const vector<string>& templateParams, const vector<string>& instantiatedParams) {
    if (templateParams.size() != instantiatedParams.size()) return false;
    for (size_t i = 0; i < templateParams.size(); ++i) {
        if (templateParams[i] != instantiatedParams[i]) return false;
    }
    return true;
}

int main() {
    int n, m;
    cin >> n >> m;
    cin.ignore();  // 忽略换行符

    vector<TemplateClass> classes;  // 用来存储所有类模板
    vector<pair<string, string>> queries;  // 用来存储查询（A, B）

    // 1. 读取类模板声明
    for (int i = 0; i < n; ++i) {
        string line;
        getline(cin, line);
        stringstream ss(line);
        string tmp, className;
        vector<string> params;

        // 读取模板参数和类名
        cin.ignore();  // 忽略 '<'
        while (ss >> tmp && tmp != ">") {
            params.push_back(tmp);  // 读取模板参数
        }
        ss >> className;  // 读取类模板名称

        int k;
        cin >> k;
        cin.ignore();  // 忽略空格和换行符

        TemplateClass tmpl;
        tmpl.name = className;
        tmpl.params = params;

        // 2. 读取友元声明
        for (int j = 0; j < k; ++j) {
            vector<string> friendParams, instantiatedParams;
            string friendClassName;
            getline(cin, line);
            stringstream fs(line);

            // 读取友元模板参数和友元类名
            cin.ignore();  // 忽略 '<'
            while (fs >> tmp && tmp != ">") {
                friendParams.push_back(tmp);  // 读取友元模板参数
            }
            fs >> friendClassName;  // 读取友元类名

            // 读取友元实例化参数
            while (fs >> tmp) {
                instantiatedParams.push_back(tmp);  // 读取友元实例化参数
            }

            tmpl.friends.push_back(make_pair(friendParams, instantiatedParams));
        }

        classes.push_back(tmpl);
    }

    // 3. 读取查询
    for (int i = 0; i < m; ++i) {
        string A, B;
        vector<string> Aparams, Bparams;
        for (int j = 0; j < 2; ++j) {
            string line;
            getline(cin, line);
            stringstream ss(line);
            string tmp;
            if (j == 0) ss >> A;  // 读取类模板A的名称
            if (j == 1) ss >> B;  // 读取类模板B的名称

            // 读取实例化参数
            cin.ignore();  // 忽略 '<'
            while (ss >> tmp && tmp != ">") {
                if (j == 0) Aparams.push_back(tmp);
                if (j == 1) Bparams.push_back(tmp);
            }
        }

        // 4. 判断A是否是B的友元
        bool isFriend = false;
        for (const auto& tmpl : classes) {
            if (tmpl.name == B) {
                for (const auto& f : tmpl.friends) {
                    // 友元模板参数和实例化参数都匹配时，A是B的友元
                    if (isMatchingParams(f.first, Aparams) && isMatchingParams(f.second, Bparams)) {
                        isFriend = true;
                        break;
                    }
                }
            }
            if (isFriend) break;
        }

        if (isFriend) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }

    return 0;
}
