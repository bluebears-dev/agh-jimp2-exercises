//
// Created by pgorski42 on 19.04.17.
//

#include "Point3D.h"

using std::cout;
using std::endl;

Point3D::Point3D(double x, double y, double z) : Point(x, y), z_(z) {
    cout << "Point3d ctor" << endl;
}

double Point3D::Distance(const Point3D point) {
    double x2 = pow(x_ - point.x_, 2),
           y2 = pow(y_ - point.y_, 2),
           z2 = pow(z_ - point.z_, 2);
    return sqrt(x2 + y2 + z2);
}

Point3D::~Point3D() {
    cout << "Point3D dtor" << endl;
}

double Point3D::GetZ() const {
    return z_;
}

void Point3D::SetZ(double z_) {
    Point3D::z_ = z_;
}
