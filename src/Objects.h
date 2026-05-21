#pragma once
#include "Materials.h"
#include "Vec3.h"

namespace Raytracer {

struct Material {
    Colors::Color* color;
    float reflectivity;
};

class Shape {
protected:
    Material* m_Material;
    Vec3* m_Position;
    
public:
    Shape(float x, float y, float z, Material* material);
    virtual ~Shape();

    Vec3* getPosition();
    void setPosition(Vec3* pos);
};

class Sphere : public Shape {
private:
    float m_Radius;

public:
    Sphere(float x, float y, float z, Material* material, float radius);
};

}