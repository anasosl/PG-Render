#ifndef SPHEREH
#define SPHEREH
#include "geometricObj.h"

using namespace std;
#include <iostream>

class sphere : public geometricObj
{
public:
    sphere(const point3 &center, double radius, 
    const vec3 &color, vec3 Kd, vec3 Ks, vec3 Ka, vec3 Kr, vec3 Kt, double N)
        : geometricObj(color, Kd, Ks, Ka, Kr, Kt, N), Center(center), Radious(radius) {}

    pair<double, vec3> intersect(const ray &r) const
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

        return {t, vec3((r.origin() + t*r.direction()) - Center)};
    }

    point3 Center;
    double Radious;
};

#endif