// "Wrapper": src.hpp
#ifndef Wrapper_CPP_Wrapper_HPP
#define Wrapper_CPP_Wrapper_HPP

#include <string>

struct Wrapper {        
    void (*function)(std::string); 
    void (*before)();
    void (*after)();
    Wrapper* next;          
    Wrapper(void (*f)(std::string), void (*b)(), void (*a)())
        : function(f), before(b), after(a), next(nullptr) {}
};
// todo: add definition for link list
Wrapper* head = nullptr;
Wrapper* rear = nullptr;
// todo: create()
Wrapper* create(void(*function)(std::string), void(*before)(), void(*after)()) {
    Wrapper* new_node = new Wrapper(function, before, after);
    if(head == nullptr) {
        head = new_node;
        rear = new_node;
    }else {
        rear->next = new_node;
        rear = new_node;
    }
    return new_node;
}

// todo: remove()
void remove(Wrapper* name) {
    if (head == nullptr) return;
    if(head == name) {
        head = head->next;
        if(head == nullptr)
            rear = nullptr;
        delete name;
        return;
    }
    Wrapper* temp = head;
    Wrapper* prev = nullptr;
    while (temp != nullptr && temp != name) {
        prev = temp;
        temp = temp->next;
    }
    if (temp != nullptr) {
        prev->next = temp->next;
        if(temp == rear)
            rear = prev;
        delete name;
        return;
    }
}
//todo:run()
void run(Wrapper* pos, std::string id) {
    if(pos == nullptr)
        return;
    pos->before();
    pos->function(id);
    pos->after();
}
// todo: destroy()
void destroy() {
    while (head != nullptr) {
        Wrapper* n = head->next;
        delete head;
        head = n;
    }
    head = nullptr;
    rear = nullptr;
    return;
}
#endif //Wrapper_CPP_Wrapper_HPP