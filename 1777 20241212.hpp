#ifndef ARRAY_LIST_HPP
#define ARRAY_LIST_HPP

#include <iostream>

#define USE_OS

// Don't delete the error class below.
// 不要删除下面的错误类
class error : public std::exception {
private:
    std::string msg;

public:
    explicit error(const char *_msg_) : msg(_msg_) {}

    const char *toString() {
        return msg.c_str();
    }
};
template <typename T>
class ArrayList {
private:
    // todo
    T* p;
    int length;
    void release() {
        length = 0;
        delete[] p;
        p = nullptr;
    }
public:
    ArrayList() {
        p = nullptr;
        length = 0;
    }
    ArrayList(T *arr, int length) {
        this->length = length;
        if(length < 0)
            throw error("invalid length");
        p = new T[length];
        for (int i = 0; i < length; i++)
            p[i] = arr[i];
    };
    ArrayList(int length) {
        this->length = length;
        if(length < 0)
            throw error("invalid length");
        p = new T[length];
        for (int i = 0; i < length; i++)
            p[i] = T();
    }
    ArrayList(const ArrayList& other) {
        length = other.length;
        p = new T[length];
        for (int i = 0; i < length; i++)
            p[i] = other.p[i];
    }
    // constructor with a given array (T* arr, int length) 从已有的数组构造
    // constructor with fixed length (int length) 构造一个固定长度的数组
    // copy constructor 拷贝构造函数
    int size() const {
        return length;
    }
    // size()
    T& operator[] (int index) {
        if(index < 0 || index >= size())
            throw error("index out of bound");
        return p[index];
    }
    const T& operator[] (int index) const {
         if(index < 0 || index >= size())
            throw error("index out of bound");
        return p[index];
    }
    // operator[]
    ArrayList operator+ (const ArrayList<T>& other) const{
        ArrayList<T> result(this->length + other.length);
        for (int i = 0; i < this->length; i++) 
            result[i] = this->p[i];
        for (int i = 0; i < other.length; i++)
            result[this->length + i] = other.p[i];
        return result;
    }
    // operator+ 
    ArrayList& operator= (const ArrayList<T> &other) {
        if(this == &other)
            return *this;
        release();
        length = other.length;
        p = new T[length];
        for (int i = 0; i < length; i++)
            p[i] = other.p[i];
        return *this;
    }
    // operator=
    // operator==
    bool operator== (const ArrayList<T> &other) const{
        if(length != other.length)
            return false;
        for (int i = 0; i < length; i++) 
            if(p[i] != other.p[i])
                return false;
        return true;
    }
    // operator!=
    bool operator!= (const ArrayList<T> &other) {
        if(*this == other)
            return false;
        return true;
    }
#ifdef USE_OS
    // operator<<
    friend std::ostream& operator<<(std::ostream& os, const ArrayList& array) {
        for (int i = 0; i < array.length; ++i) {
            os << array.p[i];
            if (i != array.length - 1) {
                os << " ";
            }
        }
        return os;
    }

#else
    // Notice: if you don't know how to implement operator<<,
    // you can use the following two print() functions AND COMMENT
    // "#define USE_OS" IN LINE 6 to enable your print functions.
    // 如果你不知道如何重载 operator<< ，请并注释掉
    // 第六行的 "#define USE_OS" 使得你的 print() 函数能够正常使用。
    void print() {
        for (int i = 0; i < length; i++)
            std::cout << arr[i] << " ";
    }
    void print() const {
        for (int i = 0; i < length; i++)
            std::cout << arr[i] << " ";
    }

#endif
    ~ArrayList() {
        release();
    }
    //destructor 析构函数
};

#endif // ARRAY_LIST_HPP