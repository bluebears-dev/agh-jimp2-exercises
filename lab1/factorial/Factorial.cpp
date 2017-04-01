//
// Created by mwypych on 02.02.17.
//
#include "Factorial.h"


int Factorial(int value) {
    auto factorial = 1;

    // abs(number) > 12 will overflow for int type
    if (-12 <= value and value < 0)
        for (auto i = value; i < 0; ++i)
            factorial *= i;
    else if (0 <= value and value <= 12)
        for (auto i = 2; i <= value; ++i)
            factorial *= i;
    else
        return 0;

    return factorial;
}
