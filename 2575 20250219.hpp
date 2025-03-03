#include <string>
#include <functional>
#include <vector>
#include <set>

class BloomFilter
{
private:
    // add whatever you want here
    int size;
    std::vector<std::function<size_t(const std::string &)>> functions;
    std::vector<bool> exist;

public:
    // Size is the size of the bit array
    // You should accept arbitrary number of hash functions!
    BloomFilter(int size, std::initializer_list<std::function<size_t(const std::string&)>> hashes):size(size), functions(hashes), exist(size, false) {
        std::initializer_list<std::function<size_t(const std::string &)>> a;

    };

    // Destructor
    // Implement if necessary to handle cleanup or memory management.

    // Method to add an item to the filter.
    void add(const std::string& item) {
        for (auto it = functions.begin(); it != functions.end(); it++) {
            size_t tmp_hash = (*it)(item);
            exist[tmp_hash % size] = true;
        }
    };

    // Method to check if the filter contains the item... possibly!
    bool possibly_contains(const std::string& item) {
        for (auto it = functions.begin(); it != functions.end(); it++) {
            size_t tmp = (*it)(item) % size;
            if(!exist[tmp])
                return false;
        }
        return true;
    };

    // Generate a hash function with a given seed.
    static std::function<size_t(const std::string&)> generate_hash_function(int seed) {
        std::hash<std::string> tmp_hash;
        return tmp_hash;
    };
};