#include <iostream>
#include <set>
#include <vector>
#include <map>
using namespace std;
int n, flag;
int num[33][2];
int size(unsigned int a) {
    if(a == 0)
        return 0;
    else{
        for (int i = 0; i <= 31; i++) {
        if(((a / (1 << i)) > 0) && ((a / (1 << (1 + i))) == 0))
            return i;
        }
    }
}
int main() {
    cin >> n >> flag;
    if(flag == 0) {
        map<unsigned int, int> num_flavor;
        unsigned int temp;
        for (int i = 0; i < n; i++) {
            cin >> temp;
            num_flavor[temp]++;
        }
        set<unsigned int> popular;
        unsigned int max_popular = 0;
        for (map<unsigned int, int>::iterator it = num_flavor.begin(); it != num_flavor.end(); it++)
        {
            if(it->second > max_popular) {
                popular.clear();
                popular.insert(it->first);
                max_popular = it->second;
            }else if(it->second == max_popular) {
                popular.insert(it->first);
            }
        }
        for (set<unsigned int>::iterator it = popular.begin(); it != popular.end(); it++) {
            cout << *it << " ";
        }
    }else if(flag == 1) {
        unsigned int num = 1, temp, ans; // num记录会不会是-的 ans记录当前的标志数
        cin >> ans;
        if(n == 1) {
            cout << ans;
            return 0;
        }
        while(n >= 2) {
            cin >> temp;
            if(num == 0) {
                ans = temp;
                num = 1;
            }else {
                if(temp != ans) 
                    num--;
                else
                    num++;
            }
            n--;
        //    cout << n << " ";
        }
        cout << ans;
    }else {
        

        unsigned int temp;
        while(n--) {
            cin >> temp;
            for (int i = 0; i <= 31; i++) {
                if((1 & (temp >> i)) == 1)
                    num[i][1]++;
                else
                    num[i][0]++;
            }
        }
//        for (int i = 0; i <= 31; i++)
//            cout << num[i][0] << " " << num[i][1] << endl;
        unsigned int ans = 0;
        int digit[32], count = 0;//count指的是0个数=1个数的总位数
        for (int i = 0; i <= 31; i++) {
            if(num[i][1] > num[i][0])
                ans += (1 << i);
            else if(num[i][1] == num[i][0]) {
                digit[count] = i;
                count++;
            }
        }
        
        //    cout << ans << endl;
        //    cout << count << endl;
                cout << ans << " ";
        for (int i = 1; i <= ((1 << count) - 1); i++) {
            unsigned int ans_add = 0;
            for (int j = 0; j <= size(i); j++) {
                if((1 & (i >> j)) == 1) {
                    ans_add += (1 << (digit[j]));
                }
            }
            cout << ans + ans_add << " ";
        }
    }
//    cout << size(n);
    return 0;
}