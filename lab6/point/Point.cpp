//Definicja w Point.cpp
#include "Point.h"

using std::istream;
using std::runtime_error;
using std::ostream;
using std::ws;
using std::cout;
using std::endl;

//Helper functions:
void CheckNextChar(char c, istream* is) {
    int next_char = is->peek();
    if (next_char != c) {
        throw runtime_error("invalid character");
    }
    is->ignore();
}

void IgnoreWhitespace(istream* is) {
    (*is) >> ws;
}

double ReadNumber(istream* is) {
    double d;
    (*is) >> d;
    return d;
}


void Point::SetX(double x) {
    x_ = x;
}

void Point::SetY(double y) {
    y_ = y;
}

// Właściwa definicja, obydwa argumenty funkcji nie
//są zadeklarowane jako const, bo obydwa są modyfikowane
//wewnątrz funkcji (STL nie używa naszej konwencji z przekazywaniem
//przez wskaźnik)
istream& operator>>(istream & input, Point& p){
    CheckNextChar('(', &input);
    p.SetX(ReadNumber(&input));
    CheckNextChar(',', &input);
    IgnoreWhitespace(&input);
    p.SetY(ReadNumber(&input));
    CheckNextChar(')', &input);
    return input;      // Umożliwia cin >> a >> b >> c;
}

ostream &operator<<(ostream &os, Point &point) {
    os << "(" << point.x_ << ", " << point.y_ << ")";
    return os;
}

Point::Point(double x, double y) : x_(x), y_(y) {
    cout << "Point ctor" << endl;
}

Point::~Point() {
    cout << "Point dtor" << endl;
}

double Point::Distance(const Point &other) const{
    return sqrt(pow(GetX()-other.GetX(),2)+pow(GetY()-other.GetY(),2));
}

double Point::GetX() const {
    return x_;
}

double Point::GetY() const {
    return y_;
}
