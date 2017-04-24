//
// Created by pgorski42 on 19.04.17.
//

#ifndef JIMP_EXERCISES_POINT3D_H
#define JIMP_EXERCISES_POINT3D_H

#include <Point.h>
#include <iostream>
#include <cmath>

class Point3D : public Point {
public:
    Point3D(double x = 0, double y = 0, double z = 0);
    virtual ~Point3D();

    void SetZ(double z_);

    double GetZ() const;

    double Distance(const Point3D point);

protected:
    double z_;
};

#endif //JIMP_EXERCISES_POINT3D_H
