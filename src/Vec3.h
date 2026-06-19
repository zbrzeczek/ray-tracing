#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <math.h>

class vec3
{
private:
    double e[3];

public:
    vec3() : e{0,0,0} {}
    vec3(double x, double y, double z) : e{x,y,z} {}
    ~vec3() {}

    double x() const {return e[0];};
    double y() const {return e[1];};
    double z() const {return e[2];};

    // operatory
    vec3 operator-(){
        return {-e[0], -e[1], -e[2]};
    }
    vec3& operator+=(const vec3& r) {
        e[0] += r.e[0];
        e[1] += r.e[1];
        e[2] += r.e[2];
        return *this;
    }
    vec3& operator*=(double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }
    vec3& operator/=(double t) {
        e[0] /= t;
        e[1] /= t;
        e[2] /= t;
        return *this;
    }
    
    // additional fucntions
    double length() const {
        return sqrt(lenght_squared());
    }
    double lenght_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }
};

using point3 = vec3;

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

inline vec3 operator+ (const vec3& v1, const vec3& v2){
    return vec3(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
}
inline vec3 operator- (const vec3& v1, const vec3& v2){
    return vec3(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z());
}
inline vec3 operator* (const vec3& v1, const vec3& v2){
    return vec3(v1.x() * v2.x(), v1.y() * v2.y(), v1.z() * v2.z());
}
inline vec3 operator* (double t, const vec3& v1){
    return vec3(v1.x() * t, v1.y() * t, v1.z() * t);
}
inline vec3 operator* (const vec3& v1, double t){
    return vec3(v1.x() * t, v1.y() * t, v1.z() * t);
}
inline vec3 operator/ (const vec3& v1, double t){
    return vec3(v1.x() / t, v1.y() / t, v1.z() / t);
}

inline double dot(const vec3& v1, const vec3& v2){
    return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z() ;
}

inline vec3 cross(const vec3& v1, const vec3& v2){
    return vec3(v1.y() * v2.z() - v1.z() * v2.y(),
        v1.z() * v2.x() - v1.x() * v2.z(),
        v1.x() * v2.y() - v1.y() * v2.x());
}

inline vec3 normalize(const vec3& v1){
    float length = v1.length();
    return v1/ length;
}

#endif