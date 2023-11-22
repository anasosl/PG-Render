#include <fstream>
#include <iostream>
#include "ray.h"
#include "sphere.h"
#include "plane.h"
#include "geometricObj.h"
#include "camera.h"
#include <bits/stdc++.h>
using namespace std;

vec3 color(const ray &r, double dist, vector<geometricObj*> &objects)
{

    vector<pair<double, int>> ts;
    for (int i = 0; i < objects.size(); i++) {
        geometricObj* obj = objects[i]; 
        double t = obj->intersect(r);
        // a interseção só é válida se ocorrer depois do plano
        if (t > dist)
            ts.push_back({t, i});
    }

    sort(ts.begin(), ts.end());
    if (ts.empty()) {
        return vec3(0,0,0);
    }
    geometricObj* objf = objects[ts[0].second];
        return objf->color();
    

    
    
    
}

int main()
{
    ofstream f_out;
    f_out.open("test4.ppm");
    point3 origem = point3(0, 0, 0);
    point3 alvo = point3(1, 0, 0);
    vec3 cima = vec3(0, 1, 0);
    Camera cam(origem, alvo, cima);
    int dist = 1;
    int resh = 500;
    int resv = 500;
    // cin >> ds >> resh >> resv;
    double tamx = 1;
    double tamy = 1;
    vec3 qx = (2 * tamx / (resh - 1)) * cam.u;
    vec3 qy = (2 * tamy / (resv - 1)) * cam.v;
    vec3 canto_inf_esq = dist * cam.w - tamx * cam.u - tamy * cam.v;

    sphere sp(point3(5, 0.0, 0.0), 1.5, vec3(255, 0, 0));
    plane pl(point3(10,0,0), vec3(-1, 0, 0), vec3(0,0, 255));

    vector<geometricObj *> objects;
    objects.push_back(&sp);
    objects.push_back(&pl);

    f_out << "P3\n";
    f_out << resh << " " << resv << "\n255\n";

    for (int y = 0; y < resh; y++)
    {
        for (int x = 0; x < resv; x++)
        {
            ray r(origem, canto_inf_esq + (x * qx) + (y * qy));
            vec3 col = color(r, dist, objects);
            int ir = int(col.r());
            int ig = int(col.g());
            int ib = int(col.b());
            f_out << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    return 0;
}
