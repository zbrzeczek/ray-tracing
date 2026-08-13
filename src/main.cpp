#include <iostream>
#include "Objects.h"
#include "color.h"
#include "ray.h"
#include "Vec3.h"
#include <vector>

color ray_color(const ray& r) {
    vec3 dir = r.get_direction();
    // tutaj jakas funkcja ktora oblicza kolor raya
    auto a  = 0.5 * (dir.y() + 1.0);
    return (1.0-a) * color(1.0,1.0,1.0) + a * color(0.2, 0.4, 1.0);
}

int main() {
    // Image info
    int width = 400;
    auto aspect_ratio = 16.0 / 9.0;

    int height = int(width / aspect_ratio);
    height = (height < 1) ? 1 : height;

    // camera info 
    auto focal_length = 1.0; // odleglosc kamery od viewport
    float viewport_height = 2.0;
    float viewport_width = viewport_height * (double(width)/height);
    vec3 camera = point3(0.0, 0.0, 0.0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);
    
    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / width;
    auto pixel_delta_v = viewport_v / height;
    
    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    // tutaj dodajemy polowe bo pixel jako srodek pixela 
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    std::vector<unsigned char> pixels(width * height * 3);

    // example objects created to test if it even works
    Material new_material;
    new_material.color = &Colors::White;
    new_material.reflectivity = 0.0f;
    Sphere *s1 = new Sphere(0.0f, 0.0f, 0.0f, &new_material, 1.0f);

    // Render

    std::cout << "P3\n" << width << ' ' << height << "\n255\n";

    for (int j = 0; j < height; j++) {
        std::clog << "\rScanlines remaining: " << (height - j) << ' ' << std::flush;
        for (int i = 0; i < width; i++) {
            auto next_pixel_centre = pixel00_loc + j * pixel_delta_v + i * pixel_delta_u;
            // tutaj odejmujemy dwa wektory zeby zobaczyc kierunek swiatla
            auto ray_direction = next_pixel_centre - camera;
            ray r(next_pixel_centre, ray_direction);

            color pixel_col = ray_color(r);
            make_color(std::cout, pixel_col);
        }
    }

    std::clog << "\rDone.                 \n";
}