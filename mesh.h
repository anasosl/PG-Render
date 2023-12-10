#ifndef MESHH
#define MESHH

#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <queue>

#include "geometricObj.h"
#include "vec3.h"
#include "point3.h"
#include "plane.h"

using namespace std;

/*
Input:
    número de triângulos
    número de vértices
    lista de vértices
    lista com triplas dos vértices
    Cor RGB normalizada [0,1]

Calculado:
    lista com normais de triângulos
    lista com normais dos vértices
*/

// classe do triângulo usada como base da mesh //
class Triangle
{
public:
    point3 A, B, C;
    vec3 normal;
    vec3 color;

    Triangle(point3 &a, point3 &b, point3 &c, vec3 &col)
    {
        color = col;

        A = a;
        B = b;
        C = c;

        vec3 AB = B - A;
        vec3 AC = C - A;

        normal = cross(AB, AC);
    }

    double intersect(const ray &r)
    {

        plane plan = plane(A, normal, vec3(0, 0, 0));
        double t = plan.intersect(r);
        if (t > 0)
        {
            point3 P = r.point_at(t);
            double ABC = 0.5 * (cross(B - A, C - A).length());
            double PAB = 0.5 * (cross(A - P, B - P).length());
            double PAC = 0.5 * (cross(A - P, C - P).length());
            double PBC = 0.5 * (cross(B - P, C - P).length());

            double alfa = PAB / ABC;
            double beta = PAC / ABC;
            double gama = PBC / ABC;

            if (alfa < 0 || alfa > 1)
                return -1;
            if (beta < 0 || beta > 1)
                return -1;
            if (gama < 0 || gama > 1)
                return -1;

            return t;
        }
        return -1;
    }
};

class Mesh : public geometricObj
{
    /*
        num_tri = número de triângulos
        num_vert = número de vértices
        vertices = lista de vértices (pontos)
        tri_vert = lista com triplas dos vértices
    */
public:
    vector<Triangle> triangles;

    Mesh(vector<Triangle> tri, vec3 &color) : geometricObj(color), triangles(tri) {}

    double intersect(const ray &r)
    {
        double t;
        int idx = 0;
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> queue_t;

        // testa interseção com todos os triângulos
        for (auto a : triangles)
        {
            t = a.intersect(r);
            // t negativo significa que não tem interseção ou ela ocorreu atrás da câmera
            if (t > 0)
                queue_t.push({t, idx});

            idx++;
        }

        if (queue_t.size() > 0)
        {
            setColor(triangles[queue_t.top().second].color);
            return queue_t.top().first;
        }
        else
        {
            return -1;
        }
    }
};

Mesh *build_mesh()
{
    int qtd_tri, qtd_vert;

    cout << "Quantidade de triangulos (1 int): " << endl;
    cout << "Quantidade de vertices (1 int): " << endl;
    cin >> qtd_tri >> qtd_vert;

    vector<vector<int>> tri_vert(qtd_tri, vector<int>(3, 0));
    vector<vec3> color(qtd_tri);
    vector<point3> vertices(qtd_vert);
    vector<Triangle> triangles(qtd_tri);

    point3 vert;
    for (int i = 0; i < qtd_vert; i++)
    {
        cout << "Vertice (3 doubles): " << endl;
        cin >> vertices[i];
    }

    for (int i = 0; i < qtd_tri; i++)
    {
        cout << "Indices dos vertices do triangulo " << i << " (3 doubles): " << endl;
        cin >> tri_vert[i][0];
        cin >> tri_vert[i][1];
        cin >> tri_vert[i][2];

        cout << "Cor do triangulo " << i << " (3 doubles): " << endl;
        cin >> color[i];
    }

    for (int i = 0; i < qtd_tri; i++)
    {
        int idxA = tri_vert[i][0];
        int idxB = tri_vert[i][1];
        int idxC = tri_vert[i][2];

        point3 A = vertices[idxA];
        point3 B = vertices[idxB];
        point3 C = vertices[idxC];

        triangles[i] = Triangle(A, B, C, color[i]);
    }

    vec3 mesh_color = vec3(0, 0, 0);
    Mesh *mesh = new Mesh(triangles, mesh_color);
    return mesh;
}

#endif