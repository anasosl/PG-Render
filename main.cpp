#include <fstream>
#include <iostream>
#include "ray.h"
#include "sphere.h"
#include "plane.h"
#include "geometricObj.h"
#include "camera.h"
#include <bits/stdc++.h>
using namespace std;

//determinar a cor do pixel
Vec3 color(const Ray &r, double dist, vector<GeometricObj*> &objects)
{
    //vetor de pares: distancia, index do objeto no vector objects
    vector<pair<double, int>> ts;

    for (int i = 0; i < objects.size(); i++) {
        GeometricObj* obj = objects[i]; 
        double t = obj->intersect(r);
        // a interseção só é válida se ocorrer depois do plano
        if (t > dist)
            ts.push_back({t, i});
    }

    //organiza o vector do objeto de forma crescente de distancia
    sort(ts.begin(), ts.end());

    //se o vector estiver vazio, o pixel é preto
    if (ts.empty()) {
        return Vec3(0,0,0);
    }
    
    //retorna a cor do objeto mais próximo
    GeometricObj* objf = objects[ts[0].second];
    return objf->color();
    
}

int main()
{
    ofstream f_out;
    f_out.open("grupo4.ppm");

    //inputs
    Point3 origem = Point3(0, 0, 0);
    Point3 alvo = Point3(1, 0, 0);
    Vec3 cima = Vec3(0, 1, 0);
    int dist = 1;
    int resh = 500;
    int resv = 500;
    
    //objetos
    Sphere sp(Point3(3.5, 0.0, -0.7), 1.5, Vec3(200, 50, 0));
    Sphere sp1(Point3(7, 0.0, 1.0), 3.0, Vec3(200, 250, 0));
    Plane pl(Point3(0, 1, 0), Vec3(0, 1, 0), Vec3(20, 20, 150));
    
    //vector dos objetos 
    vector<GeometricObj *> objects;
    objects.push_back(&sp);
    objects.push_back(&sp1);
    objects.push_back(&pl);


    
    // cin >> ds >> resh >> resv;
    
    
    Camera cam(origem, alvo, cima);
    
    double tamx = 1;
    double tamy = 1;
    Vec3 qx = (2 * tamx / (resh - 1)) * cam.u;
    Vec3 qy = (2 * tamy / (resv - 1)) * cam.v;
    Vec3 canto_inf_esq = dist * cam.w - tamx * cam.u - tamy * cam.v;

    
    

    f_out << "P3\n";
    f_out << resh << " " << resv << "\n255\n";

    //cor de cada pixel da tela
    for (int y = resh - 1; y >= 0; y--)
    {
        for (int x = 0; x < resv; x++)
        {
            Ray r(origem, canto_inf_esq + (x * qx) + (y * qy));
            Vec3 col = color(r, dist, objects);
            int ir = int(col.r());
            int ig = int(col.g());
            int ib = int(col.b());
            f_out << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    return 0;
}
