#ifndef GEOMETRICOBJH
#define GEOMETRICOBJH

#include "ray.h"

class geometricObj
{
public:
    geometricObj(vec3 Color, double Kd, double Ks, double Ka, double Kr, double Kt, double N) : color(Color), kd(Kd), ks(Ks), ka(Ka), kr(Kr), kt(Kt), n(N) {}

    virtual double intersect(const ray &r) {}
    virtual vec3 intNormal(const ray &r, double t) {}

    vec3 color;
    double kd;
    double ks;
    double ka;
    double kr;
    double kt;
    double n;

};

#endif
