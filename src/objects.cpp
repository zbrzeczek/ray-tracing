#include "Objects.h"

namespace Raytracer {

// shape 
Shape::Shape(float x, float y, float z, Material* material)
    : m_Material(material)
{
    m_Position = new Vec3(x, y, z);
}

Shape::~Shape()
{
    delete m_Position;
    m_Position = nullptr;
}

Vec3* Shape::getPosition()
{
    return m_Position;
}

void Shape::setPosition(Vec3* pos)
{
    m_Position = pos;
}

// Sphere 
Sphere::Sphere(float x, float y, float z, Material* material, float radius)
    : Shape(x, y, z, material), m_Radius(radius) {}

}