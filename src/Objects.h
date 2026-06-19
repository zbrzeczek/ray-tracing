#pragma once
#include "Materials.h"
#include "vec3.h"

struct Material {
    Colors::Color* color;
    float reflectivity;
};

class Shape {
protected:
    Material* m_Material;
    vec3* m_Position;
    
public:
    Shape(float x, float y, float z, Material* material);
    virtual ~Shape();

    vec3* getPosition();
    void setPosition(vec3* pos);
};

class Sphere : public Shape {
private:
    float m_Radius;

public:
    Sphere(float x, float y, float z, Material* material, float radius);
};
