#ifndef SPHEREH
#define SPHEREH
#include "geometricObj.h"

class sphere : public geometricObj
{
public:
    sphere(const point3 &center, double radius, const vec3 &color)
        : geometricObj(color), Center(center), Radious(radius) {}

    bool intersect(const ray &r) const
    {
        
        vec3 oc = (r.origin()) - (Center);
        double a = dot(r.direction(), r.direction());
        double b = 2.0 * dot(oc, r.direction());
        double c = dot(oc, oc) - (Radious * Radious);
        double discriminant = (b * b) - (4 * a * c);
        return (discriminant > 0);
    }

    point3 Center;
    double Radious;
};

#endif