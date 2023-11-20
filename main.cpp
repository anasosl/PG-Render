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
    f_out.open("test4.ppm");
    point3 origem = point3(20, 0, 0);
    point3 alvo = point3(1, 0, 0);
    vec3 cima = vec3(0, 0, 1);
    Camera cam(origem, alvo, cima);
    int ds;
    int resh;
    int resv;
    cin >> ds >> resh >> resv;
    int tamx = 1;
    int tamy = 1;
    vec3 qx = 2 * tamx / (resh - 1) * cam.u;
    vec3 qy = 2 * tamy / (resv - 1) * cam.v;
    vec3 canto_inf_esq = ds * cam.w - tamx * cam.u - tamy * cam.v;

    sphere sp(point3(0.0, 0.0, 0.0), 10, vec3(1.0, 0.0, 0.0));

    f_out << "P3\n";
    f_out << resh << " " << resv << "\n255\n";

    for (int y = resh - 1; y >= 0; y--)
    {
        for (int x = 0; x < resv; x++)
        {
            ray r(origem, canto_inf_esq + x * qx + y * qy);
            vec3 col = color(r, sp);
            int ir = int(255.99 * col.r());
            int ig = int(255.99 * col.g());
            int ib = int(255.99 * col.b());
            f_out << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    return 0;
}