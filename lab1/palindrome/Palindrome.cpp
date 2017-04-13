//
// Created by pgorski42 on 31.03.17.
//

#include "Palindrome.h"

#include <iostream>

bool IsPalindrome(std::string str) {
    auto left = str.begin() - 1,
         right = str.end();

    while (left++ < right--) {
        if (*left != *right)
            return false;
    }
    return true;
}
