
#pragma once

#include "vec3.h"

using color = vec3;

class Material {
private:
    color colorValue;
    float reflectivity;

public:
    // Constructor
    Material(const color& c, float r)
    : colorValue(c), reflectivity(r) {}

    // Getters
    color getColor() const {
        return colorValue;
    }
    float getReflectivity() const {
        return reflectivity;
    }
    // Setters
    void setColor(const color& c) {
        colorValue = c;
    }
    void setReflectivity(float r) {
        reflectivity = r;
    }

};