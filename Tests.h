//
// Created by mikipaw on 29.09.2020.
//
#pragma once
#ifndef STACK_TESTS_H
#define STACK_TESTS_H
#include "Stack.h"

#define DIE fprintf(stderr, "Assertion failed!\nERROR on line %d\n", __LINE__);

#define asserted || DIE

void First_test();
void Second_test();
void Third_test();


void AllTests();
#endif //STACK_TESTS_H

