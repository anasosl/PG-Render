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

#define EPSILON 0.02

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

        plane plan = plane(A, normal, vec3(0,0,0), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
        vector<vector<vec3>> a;
        tuple<double, vec3, vec3> output = plan.intersect(r, a);
        double t = get<0>(output);
        if(t>0)
        {
            point3 P = r.point_at(t);
            
            vec3 PAB = cross(B - A, P - B);
            vec3 PAC = cross(C - B, P - B);
            vec3 PBC = cross(A - C, P - C);

            if (dot(normal, PAB) < 0 || dot(normal, PAC) < 0 || dot(normal, PBC) < 0)
                return -1;

        return t;
        }
        return -1;
    }

    vec3 intNormal(const ray &r) const {
        if (dot(r.direction(), normal) > 0) {
            return vec3(-normal.x(), -normal.y(), -normal.z());
        } else return normal;
    }

};

class Mesh : public geometricObj
{
    /*
        numTriangles = número de triângulos
        numVertices = número de vértices
        vertices = lista de vértices (pontos) 
        triangleVertices = lista com triplas dos vértices
    */
public:

    vector<Triangle> triangles;

    Mesh(int numTriangles, int numVertices, const vector<point3> &vertices, const vector<vector<int>> &triangleVertices, 
    const vec3 &color, double Kd, double Ks, double Ka, double Kr, double Kt, double N)
        : geometricObj(color, Kd, Ks, Ka, Kr, Kt, N)
    {
        for (int i = 0; i < numTriangles; i++)
        {
            int idxA = triangleVertices[i][0];
            int idxB = triangleVertices[i][1];
            int idxC = triangleVertices[i][2];

            point3 A = vertices[idxA];
            point3 B = vertices[idxB];
            point3 C = vertices[idxC];

            triangles.push_back(Triangle(A, B, C));
        }
    }

    tuple<double, vec3, vec3> intersect(const ray &r, vector<vector<vec3>> &texture)
    {
        auto [t, a] = intersectTriangle(r);
        vec3 normal = a.intNormal(r);

        return {t, normal, color};
        
    }

    
    pair<double,Triangle> intersectTriangle(const ray &r) {
        double t;
        double minT = 10000000;
        point3 A = point3(0,0,0);
        Triangle T = Triangle(A,A,A);
        
        for (auto a : triangles)
        {
            t = a.intersect(r);
            // t negativo significa que não tem interseção ou ela ocorreu atrás da câmera
            if(t > 0 && t < minT){
                minT = t;
                T = a;
            }
        }

        return {minT, T};
    }


};

#endif