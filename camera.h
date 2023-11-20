#ifndef CAMERAH
#define CAMERAH


#include "point3.h"
#include "vec3.h"


class camera{
 public:
    point3 origem;
    point3 alvo;
    vec3 up;
    vec3 w;
    vec3 u;
    vec3 v;

    camera(const point3 &or, const point3 &al, const vec3 &cima);
};

camera::camera(const point3 &or, const point3 &al, const vec3 &cima){
    origem(or);
    alvo(al);
    up(cima);
    w(alvo - origem);
    u(vec3::cross(w, up));
    v(vec3::cross(w, u));
    w.make_unit_vector();
    u.make_unit_vector();
    v.make_unit_vector();
}
#endif