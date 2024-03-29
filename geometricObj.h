#ifndef GEOMETRICOBJH
#define GEOMETRICOBJH

#include "ray.h"
#include <vector>
#include <tuple>

class geometricObj
{
public:
    geometricObj(vec3 Color, double Kd, double Ks, double Ka, double Kr, double Kt, double N) : color(Color), kd(Kd), ks(Ks), ka(Ka), kr(Kr), kt(Kt), n(N) {}

    virtual tuple<double, vec3, vec3> intersect(const ray &r, vector<vector<vec3>> &texture) {
        return make_tuple(0, vec3(0,0,0), color);
    }

    vec3 color;
    double kd;
    double ks;
    double ka;
    double kr;
    double kt;
    double n;

};

#endif
