//
// Created by pgorski42 on 19.04.17.
//

#include <iostream>
#include <Point3D.h>

using namespace std;

int main() {
    // Najpierw wyświetli "Point ctor", póżniej "Point3D ctor"

    // W przypadku destruktora kolejność będzie odwrotna ze względu na to, że
    // desktruktor jest wirtualny - zostaną wywołane dwa desktruktory ~Point3D, a po nim ~Point
    Point3D pt3d(1, 2, 3);
    Point pt2d(1, 1);
    // Nastąpi rzutowanie w górę do klasy bazowej Point obiektu pt3d
    cout << pt2d.Distance(pt3d) << endl;
    // Zostanie wywołany operator<< dla klasy bazowej, czyli ponownie
    // pt3d jest rzutowane w górę do klasy bazowej
    cout << pt3d << endl;
    return 0;
}