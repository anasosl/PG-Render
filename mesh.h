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

typedef tuple<int, int, int> triple;

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
    Triangle(point3 a, point3 b, point3 c)
    {
        A = a;
        B = b;
        C = c;

        vec3 AB = A - B;
        vec3 AC = A - C;

        normal = cross(AB, AC);
    }

    double intersect(const ray &r) const
    {
        double t;

        plane plan = plane(A, normal, vec3(0, 0, 0));
        double t = plan.intersect(r);
        point3 P = r.point_at(t);

        double ABC = 0.5 * (cross(B - A, C - A).length());
        double PAB = 0.5 * (cross(P - A, P - B).length());
        double PAC = 0.5 * (cross(P - A, P - C).length());
        double PBC = 0.5 * (cross(P - B, P - C).length());

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

    vector<point3> vertices;
    point3 A, B, C;
    vec3 normal;
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
    Mesh(int num_tri, int num_vert, vector<point3> vertices, vector<vector<int>> tri_vert, const vec3 &color)
        : geometricObj(color)
    {
        for (int i = 0; i < num_tri; i++)
        {
            int idxA = tri_vert[i][0];
            int idxB = tri_vert[i][1];
            int idxC = tri_vert[i][2];

            point3 A = vertices[idxA];
            point3 B = vertices[idxB];
            point3 C = vertices[idxC];

            triangles.push_back(Triangle(A, B, C));
        }
    }

    double intersect(const ray &r) const
    {
        double t;
        priority_queue<double> queue_t;
        // testa interseção com todos os triângulos
        for (auto a : triangles)
        {
            t = a.intersect(r);
            queue_t.push(t);
        }

        // t negativo significa que não tem interseção ou ela ocorreu atrás da câmera
        while (queue_t.top() < 0) 
        {
            queue_t.pop();

            if (queue_t.empty())
                return -1;
        }

        return queue_t.top();
    }

    vector<Triangle> triangles;
};

#endif