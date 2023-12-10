#include <fstream>
#include <iostream>
#include "ray.h"
#include "sphere.h"
#include "plane.h"
#include "geometricObj.h"
#include "camera.h"
#include "mesh.h"
#include <bits/stdc++.h>
using namespace std;

vec3 color(const ray &r, vector<geometricObj *> &objects)
{
    vector<pair<double, int>> ts;
    for (long long unsigned int i = 0; i < objects.size(); i++)
    {
        geometricObj *obj = objects[i];
        double t = obj->intersect(r);
        // a interseção só é válida se ocorrer depois do plano
        if (t > 0)
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

    double x, y, z;

    point3 origem;
    point3 alvo;
    vec3 cima;

    cout << "Origem da camera (3 doubles): \n";
    cin >> x >> y >> z;
    origem = point3(x, y, z);
    cout << "Alvo (3 doubles): \n";
    cin >> x >> y >> z;
    alvo = point3(x, y, z);
    cout << "Up vector (3 doubles): \n";
    cin >> x >> y >> z;
    cima = vec3(x, y, z);

    Camera cam(origem, alvo, cima);
    double dist;
    int resh;
    int resv;

    cout << "Distancia (1 double): \n";
    cin >> dist;
    cout << "Resolucao v (1 int): \n";
    cin >> resh;
    cout << "Resolucao h (1 int): \n";
    cin >> resv;

    double tamx = 1;
    double tamy = 1;
    vec3 qx = (2 * tamx / (resh - 1)) * cam.u;
    vec3 qy = (2 * tamy / (resv - 1)) * cam.v;
    vec3 canto_inf_esq = dist * cam.w - tamx * cam.u - tamy * cam.v;

    vector<geometricObj *> objects;
    vector<point3> lst_ver = {point3(5, 0, 0), point3(5, 1, 0), point3(5, 0, 1), point3(5, 1, 1)};
    vector<vector<int>> lst_tri(2);
    lst_tri[0].push_back(0);
    lst_tri[0].push_back(1);
    lst_tri[0].push_back(2);
    lst_tri[1].push_back(1);
    lst_tri[1].push_back(2);
    lst_tri[1].push_back(3);


    vec3 cor_tri = vec3(255, 255, 0);
    Mesh *malha = new Mesh(2, 4, lst_ver, lst_tri, cor_tri);
    objects.push_back(malha);
    cout << "\ndigite end para gerar a imagem | plane para adicionar um plano | sphere para adicionar uma esfera\n";
    while (true)
    {
        string type = "";
        double x, y, z;
        point3 p;
        double r;
        vec3 v1, v2;

        cout << "\nTipo de objeto: \n";
        cin >> type;

        if (type == "sphere")
        {
            cout << "Centro (3 doubles): \n";
            cin >> x >> y >> z;
            p = point3(x, y, z);
            cout << "Raio (1 double): \n";
            cin >> r;
            cout << "Cor (3 doubles): \n";
            cin >> x >> y >> z;
            v1 = vec3(x, y, z);
            sphere *sp = new sphere(p, r, v1);
            objects.push_back(sp);
        }
        else if (type == "plane")
        {
            cout << "Ponto do plano (3 doubles): \n";
            cin >> x >> y >> z;
            p = point3(x, y, z);
            cout << "Vetor normal (3 doubles): \n";
            cin >> x >> y >> z;
            v1 = vec3(x, y, z);
            cout << "Cor (3 doubles): \n";
            cin >> x >> y >> z;
            v2 = vec3(x, y, z);
            plane *pl = new plane(p, v1, v2);
            objects.push_back(pl);
        }
        else if (type == "end")
        {
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
            vec3 col = color(r, objects);
            int ir = int(col.r());
            int ig = int(col.g());
            int ib = int(col.b());
            f_out << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    return 0;
}
