#include "Objects.h"

// shape 
Shape::Shape(float x, float y, float z, Material* material)
    : m_Material(material)
{
    m_Position = new vec3(x, y, z);
}

Shape::~Shape()
{
    delete m_Position;
    m_Position = nullptr;
}

vec3* Shape::getPosition()
{
    return m_Position;
}

void Shape::setPosition(vec3* pos)
{
    m_Position = pos;
}

// Sphere 
Sphere::Sphere(float x, float y, float z, Material* material, float radius)
    : Shape(x, y, z, material), m_Radius(radius) {}
