#include <bits/stdc++.h>
using namespace std;

pair<int, int> partition(vector <int> &a, int pivot) {
    int l = 0, r = a.size() - 1;
    int i = 0;
    int min_a = 0;
    for (int j = 0; j < r; j++){
        if(a[j] < min_a) {
            min_a = a[j];
        }
    }
        while (i <= r && l <= r + 1)
        {
            if (a[i] < pivot){
                swap(a[i], a[l]);
                l++;
                i++;
            }
            else if (a[i] > pivot) {
                if(i != r){
                    swap(a[i], a[r]);
                    r--;
                }else{
                    break;
                }


            }
            else {
                i++;
            }
        }
   // if(min_a != pivot)    
        return {l, r};
 /*   else {
        for (int i = 0; i < a.size(); i++){
            if(a[i] > pivot){
                r = i;
                break;
            }
        }
        return {l, r};
    }*/
}

int main() {
    int n, pivot;
    cin >> n >> pivot;
    vector <int> arr, before;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        arr.push_back(x);
    }
    before = arr;
    auto [l, r] = partition(arr, pivot);
    cout << "Returns: " << l << " " << r << endl;
    cout << "Array after modification:";
    for (auto i : arr) {
        cout << ' ' << i;
    }
    cout << endl;
    // check solution:
    vector <int> after = arr;
    sort(before.begin(), before.end());
    sort(after.begin(), after.end());
    if (before != after) {
        cout << "FAILED: numbers not matched" << endl;
        return 1;
    }
    if (l < 0 || r > n || l > r || (l == r && (l == 0 || l == n))) {
        cout << "FAILED: l r at bad position" << endl;
        return 1;
    }
    int left = 0, right = 0, mid = 0;
    for (int i = 0; i < l; i++) {
        if (arr[i] > pivot) {
            cout << "FAILED: position " << i << " is greater than pivot" << endl;
            return 1;
        }
        if (arr[i] == pivot) left ++;
    }
    for (int i = l; i < r; i++) {
        if (arr[i] != pivot) {
            cout << "FAILED: position " << i << " is not equal to pivot" << endl;
            return 1;
        }
        mid ++;
    }
    for (int i = r; i < n; i++) {
        if (arr[i] < pivot) {
            cout << "FAILED: position " << i << " is less than pivot" << endl;
            return 1;
        }
        if (arr[i] == pivot) right ++;
    }
    double ratio = max(left, right) * 1. / (left + mid + right);
    cout << "Ratio: " << ratio << endl;
    if (max(left, right) > 10 && ratio > 0.8) {
        cout << "FAILED: too imbalanced" << endl;
        return 1;
    }
    cout << "OK" << endl;
}