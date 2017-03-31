//
// Created by pgorski42 on 31.03.17.
//

#include "DoubleBasePalindromes.h"

using namespace std;

string to_binary(int number) {
    string binary("");
    do {
        binary += number % 2 + '0';
        number /= 2;
    } while (number > 0);
    return reverse(binary);
}

uint64_t DoubleBasePalindromes(int max_value_exclusive) {
    uint64_t sum = 0;
    for (auto i = 1; i < max_value_exclusive; ++i) {
        if (i % 10 and i % 2)
            if (is_palindrome(to_string(i)) and is_palindrome(to_binary(i)))
                sum += i;
    }
    return sum;
}
