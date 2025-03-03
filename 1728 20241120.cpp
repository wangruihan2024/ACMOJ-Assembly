#include<algorithm>

void Init(int **&p,int n){//初始化，n为vector的个数,传入的p指向nullptr
    //todo
    p = new int *[n];
    for (int i = 0; i < n; i++)
        p[i] = nullptr;
}
void Add_element(int **&p,int x,int y){//在第x(1base)个vector后面添加一个元素y
    //todo
    int* temp = p[x - 1];
    int size, capacity = 0;
    if(temp == nullptr)
        size = 0;
    else {
        size = temp[0];
        capacity = temp[1];
    }
    if(size == capacity) {
        if(capacity == 0)
            capacity++;
        else
            capacity *= 2;
        int *sub = new int[capacity + 2];
        sub[0] = size;
        sub[1] = capacity;
        for (int i = 0; i < size; i++)
            sub[2 + i] = temp[2 + i];
        delete[] temp;
        temp = sub;
    }
    temp[0] = size + 1;
    temp[2 + size] = y;
    p[x - 1] = temp;
}
int Get_element(int **&p,int x,int k){//获取第x(1base)个vector中第k个(1-base)元素的值
    //todo
    return p[x - 1][k + 1];
}
void Clear(int **&p,int n){//回收空间
    //todo
    for (int i = 0; i < n; i++)
        delete[] p[i];
    delete[] p;
    p = nullptr;
}