#ifndef CAMERAH
#define CAMERAH

#include "point3.h"
#include "vec3.h"

using namespace std;
#include <iostream>

class Camera
{
public:
    Camera(const point3 &Origin, const point3 &Target, const vec3 &Up)
    {
        origin = Origin;
        target = Target;
        up = Up;
        w = target - origin;
        u = cross(w, up);
        v = cross(u, w);
        w.make_unit_vector();
        u.make_unit_vector();
        v.make_unit_vector();
    }

    point3 origin;
    point3 target;
    vec3 up;
    vec3 w;
    vec3 u;
    vec3 v;
};

#endif
