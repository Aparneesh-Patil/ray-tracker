#include <stdio.h>
#include <iostream>
#include <cmath>
#include "color.h"
#include "ray.h"

// returns the t at which the ray hits the sphere
double hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = center - r.origin();

    // Simplified sphere interaction
    double a = r.direction().length_squared();
    double h = dot(r.direction(), oc);
    double c = oc.length_squared() - radius*radius;
    double discriminant = h*h - a*c;

    return discriminant < 0 ? -1.0 : (h - std::sqrt(discriminant)) / a; 
}

// ray for each pixel
color ray_color(const ray& r){

    // normal visualization that gives the sphere a 3d look
    double t = hit_sphere(point3(0,0,-1), 0.5, r);
    if (t > 0.0) {
        vec3 N = unit_vector(r.at(t) - vec3(0,0,-1));
        return 0.5*color(N.x()+1, N.y()+1, N.z()+1);
    }

    // background color
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
};

int main(){
    // image generation
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // make sure the image height is atleast 1
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // camera
    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * (double(image_width)/image_height);
    point3 camera_center = point3(0, 0, 0);

    // vector viewpoints for u and v
    vec3 viewport_u = vec3(viewport_width, 0, 0);
    vec3 viewport_v = vec3(0, -viewport_height, 0);

    // pixel delta vectors
    vec3 pixel_delta_u = viewport_u / image_width;
    vec3 pixel_delta_v = viewport_v / image_height;

    // upperleft viewport pixel
    auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    auto upper_left_pixel_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // rendering for each pixel
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            auto pixel_center = upper_left_pixel_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
}