#include <iostream>
#include <cstring>

int n;
// 写出两个函数的声明
int*& funA(int**& p) {
    p = new int*;
    return *p;
}
void funB(int* c, int** p, int** q) {
    int* pos1 = *p;
    int* pos2 = *q;
    for (int i = 0; i < n; i++)
        c[i] = pos1[i] * pos2[i];
}
int main() {
    int a[100], b[100], c[100];
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i];
    }
    int **p = nullptr;
    int **q = nullptr;
    funA(p) = a;
    funA(q) = b;
    funB(c, p, q);
    for (int i = 0; i < n; ++i) {
        std::cout << c[i] << " ";
    }
    delete p;
    delete q;
    return 0;
}

// 写出两个函数的定义