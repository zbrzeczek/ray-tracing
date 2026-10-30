#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
private:
    point3 origin;
    vec3 direction;

public:
    ray(const vec3& o, const vec3& d) : origin(o), direction(d) {}

    // getery
    point3 getOrigin() const { return origin; }
    point3 getDirection() const { return direction; }

    point3 at(double t) {
        return origin + t * direction;
    }
};

#endif