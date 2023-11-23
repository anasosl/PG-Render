#include <fstream>
#include <iostream>
#include "ray.h"
#include "sphere.h"
#include "plane.h"
#include "geometricObj.h"
#include "camera.h"
#include <bits/stdc++.h>
using namespace std;

vec3 color(const ray &r, double dist, vector<geometricObj *> &objects)
{

    vector<pair<double, int>> ts;
    for (int i = 0; i < objects.size(); i++)
    {
        geometricObj *obj = objects[i];
        double t = obj->intersect(r);
        // a interseção só é válida se ocorrer depois do plano
        if (t > dist)
            ts.push_back({t, i});
    }

    sort(ts.begin(), ts.end());
    if (ts.empty())
    {
        return vec3(0, 0, 0);
    }
    geometricObj *objf = objects[ts[0].second];
    return objf->color();
}

int main()
{
    ofstream f_out;
    f_out.open("test4.ppm");
    
    point3 origem;
    point3 alvo;
    vec3 cima;

    cin >> origem >> alvo >> cima;
    
    Camera cam(origem, alvo, cima);
    int dist;
    int resh;
    int resv;
    
    cin >> dist >> resh >> resv;
    
    double tamx = 1;
    double tamy = 1;
    vec3 qx = (2 * tamx / (resh - 1)) * cam.u;
    vec3 qy = (2 * tamy / (resv - 1)) * cam.v;
    vec3 canto_inf_esq = dist * cam.w - tamx * cam.u - tamy * cam.v;

    vector<geometricObj *> objects;

    while(true){
        string type = "";
        point3 p;
        double r;
        vec3 v1, v2;
        
        cin >> type;

        if (type == "sphere"){
            cin >> p >> r >> v1;
            sphere sp(p, r, v1);
            objects.push_back(&sp);
        } else if (type == "plane"){
            cin >> p >> v1 >> v2;
            plane pl(p, v1, v2);
            objects.push_back(&pl);
        } else if (type == "end"){
            break;
        }
                    
    }

    f_out << "P3\n";
    f_out << resh << " " << resv << "\n255\n";

    for (int y = resv - 1; y >= 0; y--)
    {
        for (int x = 0; x < resh; x++)
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
