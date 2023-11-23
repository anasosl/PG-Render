#ifndef SPHEREH
#define SPHEREH
#include "geometricObj.h"

class Sphere : public GeometricObj
{
public:
    Sphere(const Point3 &center, double radius, const Vec3 &color)
        : GeometricObj(color), Center(center), Radious(radius) {}

    double intersect(const Ray &r) const
    {
        double t;

        
        Vec3 oc = (r.origin()) - (Center);
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

    Point3 Center;
    double Radious;
};

#endif