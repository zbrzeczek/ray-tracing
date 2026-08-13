# Ray Tracing

A C++ implementation of a ray tracing engine to practice graphics programming and mathematics concepts.

## Overview

This project implements a basic ray tracing renderer from scratch. Ray tracing is a rendering technique that simulates light rays bouncing around a 3D scene to produce photorealistic images. The project includes:

- **Vector Math**: A custom `Vec3` class for 3D vector operations
- **Materials System**: Support for different material properties including color and reflectivity
- **Geometric Objects**: Shapes like spheres that can be rendered
- **Ray Casting**: Core ray tracing logic to compute pixel colors
- **Camera System**: Configurable camera with viewport and projection

## Project Structure

```
src/
├── main.cpp          # Main application entry point
├── Vec3.h            # 3D vector class and operations
├── ray.h             # Ray definition and operations
├── Objects.h         # Shape definitions (Sphere, etc.)
├── objects.cpp       # Shape implementations
├── Materials.h       # Material properties and colors
└── color.h           # Color representation
CMakeLists.txt        # CMake build configuration
```

## Building

### Requirements

- C++17 or later
- CMake 3.10+
- GLFW3
- OpenGL

### Build Instructions

```bash
mkdir build
cd build
cmake ..
make
./app
```

## Features

- **3D Vector Math**: Complete vector operations (addition, subtraction, scalar multiplication, dot product, cross product)
- **Ray-Object Intersection**: Ray tracing through geometric shapes
- **Material Properties**: Colors and reflectivity for realistic rendering
- **Viewport Rendering**: Configurable image resolution and aspect ratio

## Code Example

```cpp
// Create a material
Material new_material;
new_material.color = &Colors::White;
new_material.reflectivity = 0.0f;

// Create a sphere
Sphere *s1 = new Sphere(0.0f, 0.0f, 0.0f, &new_material, 1.0f);

// Render by casting rays
```

## Future Enhancements

- [ ] Recursive ray bouncing for reflections
- [ ] Shadows and lighting calculations
- [ ] Additional shape types (planes, triangles, meshes)
- [ ] Texture mapping
- [ ] Performance optimizations (BVH acceleration structures)
- [ ] Output to image files (PPM, PNG)

## Learning Resources

This project is inspired by the principles of ray tracing described in computer graphics literature and serves as a hands-on exploration of 3D graphics fundamentals.
