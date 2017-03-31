//
// Created by pgorski42 on 31.03.17.
//

#include "ReverseString.h"

using namespace std;

string reverse(string str) {
    string reversed("");
    for (auto i = str.end() - 1; i >= str.begin(); --i)
        reversed += *i;
    return reversed;
}