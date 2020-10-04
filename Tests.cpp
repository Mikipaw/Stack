//
// Created by pawlo on 02.10.2020.
//


#include "Tests.h"

void First_test(){
    Stack<int> stk = Stack<int>(5);
    stk.push(2);
    stk.push(4);
    assert(stk[1] == 4);
    stk.Destruct();

    fprintf(stderr, "First test is OK!\n");
}
