//
// Created by mikipaw on 29.09.2020.
//
#pragma once
#ifndef STACK_STACK_H
#define STACK_STACK_H


#define NAME(var) #var


#include <cassert>
#include <cstdio>
#include <stdexcept>

const long long STRANGE_NUMBER = 0xDEADBEEF;


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
    const long long canary1 = STRANGE_NUMBER;

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

    const T&
    at(int index) const;

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
    *  @method bool Stack_OK().
    *  @brief  This method checks if stack is OK.
    *
    *  @return bool - true if stack is ok, false if it is not ok.
    */
    bool
    Stack_OK();

    /*!
    *  @method bool Zero(T element).
    *  @brief  This method checks if element is zero.
    *
    *  @return bool - true if element is zero, false it is not zero.
    */
    bool
    Zero(T element);

private:
    T* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;

    const long long canary2 = STRANGE_NUMBER;
};


/*!@function charsum(const char* string)
 * @brief This function finds sum of chars of the string
 * @param string
 * @return an integer - sum of chars
 */
int charsum(const char* string);

template<typename T>
void Stack_info(const Stack<T>& stk);

template<typename T>
void Print_template_type(const T& var_name);


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
        exit(6);
    }

    if(size - 1 < capacity/4) Decrease();
    size--;

    T result = data[size];
    data[size] = 0;

    this->Stack_OK();
    return result;
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
            fprintf(stderr, "Bad pointer!\n");
            break;

        case 2:
            fprintf(stderr, "Size is bad!\n");
            break;

        case 3:
            fprintf(stderr, "Canary was hit!\n");
            break;
        case 4:
            fprintf(stderr, "Unused elements was changed!");
            break;

        default:
            fprintf(stderr, "Unknown error!\n");
            Stack_info(*this);
            exit(11);
    }
    Stack_info(*this);
    exit(1);
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
    if (data == nullptr) *flag = false;

    for (int i = size; i < capacity; ++i) data[i] = 0;
}

template<typename T>
void Stack<T>::Decrease() {
    capacity/=2;
    data = (T*) realloc(data, capacity*sizeof(T));
}

template<typename T>
bool Stack<T>::Stack_OK() {
    int ERR = 0;

    if(this == nullptr) {   //NULL POINTER
        ERR = 1;
        StackError(ERR);
        return false;
    }

    if(size > capacity) {   // BAD SIZE
        ERR = 2;
        StackError(ERR);
        return false;
    }

    if(this->data == nullptr) { //NULL POINTER
        ERR = 1;
        StackError(ERR);
        return false;
    }

    if(canary1 != STRANGE_NUMBER || canary2 != STRANGE_NUMBER) { //CANARY WAS HIT
        ERR = 3;
        StackError(ERR);
        return false;
    }

    for(int i = size; i < capacity; ++i) {
        if (!Zero(data[i])) {
            ERR = 4;
            StackError(ERR);
        }

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
const T& Stack<T>::at(int index) const {
    return *(data + index);
}

template<typename T>
void Print_template_type(const T& var_name){
    int a = charsum(typeid(var_name).name());
    switch (a) {
        case 105:
            printf("%d " , var_name);
            break;

        case 99:
            printf("%c " , var_name);
            break;

        case 254:
            printf("%s ", var_name);
            break;

        case 179:
            printf("%s ", var_name);

        case 102:
            printf("%f", var_name);

        case 100:
            printf("%lf", var_name);

        default:
            printf("unknown type\n");
            fprintf(stderr, "Unknown type!\n");
            return;
    }
}

/*!
 * @function str_cmp(const char* str1, const char* str2)
 * @brief Function compares 2 strings
 * @param str1
 * @param str2
 * @return true if strings are equal, false if not
 */
int str_cmp(const char* str1, const char* str2);

template<typename T>
void Stack_info(const Stack<T>& stk){
    printf("Stack = [%p], \"%s\"\n",    &stk, NAME(stk));
    printf("{\n");
    printf("\tsize = %d\n",             stk.Get_Size());
    printf("\tcapacity = %d\n",         stk.Get_Capacity());
    printf("\tdata [%p]\n",             stk.Get_Data());
    printf("\t{\n");

    for(int i = 0; i < stk.Get_Capacity(); ++i){
        printf("\t\t[%d] = ", i);
        Print_template_type(stk.at(i));
        printf("\n");
    }
    printf("\t}\n");
}

template<typename T>
bool Stack<T>::Zero(T element){
    const char* typ = typeid(element).name();
    if(str_cmp(typ, "f") || str_cmp(typ, "i")) return element == 0;
    if(str_cmp(typ, "CKp") || str_cmp(typ, "Cp")) return str_cmp(element, "");

    return (element < 10e-6 && element > -10e-6);
}


#endif //STACK_STACK_H
