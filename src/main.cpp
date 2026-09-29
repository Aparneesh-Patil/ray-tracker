#include <stdio.h>
#include <iostream>
#include "color.h"

int main(){
    int image_width = 256;
    int image_height = 256;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    // rendering
    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            color pixel_color = color(double(j) / (image_width-1), double(i) / (image_height-1), 0.0);
            write_color(std::cout, pixel_color);
        }
    }
}