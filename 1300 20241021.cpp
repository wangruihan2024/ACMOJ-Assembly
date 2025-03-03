#include <bits/stdc++.h>
#include <random>
#include <chrono>
using namespace std;
int n, k;
vector <int> a;
const int RANDOM_SEED = chrono::system_clock::now().time_since_epoch().count();
mt19937 rng(RANDOM_SEED); // random number generator

int randint(int l, int r) { // rand in [l, r]
    return int(rng() % (r - l + 1) + l);
}
void read_input_data_vector()
{
 int m;
 cin >> n >> k >> m; a.resize(n);
 for (int i = 0; i < m; i++)
 {
     cin >> a[i];
 }
 unsigned int z = a[m - 1];
 for (int i = m; i < n; i++)
 {
     z ^= z << 13;
     z ^= z >> 17;
     z ^= z << 5;
     a[i] = z & 0x7fffffff;
 }
}
int partition(vector<int>& a, int l, int r) {//输出pivot的位置
    int result = l - 1;
    int ran = randint(l, r);
    int pivot = a[ran];
    swap(a[ran], a[r]);
    
    for (int i = l;i < r; i++) {
        if(a[i] <= pivot) { 
            result++;
            swap(a[i], a[result]);
            
        }
    }
    swap(a[result + 1], a[r]);
    return result + 1;
}
int find(vector<int>& a, int l, int r, int k) {
    if(l <= r) {
    int pos = partition(a, l, r);
    if(pos == k - 1)
        return a[pos];
    else if(pos < k - 1) {
      //  k -=  (pos);
        return find(a, pos + 1, r, k);
        
    }else
        return find(a, l, pos - 1, k);
    }
    return -1;
}
int main() {
    read_input_data_vector();
    cout << find(a, 0, n - 1, k);
    return 0;
}