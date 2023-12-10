#ifndef GEOMETRICOBJH
#define GEOMETRICOBJH

#include "ray.h"

class geometricObj
{
public:
    vec3 Color;

    geometricObj(vec3 col) : Color(col) {}

    inline vec3 getColor() const { return Color; }
    inline void setColor(vec3 col) { Color = col; }
    virtual double intersect(const ray &r) = 0;
};

#endif
