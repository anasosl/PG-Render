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

    camera(point3 &or, point3 &al, vec3 &cima);
};

camera::camera(point3 &or, point3 &al, vec3 &cima){
    origem = or;
    alvo = al;
    up = cima;
    w = alvo - origem;
    w.make_unit_vector;
    u = cross(w, up);
    u.make_unit_vector;
    v = cross(w, u);
    v.make_unit_vector;

}
camera
#endif