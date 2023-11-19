#include <fstream>
#include <iostream>
#include "ray.h"
#include "sphere.h"
#include "geometricObj.h"

vec3 color(const ray &r, const geometricObj &obj)
{
    if (obj.intersect(r))
        return obj.color();
    else
        return vec3(0.0, 0.0, 0.0);
}

int main()
{
    std::ofstream f_out;
    f_out.open("test2.ppm");

    int width = 400;
    int height = 400;
    vec3 lower_left_corner(-1.0, -1.0, 1.0);
    vec3 horizontal(1.0, 0.0, 0.0);
    vec3 vertical(0.0, 1.0, 0.0);
    point3 origin(0.0, 0.0, 0.0);

    sphere sp(point3(0.0, 0.0, 2), 0.5, vec3(1.0, 0.0, 0.0));

    f_out << "P3\n";
    f_out << width << " " << height << "\n255\n";

    for (int y = height - 1; y >= 0; y--)
    {
        for (int x = 0; x < width; x++)
        {
            double u = double(x) / double(width);
            double v = double(y) / double(height);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            vec3 col = color(r, sp);
            int ir = int(255.99 * col.r());
            int ig = int(255.99 * col.g());
            int ib = int(255.99 * col.b());
            f_out << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
}