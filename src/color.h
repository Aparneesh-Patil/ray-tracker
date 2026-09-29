#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>

using color = vec3;

inline void write_color(std::ostream& os, const color& pixel_color){
    double r = pixel_color.x();
    double g = pixel_color.y();
    double b = pixel_color.z();

    os << int(255.999 * r) << " " << int(255.999 * g) << " " << int(255.999 * b) << "\n";
} 

#endif