#include <fstream>
#include <iostream>
#include "ray.h"
#include "sphere.h"
#include "geometricObj.h"
#include "camera.h"
using namespace std;

vec3 color(const ray &r, const geometricObj &obj)
{
    if (obj.intersect(r))
        return obj.color();
    else
        return vec3(0.0, 0.0, 0.0);
}

int main()
{
    ofstream f_out;
    f_out.open("test2.ppm");
    camera cam(point3(0,0,0), point3(3,3,3), vec3(0,1,0));
    int ds;
    int resh;
    int resv;
    cin>>ds>>resh>>resv;
    int tamx = 1;
    int tamy = 1;
    vec3 qx = 2*tamx/(resh-1)*cam.u;
    vec3 qy = 2*tamy/(resv-1)*cam.v;
    vec3 ct_inf_esq = ds*cam.w - tamx*cam.u - tamy*cam.v;
    
    

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