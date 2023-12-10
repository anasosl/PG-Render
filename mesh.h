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
class Triangle : public geometricObj
{
public:
    point3 A, B, C;
    vec3 normal;

    Triangle(const point3 &a, const point3 &b, const point3 &c, const vec3 &col)
        : geometricObj(col), A(a), B(b), C(c)
    {
        vec3 AB = B - A;
        vec3 AC = C - A;

        normal = cross(AB, AC);
    }

    double intersect(const ray &r) const
    {

        plane plan = plane(A, normal, vec3(0, 0, 0));
        double t = plan.intersect(r);
        if (t > 0)
        {
            point3 P = r.point_at(t);

            vec3 v0 = B - A;
            vec3 v1 = C - A;
            vec3 v2 = P - A;
            double d00 = dot(v0, v0);
            double d01 = dot(v0, v1);
            double d11 = dot(v1, v1);
            double d20 = dot(v2, v0);
            double d21 = dot(v2, v1);

            double denom = d00 * d11 - d01 * d01;

            double alfa = (d11 * d20 - d01 * d21) / denom;
            double beta = (d00 * d21 - d01 * d20) / denom;
            double gama = 1 - alfa - beta;

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

#endif