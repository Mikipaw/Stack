//
// Created by pawlo on 02.10.2020.
//


#include "Tests.h"

void AllTests(){
    //First_test();
    //Second_test();
    Third_test();
    fprintf(stderr, "All tests are OK!\n");
}

void First_test(){
    Stack<int> stk = Stack<int>(5);
    stk.push(2);
    stk.push(4);
    stk.push(88);

    stk[1] == 4             asserted;
    stk[2] == 88            asserted;
    stk.Get_Capacity() == 5 asserted;
    stk.Get_Size() == 3     asserted;

    stk.pop() == 88         asserted;
    stk.Get_Size() == 2     asserted;
    stk.Get_Capacity() == 5 asserted;

    stk.push(1);
    stk.push(0);
    stk.push(988);

    stk.Get_Capacity() == 5 asserted;

    stk.push(123);

    stk.Get_Capacity() == 11 asserted;

    Stack_info(stk);
    stk.Destruct();

    fprintf(stderr, "First test is OK!\n");
}

void Second_test(){
    const char* str = "String";

    if (str_cmp (typeid(str).name(), "PKc")) fprintf(stderr, "Second test is OK!\n");
    else fprintf(stderr, "Second test was failed!\n%s != PKc\n", typeid(str).name());
}

void Third_test() {
    int i = 0;
    double d = 0;
    const char* ccp = "string";
    char* cp = nullptr;
    float f = 3;
    char c = 0;

    int sum1 = charsum(typeid(i).name());
    int sum2 = charsum(typeid(d).name());
    int sum3 = charsum(typeid(ccp).name());
    int sum4 = charsum(typeid(cp).name());
    int sum5 = charsum(typeid(f).name());
    int sum6 = charsum(typeid(c).name());

    sum1 == 105 asserted;
    sum2 == 100 asserted;
    sum3 == 254 asserted;
    sum4 == 179 asserted;
    sum5 == 102 asserted;
    sum6 == 99  asserted;

    fprintf(stderr, "Third test is OK!\n");
}
