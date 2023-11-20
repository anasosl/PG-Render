#ifndef CAMERAH
#define CAMERAH

#include "point3.h"
#include "vec3.h"

class Camera
{
public:
    Camera(const point3 &orig, const point3 &al, const vec3 &cima)
    {
        origem = orig;
        alvo = al;
        up = cima;
        w = alvo - origem;
        u = cross(w, up);
        v = cross(w, u);
        w.make_unit_vector();
        u.make_unit_vector();
        v.make_unit_vector();
    }

    point3 origem;
    point3 alvo;
    vec3 up;
    vec3 w;
    vec3 u;
    vec3 v;
};

#endif
