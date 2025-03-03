#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;
int n, max_num, max_digit;
vector<int> a, b;
string s, digit;
void input() {
    getline(cin, s);
    s = s.substr(1, s.size() - 2);
    istringstream ss(s);
    while(getline(ss, digit, ',')) {
        a.push_back(stoi(digit));
    }
}
int main() {
    cin >> n;
    cin.ignore();
    input();
    for (int i = 0; i < n; i++) {
        if(a[i] > max_num) {
            max_num = a[i];
            max_digit = i;
        }
    }
    b.resize(n);
    b[0] = a[0];
    b[n - 1] = a[n - 1];
    for (int i = 1; i <= max_digit; i++) {
        b[i] = max(b[i - 1], a[i]);
    }
    for (int i = n - 2; i > max_digit; i--) {
        b[i] = max(b[i + 1], a[i]);
    }
    long long int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += (b[i] - a[i]);
    }
    cout << sum << endl;
    return 0;
}