//
// Created by pgorski42 on 25.04.17.
//

#ifndef JIMP_EXERCISES_SHAPES_H
#define JIMP_EXERCISES_SHAPES_H

#include <iostream>
#include <cmath>

class Shape {
public:
    Shape(int limit = 0) : limit_(limit) {};
    virtual ~Shape() = default;

    virtual void Draw() const = 0;

protected:
    int limit_;
};

class Square : public Shape {
public:
    Square(int limit = 0) : Shape(limit) {};
    virtual ~Square() = default;

    virtual void Draw() const override;
};

class Circle : public Shape {
public:
    Circle(int limit = 0) : Shape(limit) {};
    virtual ~Circle() = default;

    virtual void Draw() const override;
};

class Triangle : public Shape {
public:
    Triangle(int limit = 0) : Shape(limit) {};
    virtual ~Triangle() = default;

    virtual void Draw() const override;
};

#endif //JIMP_EXERCISES_SHAPES_H
