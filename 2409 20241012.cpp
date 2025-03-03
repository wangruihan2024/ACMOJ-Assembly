#include <iostream>
#include <map>
#include <utility>
using namespace std;
int n, a[100005], ans, sear;
multimap<int, int> num;
int main() {
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        ans ^= x;
        a[i] = x;
    }
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        ans ^= x;
        num.insert(make_pair(x, i));
    }
//    cout << ans << endl;
    for (int i = 0; i < n; i++) {
        sear = a[i] ^ ans;
        if(num.count(sear)) {
            a[i] = num.find(sear)->second;
            num.erase(num.find(sear));
        }else{
            std::cout << -1 << std::endl;
            return 0;
        }
    }
    for (int i = 0; i < n; i++) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << a[i] << " ";
    }
        // 输出
        return 0;
}