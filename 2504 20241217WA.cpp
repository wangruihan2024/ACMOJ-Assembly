#include<iostream>
using namespace std;
int response, n, snd;
int binary_search(int l, int r) {
    while(l <= r) {
        int >mid = (l + r) / 2;
        cout << 0 << " " << mid << " " << r << endl;
        cin >> response;
        if(response == snd)
            l = mid;
        else
            r = mid - 1;
    }
    if(l == r - 1){
        if(l == snd)
            return r;
        return l;
    }else if(l == r)
        return l;
    else if(l < r - 1)
        return -1;
}
int main() {
   
    
}