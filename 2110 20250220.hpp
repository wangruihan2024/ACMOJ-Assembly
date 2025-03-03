#ifndef SKIP_LIST_HPP
#define SKIP_LIST_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <climits>
template<typename T>
class Node {
public:
    T *value;
    std::vector<Node<T>*> forward;
    Node(int level) {
        value = nullptr;
        forward = std::vector<Node<T> *>(level, nullptr);
    }
    Node(T val, int level) {
        value = new T(val);
        forward = std::vector<Node<T> *>(level, nullptr);
    }
    ~Node() {
        if(value != nullptr)
            delete value;
    }
};
static constexpr int maxlevel = 32;
template<typename T>
class SkipList {
private:
    //add whatever you want here
    int level;
    Node<T> *head;
    int randomlevel() {
        int tmp_level = 1;
        while (rand() % 2 == 0 && tmp_level < maxlevel)
            tmp_level++;
        return tmp_level;
    }
public:
    SkipList() {
        level = 1;
        head = new Node<T>(maxlevel);
        srand(time(0));
    };
    ~SkipList() {
        Node<T> *tmp = head;
        while(tmp != nullptr) {
            Node<T>* nxt = tmp->forward[0];
            delete tmp;
            tmp = nxt;
        }
    };
    // Insert a value into the skip list. If the value already exists, do nothing.
    void insert(const T & item) {
        Node<T> *tmp = head;
        std::vector<Node<T>*> revise(maxlevel, nullptr);
        for (int tmp_level = level - 1; tmp_level >= 0; tmp_level--)
        {
            while(tmp->forward[tmp_level] != nullptr && *(tmp->forward[tmp_level]->value) < item)
                tmp = tmp->forward[tmp_level];
            revise[tmp_level] = tmp;
        }
        tmp = tmp->forward[0];
        if(tmp == nullptr || !(item < *(tmp->value)))
            return;
        int new_level = randomlevel();
        if(new_level > level) {
            for (int tmp_level = level; tmp_level < new_level; tmp_level++)
                revise[tmp_level] = head;
            level = new_level;
        }
        Node<T> *add = new Node<T>(item, new_level);
        for (int i = 0; i < new_level; i++) {
            add->forward[i] = revise[i]->forward[i];
            revise[i]->forward[i] = add;
        }
        // delete tmp;
    };

    // Search for a value in the skip list
    bool search(const T & item) {
        Node<T> *tmp = head;
        for (int tmp_level = level - 1; tmp_level >= 0; tmp_level--) {
            // if(tmp->forward[tmp_level] == nullptr)
            //     continue;
            while(tmp->forward[tmp_level] != nullptr && *(tmp->forward[tmp_level]->value) < item) {
                tmp = tmp->forward[tmp_level];
            }
        }
        if(tmp->forward[0] != nullptr) {
            if(*(tmp->forward[0]->value) < item || item < *(tmp->forward[0]->value))
                return false;
            else
                return true;
        }
        return false;
    };

    // Delete a value from the skip list. If the value does not exist in the skip list, do nothing.
    void deleteItem(const T & item) {
        std::vector<Node<T>*> revise(maxlevel, nullptr);
        Node<T>* tmp = head;
        for (int tmp_level = level - 1; tmp_level >= 0; tmp_level--) {
            while(tmp->forward[tmp_level] && *(tmp->forward[tmp_level]->value) < item) {
                tmp = tmp->forward[tmp_level];
            }
            revise[tmp_level] = tmp;
        }
        tmp = tmp->forward[0];
        if(tmp == nullptr || (item < *(tmp->value)))
            return;
        for (int i = 0; i < level; i++) {
            if(revise[i]->forward[i] != tmp)
                break;
            revise[i]->forward[i] = tmp->forward[i];
        }
        delete tmp;
        while(level > 1  && head->forward[level - 1] == nullptr)
            level--;
    };

    void display() {
        Node<T>* tmp = head->forward[0];  
        while (tmp != nullptr) {
            if (tmp->value != nullptr) {  
                std::cout << *(tmp->value) << " "; 
            }
            tmp = tmp->forward[0]; 
        }
        std::cout << std::endl;
    }
};

#endif