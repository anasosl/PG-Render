#ifndef GEOMETRICOBJH
#define GEOMETRICOBJH

#include "ray.h"

class geometricObj
{
public:
    geometricObj(vec3 Color, vec3 Kd, vec3 Ks, vec3 Ka, vec3 Kr, vec3 Kt, double N) : color(Color), kd(Kd), ks(Ks), ka(Ka), kr(Kr), kt(Kt), n(N) {}

    virtual double intersect(const ray &r) const = 0;
    virtual vec3 intNormal(const ray &r, double t) const = 0;

    vec3 color;
    vec3 kd;
    vec3 ks;
    vec3 ka;
    vec3 kr;
    vec3 kt;
    double n;

};

#endif
