#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int n;
long long h;
long long A;//101010
long long B;//010101
int main() {
    cin >> n;
    cin >> h;
    A = h; 
    B = h;
    long long A_count = 1, B_count = 1;
    bool find_smaller = true, find_larger = true;
    for (int i = 1; i < n; i++) {
        cin >> h;
        if((h < A && find_smaller) || (h > A && !find_smaller)) {
            if (find_smaller)
                find_smaller = false;
            else
                find_smaller = true;
            A_count++;
        }

        if((h > B && find_larger) || (h < B && !find_larger)) {
            if (find_larger)
                find_larger = false;
            else
                find_larger = true;
            B_count++;
        }
        A = h;
        B = h;
    }
    cout << max(A_count, B_count) << endl;
}