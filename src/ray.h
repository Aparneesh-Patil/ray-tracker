#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray{
    public:
        // constructors
        ray(){}
        ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

        // accessors
        const point3& origin() const  { return orig; }
        const vec3& direction() const { return dir; }

        // given a time t, gets you the point at which the ray is at (makes sure the object isn't changed)
        point3 at(double t) const{
            return orig + t*dir;
        }

    private:
        point3 orig;
        vec3 dir;
};


#endif