#include <cstdio>
#include <cstdint>
#include <vector>
#include <iostream>
typedef uint32_t u32;
const u32 maxn = 2e7 + 2;

u32 n, a[maxn], seed;
inline u32 nextInteger(u32 x) {
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return x;
}

bool outputArr(void *a, u32 size) {
    if (size % 4) {
        return puts("-1"), 0;
    }

    u32 blocks = size / 4;
    u32 *A = (u32 *)a;
    u32 ret = size;
    u32 x = 23333333;
    for (u32 i = 0; i < blocks; i++) {
        ret = ret ^ (A[i] + x);
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
    }
    return printf("%u\n", ret), 1;
}

signed main() {
    scanf("%d%d", &n, &seed);
    for (u32 i = 0; i < n; ++i) {
        seed = nextInteger(seed);
        a[i] = seed;
    }
    u32 max_a = a[0];
   /* for (u32 i = 1; i < n; i++) {
        if(max_a < a[i])
            max_a = a[i];
    }*/
    std::vector<u32> result(n);
    std::vector<int> count(256, 0);
    long long i = 1;
    int k = 0;
    while (k <= 3) {
        for (int j = 0; j < 256; j++) {
            count[j] = 0;
        }
        for (int j = 0; j < n; j++) {
            count[(a[j] / i) % 256]++;
        }
        for (int j = 1; j < 256; j++) {
            count[j] += count[j - 1];
        }
        for (int j = n - 1; j >= 0; j--) {
            result[count[(a[j] / i) % 256] - 1] = a[j];
            count[(a[j] / i) % 256]--;
        }
        for (u32 j = 0; j < n; j++) 
            a[j] = result[j];
        k++;
        i = i << 8;
//        std::cout << i << std::endl;
    }
    outputArr(a, n * sizeof(u32));
}