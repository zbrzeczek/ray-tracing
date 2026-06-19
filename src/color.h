#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

using color = vec3;

void make_color(std::ostream& out, const color& pixel){
    auto r = pixel.x();
    auto g = pixel.y();
    auto b = pixel.z();

    int ir = int(255.999 * r);
    int ig = int(255.999 * g);
    int ib = int(255.999 * b);

    out << ir << ' ' << ig << ' ' << ib << '\n';
}


#endif