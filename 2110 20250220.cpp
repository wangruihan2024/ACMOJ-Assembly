#include <iostream>
#include "2110 20250222.hpp"
// using namespace std;

int main() {
    // Node<int> a(1, 5);
    SkipList<char> s;
    std::cout << s.search('c') << std::endl;
    s.insert('c');
    std::cout << "1" << std::endl;
    std::cout << s.search('c') << std::endl;
    std::cout << "2" << std::endl;
    std::cout << s.search('d') << std::endl;
    std::cout << "3" << std::endl;
    s.insert('e');
    std::cout << "4" << std::endl;
    s.insert('f');
    s.display();
    std::cout << "5" << std::endl;
    s.deleteItem('e');
    std::cout << "6" << std::endl;
    s.display();
    std::cout << "7" << std::endl;
    return 0;
}