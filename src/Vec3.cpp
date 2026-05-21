#include <math.h>
#include "Vec3.h"

namespace Raytracer {

// constructors
Vec3::Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

//destructor
Vec3::~Vec3(){
}

// operators
Vec3 Vec3::operator+(const Vec3& r) {
    return {x + r.x, y + r.y, z+ r.z};
}
Vec3 Vec3::operator-(const Vec3& r) {
        return {x - r.x, y - r.y, z - r.z};
}
Vec3 Vec3::operator*(const Vec3& r) {
    return {x * r.x, y * r.y, z * r.z};
}

// additional fucntions
float Vec3::length(){
    return sqrt(x*x + y*y + z*z);
}
Vec3 Vec3::normalize(){
    float lenght = length();
    return {x / lenght, y / lenght, z / lenght};
}

}