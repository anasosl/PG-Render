#ifndef CAMERAH
#define CAMERAH

#include "point3.h"
#include "vec3.h"

class Camera
{
public:
    Camera(const Point3 &orig, const Point3 &al, const Vec3 &cima)
    {
        //ponto central da camera
        origem = orig;

        //ponto central da tela
        alvo = al;

        //vetor vertical da camera 
        up = cima;

        //vetor entre a camera e a tela (para frente)
        w = alvo - origem;

        //vetor horizontal - produto vetorial (para o lado)
        u = cross(w, up);

        //vetor vertical - produto vetorial (para cima)
        v = cross(w, u);

        //normalizando os vetores
        w.make_unit_vector();
        u.make_unit_vector();
        v.make_unit_vector();
    }

    //declarando valores da classe
    Point3 origem;
    Point3 alvo;
    Vec3 up;
    Vec3 w;
    Vec3 u;
    Vec3 v;
};

#endif
