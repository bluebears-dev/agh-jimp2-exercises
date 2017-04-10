//
// Created by pgorski42 on 04.04.17.
//

#include <iostream>
#include <sstream>
#include <Point.h>

using namespace std;

int main() {
    Point point;
    point.SetX(1.0);
    point.SetY(3.0);
    cout << point << endl;
    cin >> point;
    cout << point << endl;
    stringstream sstr;
    sstr << point;
    cout << sstr.str() << endl;
    return 0;
}