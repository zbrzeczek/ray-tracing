#ifndef VEC3_H
#define VEC3_H

#include <math.h>

class Vec3
{
private:
    float x, y, z;

public:
    Vec3();
    Vec3(float x, float y, float z);
    ~Vec3();

    Vec3 operator+ (const Vec3& r);
    Vec3 operator- (const Vec3& r);
    Vec3 operator* (const Vec3& r);


    float length();
    Vec3 normalize();

    // TODO dodaj tutaj
    // - dot operation
};

#endif