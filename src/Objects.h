#pragma once
#include "Materials.h"
#include "vec3.h"

class Shape {
protected:
    Material &m_Material;
    vec3 m_Position;
    
public:
    Shape(float x, float y, float z, Material & material);
    virtual ~Shape();

    vec3 getPosition();
    void setPosition(vec3 pos);

    Material & getMaterial();
    void setMaterial(Material & material);
};

class Sphere : public Shape {
private:
    float m_Radius;

public:
    Sphere(float x, float y, float z, Material & material, float radius);

    float getRadius();
    void setRadius(float r);
};
