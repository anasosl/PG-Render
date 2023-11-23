#ifndef RAYH
#define RAYH

#include "vec3.h"
#include "point3.h"

// P(t) = P + t*D
class Ray
{
public:
    Ray() {}
    Ray(const Point3 &p, const Vec3 d)
    {
        P = p;
        D = d;
    }

    //ponto de origem do raio
    Point3 origin() const { return P; }

    //vetor da direcao do raio
    Vec3 direction() const { return D; }

    //retorna um ponto a partir da origem
    Point3 point_at(double t) const { return P + t * D; }

    Point3 P;
    Vec3 D;
};

#endif