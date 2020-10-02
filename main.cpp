
#include <cstdio>
#include <cassert>

#include "Stack.h"
#include "Tests.h"

#define DIE printf("ERROR on line %d\n", __LINE__)
#define asserted || DIE

int main() {
    AllTests();
    Stack<double> stk = {};
    stk = Stack<double>(10);
    assert(stk.StackError());
    stk.push(100) asserted;
    stk.push(200) asserted;

    stk.pop() == 200 asserted;

    stk.Destruct();

    return 0;
}
