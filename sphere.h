#ifndef SPHEREH
#define SPHEREH
#include "geometricObj.h"

class sphere : public geometricObj
{
public:
    sphere(const point3 &center, double radius, 
    const vec3 &color, double Kd, double Ks, double Ka, double Kr, double Kt, double N)
        : geometricObj(color, Kd, Ks, Ka, Kr, Kt, N), Center(center), Radious(radius) {}

    double intersect(const ray &r) const
    {
        double t;

        vec3 oc = (r.origin()) - (Center);
        double a = dot(r.direction(), r.direction());
        double b = 2.0 * dot(oc, r.direction());
        double c = dot(oc, oc) - (Radious * Radious);
        double delta = (b * b) - (4 * a * c);
        if (delta >= 0)
        {
            t = (-b - sqrt(delta)) / 2 * a;

            if (t < 0)
                t = (-b + sqrt(delta)) / 2 * a;
        }
        else
            t = -1;

        return t;
    }
    vec3 intNormal(const ray &r, double t) const {
        vec3 norm = (r.origin() + t*r.direction()) - (Center);
        return norm;
    }

    point3 Center;
    double Radious;
};

#endif