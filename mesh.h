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

    vector<point3> vertices;
    point3 A, B, C;
    vec3 normal;

    Triangle(const point3 &a, const point3 &b, const point3 &c)
    {
        A = a;
        B = b;
        C = c;

        vec3 AB = B - A;
        vec3 AC = C - A;

        normal = cross(AB, AC);
    }

    double intersect(const ray &r) const
    {

        plane plan = plane(A, normal, vec3(0, 0, 0));
        double t = plan.intersect(r);
        if(t>0)
        {
            point3 P = r.point_at(t);
            
            vec3 PAB = cross(B - A, P - B);
            vec3 PAC = cross(C - B, P - B);
            vec3 PBC = cross(A - C, P - C);

            if (dot(normal, PAB) < 0)
                return -1;
            if (dot(normal, PAC) < 0)
                return -1;
            if (dot(normal, PBC) < 0)
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

    Mesh(int num_tri, int num_vert, const vector<point3> &vertices, const vector<vector<int>> &tri_vert, const vec3 &color)
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
        priority_queue<double, vector<double>, greater<double> > queue_t;
        // testa interseção com todos os triângulos
        for (auto a : triangles)
        {
            t = a.intersect(r);
            // t negativo significa que não tem interseção ou ela ocorreu atrás da câmera
            if(t > 0)
            queue_t.push(t);
        }

        if(queue_t.size()>0)
            return queue_t.top();

        else{
            return -1;
        }
    }

};

#endif