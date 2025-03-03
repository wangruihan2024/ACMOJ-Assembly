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
    vector <int> arr;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        arr.push_back(x);
    }
    auto [l, r] = partition(arr, pivot);
    for (auto i : arr) cout << i << ' ';
    cout << '\n' << l << ' ' << r << '\n';
}