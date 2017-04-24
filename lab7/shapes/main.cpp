//
// Created by pgorski42 on 25.04.17.
//

#include <Shapes.h>
#include <vector>
#include <memory>
#include <random>
#include <ctime>

using namespace std;

int main() {
    int limit = 5;
    Square s(limit);
    Triangle t(limit);
    Circle c(limit);

    s.Draw();
    t.Draw();
    c.Draw();

    vector<Shape*> shapes;

    // Primitive random number generator
    time_t time1;
    srand(time(&time1));

    for (auto i = 1; i < 6; ++i)
        shapes.push_back(new Circle(rand() % 10 + 1));

    // Wywoła funkcję klasy Circle
    // Klasa bazowa posiada deklarację funkcji wirtualnej Draw, czyli bez problemu można
    // wywołać funkcję Draw ze wskaźnika typu Shape* dla dowolnej pochodnej klasy Shape
    for (auto i : shapes)
        i->Draw();

    for (auto i : shapes)
        delete i;

    return 0;
}