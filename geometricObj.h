#ifndef GEOMETRICOBJH
#define GEOMETRICOBJH

#include "ray.h"

//superclasse dos objetos geometricos
class GeometricObj
{
public:

    //determina o vetor de cores do objeto
    GeometricObj(Vec3 color) { Color = color; }

    //retorna o vetor de cores do objeto
    inline Vec3 color() const { return Color; }

    virtual double intersect(const Ray &r) const = 0;

    Vec3 Color;
};

#endif
