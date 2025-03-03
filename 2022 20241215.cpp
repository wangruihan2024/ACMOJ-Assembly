#include <iostream>
#include <vector>
using namespace std;
long long int cnt = 0;
void merge(vector<long long int> &b, long long int l, long long int r) {
    long long int mid = (l + r) / 2;
    vector<long long int> temp(r - l + 1);
    long long int i = l, j = mid + 1, k = 0;
    while(i <= mid && j <= r) {
        if(b[i] < b[j]) {
            temp[k] = b[i];
            cnt += (r - j + 1);
            k++;
            i++;
        }else {
            temp[k] = b[j];
            j++;
            k++;
        }
    }
    while(i <= mid)
        temp[k++] = b[i++];
    while(j <= r) {
        temp[k++] = b[j++];
        // cnt += (mid - l + 1);
    }
    for (long long int x = 0; x < temp.size(); x++)
        b[x + l] = temp[x];
}
void merge_sort(vector<long long int> &b, long long int l, long long int r) {
    long long int mid = (l + r) / 2;
    if(l >= r)
        return;
    merge_sort(b, l, mid);
    merge_sort(b, mid + 1, r);
    merge(b, l, r);
}

int main() {
    long long int N;
    cin >> N;
    vector<long long int> a(N + 1), b(N + 1);
    for (long long int i = 1; i <= N; i++) {
        cin >> a[i];
        b[i] = a[i] - i * i;
    }
    /*for (int i = 1; i <= N; i++) {
        cout << "-" << b[i];
    }
    cout << endl;*/
    merge_sort(b, 1, N);
    cout << cnt << endl;
}