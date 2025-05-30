#include <iostream>
#include <unordered_map>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
 int longestPalindrome(vector<string>& words) {
    unordered_map<string, int> freq;
    for(string s : words)
        freq[s]++;
    int length = 0;
    bool center = false;
    for(auto& [word, count]: freq) {
        if(word[1] == word[0]) {
            length += ((int)count / 2) * 4;
            if(!center)
                center = count % 2;
        }else {
            string word_ = string() + word[1] + word[0];
            if(freq.count(word_)) {
                int num = std::min(count, freq[word_]);
                length += num * 4;
                freq[word] = 0;
                freq[word_] = 0;
            }
        }
    }
    if(center)
        length += 2;
    return length;
 }
};

int main() {
    Solution s;
    vector<string> words_ = {"lc","cl","gg"};
    cout << s.longestPalindrome(words_) << endl;
}