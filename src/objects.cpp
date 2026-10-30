#include "Objects.h"

// shape 
Shape::Shape(float x, float y, float z, Material& material)
    : m_Material(material), m_Position(x, y, z)
{
}

Shape::~Shape()
{
}

vec3 Shape::getPosition()
{
    return m_Position;
}

void Shape::setPosition(vec3 pos)
{
    m_Position = pos;
}

Material & Shape::getMaterial(){
    return m_Material;
}

void Shape::setMaterial(Material &material){
    m_Material = material;
}


// Sphere 
Sphere::Sphere(float x, float y, float z, Material& material, float radius)
    : Shape(x, y, z, material), m_Radius(radius) {}

void Sphere::setRadius(float r){
   m_Radius = r;
}

float Sphere::getRadius(){
    return m_Radius;
}
