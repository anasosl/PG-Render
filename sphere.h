#ifndef SPHEREH
#define SPHEREH
#include "geometricObj.h"

class sphere : public geometricObj
{
public:
    sphere(const point3 &center, double radius, const vec3 &color)
        : geometricObj(color), Center(center), Radious(radius) {}

    double intersect(const ray &r) const
    {
        double t;

        vec3 oc = (r.origin()) - (Center);
        double a = dot(r.direction(), r.direction());
        double b = 2.0 * dot(oc, r.direction());
        double c = dot(oc, oc) - (Radious * Radious);
        double delta = (b * b) - (4 * a * c);
        if (delta >= 0)
            t = -b - sqrt(delta);
        else
            t = -1;
        
        return t;
    }

    point3 Center;
    double Radious;
};

#endif