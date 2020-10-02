//
// Created by pawlo on 01.10.2020.
//

#include <cstdlib>
#include <stdexcept>
#include "Stack.h"


template<typename T>
void Stack<T>::Destruct(){
    assert(this);
    free(data);
    data = ERRPTR;
    size = -1;
    capacity = -1;
}

template<typename T>
T Stack<T>::pop(){
    assert(this);
    if(size == 0) throw std::logic_error("It is impossible to delete element from empty stack\n");
    if(size - 1 < capacity/4) Decrease();
    return data[size--];
}

template<typename T>
bool Stack<T>::push(const T& item){
    assert(this);
    bool flag = true;
    if (size == capacity) Expand(&flag);
    data[size] = item;
    return flag;
}

template<typename T>
int Stack<T>::StackError(){

}

template<typename T>
T& Stack<T>::operator[](size_t index){
    return data[index];
}

template<typename T>
void Stack<T>::Expand(bool* flag) {
    (capacity*=2)++;
    data = (T*) realloc(nullptr, capacity*sizeof(T));
    if(data == nullptr) *flag = false;
}

template<typename T>
void Stack<T>::Decrease() {
    capacity/=2;
    data = (T*) realloc(data, capacity*sizeof(T));
}