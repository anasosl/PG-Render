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
    for (long long unsigned int i = 0; i < objects.size(); i++)
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

    double x, y, z;

    point3 origem;
    point3 alvo;
    vec3 cima;

    cout << "\nPara inicializar, tu precisas colocar 9 doubles (3 para a origem, 3 para o alvo e 3 para determinar o vetor cima)\n";
    cin >> x >> y >> z;
    origem = point3(x, y, z);
    cin >> x >> y >> z;
    alvo = point3(x, y, z);
    cin >> x >> y >> z;
    cima = vec3(x, y, z);

    Camera cam(origem, alvo, cima);
    int dist;
    int resh;
    int resv;

    cout << "\nAgora, tu precisas colocar 3 inteiros (distancia da camera para a tela, resolucao horizontal e resolucao vertical)\n";
    cin >> dist >> resh >> resv;

    double tamx = 1;
    double tamy = 1;
    vec3 qx = (2 * tamx / (resh - 1)) * cam.u;
    vec3 qy = (2 * tamy / (resv - 1)) * cam.v;
    vec3 canto_inf_esq = dist * cam.w - tamx * cam.u - tamy * cam.v;

    vector<geometricObj *> objects;

    while (true)
    {
        string type = "";
        double x, y, z;
        point3 p;
        double r;
        vec3 v1, v2;

        cout << "\nPara cada objeto, coloque sphere ou plane. Se tu nao quiseres adicionar outro objeto, digite end.\n";
        cin >> type;

        if (type == "sphere")
        {
            cout << "\nPara a esfera, tu precisas colocar 7 doubles (3 para o centro, 1 para o raio e 3 para as cores)\n";
            cin >> x >> y >> z;
            p = point3(x, y, z);
            cin >> r;
            cin >> x >> y >> z;
            v1 = vec3(x, y, z);
            sphere *sp = new sphere(p, r, v1);
            objects.push_back(sp);
        }
        else if (type == "plane")
        {
            cout << "\nPara o plano, tu precisas colocar 9 doubles (3 para o centro, 3 para a normal e 3 para as cores)\n";
            cin >> x >> y >> z;
            p = point3(x, y, z);
            cin >> x >> y >> z;
            v1 = vec3(x, y, z);
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
            vec3 col = color(r, dist, objects);
            int ir = int(col.r());
            int ig = int(col.g());
            int ib = int(col.b());
            f_out << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    return 0;
}
