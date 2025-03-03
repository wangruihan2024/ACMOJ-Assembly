#include <iostream>
#include "2575 20250219.hpp"
using namespace std;

int main() {
    const int size = 50;
    auto hash1 = BloomFilter::generate_hash_function(1);
    auto hash2 = BloomFilter::generate_hash_function(2);
    auto hash3 = BloomFilter::generate_hash_function(3);
    cout << "generate hash function successfully" << endl;
    BloomFilter bf(size, {hash1, hash2, hash3});
    cout << "generate Bloomfilter " << endl;
    std::vector<std::string> inserted = {"test1", "test2", "test3", "", "a", "aa", "aaa", "!!!!", "12345"};
    std::vector<std::string> not_inserted = {"test4", "test5", "aaaa", "bbb", "ccc", "?????"};
    
    for (const auto& s : inserted) {
        bf.add(s);
    }
    cout << "add" << endl;
    int tp = 0, fp = 0, tn = 0, fn = 0;
    
    for (const auto& s : inserted) {
        if (bf.possibly_contains(s)) tp++;
        else fn++;
    }
    
    for (const auto& s : not_inserted) {
        if (bf.possibly_contains(s)) fp++;
        else tn++;
    }

    cout << fn << endl;
    return 0;
}