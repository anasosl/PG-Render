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

vec3 calc_color(const ray &r, vector<geometricObj *> &objects)
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

    int qtd_tri, qtd_vert;

    cout << "Quantidade de triangulos (1 int): " << endl;
    cout << "Quantidade de vertices (1 int): " << endl;
    cin >> qtd_tri >> qtd_vert;

    vector<vector<int>> tri_vert(qtd_tri);
    vector<vec3> tri_colors(qtd_tri);
    vector<point3> vertices(qtd_vert);
    vector<Triangle> triangles(qtd_tri);

    for (int i = 0; i < qtd_vert; i++)
    {
        double x1, y1, z1;
        cout << "Vertice (3 doubles): " << endl;
        cin >> x1 >> y1 >> z1;
        point3 v = point3(x1, y1, z1);
        vertices[i] = v;

    }

    for (int i = 0; i < qtd_tri; i++)
    {
        cout << "Indices dos vertices do triangulo " << i << " (3 int): " << endl;
        int ind;
        cin >> ind;
        tri_vert[i].push_back(ind);
        cin >> ind;
        tri_vert[i].push_back(ind);
        cin >> ind;
        tri_vert[i].push_back(ind);
        double x1, y1, z1;
        cout << "Cor do triangulo " << i << " (3 doubles): " << endl;
        cin >> x1 >> y1 >> z1;
        vec3 v2 = vec3(x1, y1, z1);
        tri_colors[i] = v2;
    }

    for (int i = 0; i < qtd_tri; i++)
    {
        int idxA = tri_vert[i][0];
        int idxB = tri_vert[i][1];
        int idxC = tri_vert[i][2];

        point3 A = vertices[idxA];
        point3 B = vertices[idxB];
        point3 C = vertices[idxC];

        Triangle *tri = new Triangle(A, B, C, tri_colors[i]);
        objects.push_back(tri);
    }

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
            vec3 col = calc_color(r, objects);
            int ir = int(col.r());
            int ig = int(col.g());
            int ib = int(col.b());
            f_out << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    return 0;
}
