#ifndef ROLLING_HASH_HPP
#define ROLLING_HASH_HPP

#include <iostream>
#include <vector>
#include <string>
const int max = 5005;
class RollingHash {
private:
    long long p1 = 1e7 + 3,p2 = 1e7 + 9, B = 131;
    //std::vector<char> str;
    long long n = 0;
    std::vector<long long> hash1, hash2, fac1, fac2;
        // 在这里添加你需要的私有成员变量和函数

    public:
    RollingHash() {
        hash1.resize(max, 0);
        hash2.resize(max, 0);
        fac1.resize(max, 1);
        fac2.resize(max, 1);
        //fac1[0] = fac2[0] = 1;
        for (int i = 1; i < max; i++) {
            fac1[i] = fac1[i - 1] * B % p1;
            fac2[i] = fac2[i - 1] * B % p2;
        }
        // 初始化你的class
    };

    ~RollingHash() {};
    std::pair<long long, long long> getp()
    {
        return std::pair<long long, long long>(p1, p2);
    };
    // 将字符 c 追加到字符串末尾
    void append(char c) {
        int val = c - 'a' + 1;
        n++;
        //str[n] = c;
        hash1[n] = (hash1[n - 1] * B + val) % p1;
        hash2[n] = (hash2[n - 1] * B + val) % p2;
    };        

    // 获取从位置 l 到位置 r 的子串的哈希值（1-based 索引）
    // 返回一个包含两个 long long 的 pair，分别是两个模数下的哈希值
    std::pair<long long, long long> getHash(int l, int r){
        int length = r - l + 1;
        long long hash_1 = (hash1[r] - hash1[l - 1] * fac1[length] % p1 + p1) % p1;
        long long hash_2 = (hash2[r] - hash2[l - 1] * fac2[length] % p2 + p2) % p2;
        return std::make_pair(hash_1, hash_2);
    };

};
#endif