//
// Created by mikipaw on 29.09.2020.
//

#ifndef STACK_STACK_H
#define STACK_STACK_H

#define NAME(var) #var

#include <cassert>
#include <cstdio>
#include <stdexcept>

int err = 0;
const long long strange_number = 0xDEADBEEF;


/*! \class Stack
 *  \brief This is a stack of memory for storage various elements.
 *  \param data - pointer to block of memory with elements.
 *  \param size - number of elements in Stack.
 *  \param capacity - number of maximum elements can be located in current block of memory.
 *  Some details about the Stack class.
 */
template<typename T>
class Stack{
private:
    const long long canary1 = strange_number;

public:
    Stack() = default;
    explicit
    Stack(size_t new_capacity):
        capacity (new_capacity),
        size     (0){
        data = (T*) calloc(capacity, sizeof(T));
    }

    explicit
    Stack(T* new_data, size_t number_of_elements):
        capacity (number_of_elements),
        size     (number_of_elements),
        data     (new_data){}

    int
    StackError(int error_number);

    /*!
    *  @method bool push(const T& item).
    *  @brief  Adds element in the end of the stack.
    *  It expands the Stack by one.
    *
    *  @return a bool - true if operation was successful, false - if not
    */
    bool
    push(T item);


    /*!
     *  @method T pop().
     *  @brief  Removes last element.
     *  It shrinks the Stack by one.
     *
     *  @return a T - the element that was destroyed
     */
    T
    pop();


    /*!
     *  @brief  Access to the data contained in the Stack.
     *  @param index The index of the element for which data should be
     *  accessed.
     *  @return  Reference to data.
     */
    T&
    operator[](size_t index);

    /*!
     *  @method void Destruct().
     *  @brief  Destroys the class.
     *
     *  @return nothing
     */
    void
    Destruct();

    size_t  Get_Size()      const;
    size_t  Get_Capacity()  const;
    T *     Get_Data()      const;

private:

    /*!
    *  @method void Expand(bool* flag).
    *  @brief  This method expands block of memory.
    *  @param flag a bool* - true if all is ok, false if expand was unsuccessful.
    *
    *  @return nothing
    */
    void
    Expand(bool* flag);

    /*!
    *  @method void Decrease().
    *  @brief  This method decreases block of memory.
    *
    *  @return nothing
    */
    void
    Decrease();

    /*!
    *  @method bool Stack_OK.
    *  @brief  This method checks if stack is OK.
    *
    *  @return bool - true if stack is ok, false if it is not ok.
    */
    bool
    Stack_OK();


private:
    T* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;
    const long long canary2 = strange_number;
};

template<typename T>
void Stack_info(const Stack<T>& stk);

template<typename T>
void Stack<T>::Destruct(){
    this->Stack_OK();
    assert(this);
    free(data);
    *data = 13;
    size = -1;
    capacity = -1;
}

template<typename T>
T Stack<T>::pop(){
    this->Stack_OK();
    assert(this);
    if(size == 0) {
        fprintf(stderr, "Logic error at line %d:\n"
                        "It is impossible to delete an element from empty stack\n", __LINE__);
        exit(3);
    }
    if(size - 1 < capacity/4) Decrease();
    this->Stack_OK();
    return data[size--];
}

template<typename T>
bool Stack<T>::push(T item){
    this->Stack_OK();
    assert(this);
    bool flag = true;
    if (size == capacity) Expand(&flag);
    data[size++] = item;
    this->Stack_OK();
    return flag;
}

template<typename T>
int Stack<T>::StackError(int error_number){
    switch (error_number) {
        case 1:

        case 2:

        default:
            fprintf(stderr, "Unknown error!\n");
            Stack_info(this);
            exit(11);
    }
    return 0;
}

template<typename T>
T& Stack<T>::operator[](size_t index){
    if(index < 0 || index >= size) {
        fprintf(stderr, "Out of range error at line %d:\n"
                        "Index %d is out of range!\n", __LINE__, index);
        exit(3);
    }
    return data[index];
}

template<typename T>
void Stack<T>::Expand(bool* flag) {
    (capacity*=2)++;
    data = (T*) realloc(data, capacity*sizeof(T));
    if(data == nullptr) *flag = false;
}

template<typename T>
void Stack<T>::Decrease() {
    capacity/=2;
    data = (T*) realloc(data, capacity*sizeof(T));
}

template<typename T>
bool Stack<T>::Stack_OK() {
    if(this == nullptr) {   //NULL POINTER
        err = 1;
        StackError(err);
        return false;
    }
    if(size > capacity) {   // BAD SIZE
        err = 2;
        StackError(err);
        return false;
    }
    if(this->data == nullptr) { //NULL POINTER
        err = 1;
        StackError(err);
        return false;
    }
    if(canary1 != strange_number || canary2 != strange_number){ //CANARY WAS HIT
        err = 3;
        StackError(err);
        return false;
    }
    return true;
}

template<typename T>
size_t Stack<T>::Get_Size() const { return size; }

template<typename T>
size_t Stack<T>::Get_Capacity() const { return capacity; }

template<typename T>
T* Stack<T>::Get_Data() const { return data; }


template<typename T>
void Stack_info(const Stack<T>& stk){
    printf("Stack = [%p], \"10s\"\n", stk, NAME(stk));
    printf("{\n");
    printf("\tsize = %d\n", stk.Get_Size());
    printf("\tcapacity = %d\n", stk.Get_Capacity());
    printf("\tdata [%p]\n", stk.Get_Data());
    printf("\t{\n");
    for(int i = 0; i < stk.Get_Capacity(); ++i){
        printf("\t\t[%d] = %s\n", i, NAME(stk[i]));
    }
    printf("\t}\n");
}


#endif //STACK_STACK_H
