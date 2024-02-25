#ifndef RAYH
#define RAYH

#include "vec3.h"
#include "point3.h"

using namespace std;
#include <iostream>

// P(t) = P + t*D
class ray
{
public:
    ray() {}
    ray(const point3 &p, const vec3 d)
    {
        P = p;
        D = d;
        D.make_unit_vector();
    }
    point3 origin() const { return P; }
    vec3 direction() const { return D; }
    point3 point_at(double t) const { return P + t * D; }

    point3 P;
    vec3 D;
};

#endif