//
// Created by pgorski42 on 25.04.17.
//

#include "Shapes.h"

using std::cout;
using std::endl;

void Square::Draw() const {
    for (auto i = 0; i < limit_; ++i) {
        for (auto j = 0; j < limit_; ++j)
            cout << '*';
        cout << endl;
    }
}

void Circle::Draw() const {
    int radius = (limit_ - 1) / 2;
    for (auto i = 0; i < limit_; ++i) {
        for (auto j = 0; j < limit_; ++j)
            if (pow(i - radius, 2) + pow(j - radius, 2) <= pow(radius, 2))
                cout << '*';
            else
                cout << " ";
        cout << endl;
    }
}

void Triangle::Draw() const {
    for (auto i = 0; i < limit_; ++i) {
        for (auto j = 0; j <= i; ++j)
            cout << '*';
        cout << endl;
    }
}
