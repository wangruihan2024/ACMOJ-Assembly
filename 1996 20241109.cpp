#include <iostream>
#include <cstdint>
#include <vector>
using namespace std;

unsigned int h, n;
unsigned int multiplier = 0xc2b2ae35;     

unsigned int inverse_16(unsigned int h) {
    unsigned int ans = 0;
    vector<int> h_temp(32);
    vector<int> ans_temp(32, 0);
    for (int i = 0; i < 32; i++) 
        h_temp[i] = (h >> i) & 1;
    for (int i = 16; i < 32; i++)
        ans_temp[i] = h_temp[i];
    for (int i = 0; i < 16; i++)
        ans_temp[i] = h_temp[i] ^ ans_temp[i + 16];
    for (int i = 0; i < 32; i++)
        ans += ans_temp[i] * (1 << i);
    return ans;
}

unsigned int inverse_13(unsigned int h) {
    unsigned int ans = 0;
    vector<int> h_temp(32);
    vector<int> ans_temp(32, 0);
    for (int i = 19; i < 32; i++) {
        h_temp[i] = (h >> i) & 1;
        ans_temp[i] = h_temp[i];
    }
    for(int i = 0; i < 19; i++) 
        h_temp[i] = (h >> i) & 1;
    for (int i = 6; i < 19; i++) 
        ans_temp[i] = ans_temp[i + 13] ^ h_temp[i];
    for (int i = 0; i < 6; i++)
        ans_temp[i] = h_temp[i] ^ ans_temp[i + 13];
    for (int i = 0; i < 32; i++)
        ans += (1 << i) * ans_temp[i];
    return ans;
}


uint32_t inverse_mod(uint32_t a) {
    int64_t t = 0, newT = 1;
    int64_t r = 0x100000000, newR = a;
    while (newR != 0) {
        int64_t quotient = r / newR;
        int64_t tempT = t;
        t = newT;
        newT = tempT - quotient * newT;
        int64_t tempR = r;
        r = newR;
        newR = tempR - quotient * newR;
    }
    if (t < 0) {
        t += 0x100000000;
    }
    return static_cast<uint32_t>(t);
}

unsigned int inverse_ROTL_13(unsigned int h) {
    unsigned int ans = 0;
    ans += (h / (1 << 13));
    ans += ((h % (1 << 13)) << 19);
    return ans;
}

unsigned int inverse_ROTL_15(unsigned int h) {
    unsigned int ans = 0;
    ans += (h / (1 << 15));
    ans += ((h % (1 << 15)) << 17);
    return ans;
}

int main() {
    cin >> h >> n;
    h = inverse_16(h); 

    unsigned int inverse = inverse_mod(multiplier); 
    h *= inverse;

    h = inverse_13(h); 
    h = inverse_16(h);  

    h = (h - 0xe6546b64) % 0x100000000;  
    h = inverse_ROTL_13(h);
    unsigned int h_temp = 0;
    for (int i = 1; i <= n - 1; i++) {
        h_temp = ((h_temp << 13) | (h_temp >> 19));  
        h_temp += 0xe6546b64;
    }

    unsigned int result = 0;
    result = h_temp ^ h;
    result = inverse_ROTL_15(result); 
    for (int i = 0; i < n - 1; i++) {
        cout << 0 << " ";
    }
    cout << result << endl;

    return 0;
}

