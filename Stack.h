//
// Created by mikipaw on 29.09.2020.
//

#ifndef STACK_STACK_H
#define STACK_STACK_H

#include <cstdio>

const void* ERRPTR = (void*) 13;

template<typename T>
class Stack{
public:
    Stack() = default;
    explicit Stack(size_t new_capacity):
        capacity (new_capacity),
        size     (0){}

    explicit Stack(T* new_data, size_t number_of_elements):
        capacity (number_of_elements),
        size     (number_of_elements),
        data     (new_data){}

    int StackError();

    bool push(const T& item);

    T pop();

    T& operator[](size_t index);

    void Destruct();

private:
    void Expand(bool* flag);
    void Decrease();

private:
    T* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;
};




#endif //STACK_STACK_H
