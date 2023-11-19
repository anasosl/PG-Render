#ifndef GEOMETRICOBJH
#define GEOMETRICOBJH

#include "ray.h"

class geometricObj
{
public:
    geometricObj(vec3 color) { Color = color; }

    inline vec3 color() const { return Color; }
    virtual bool intersect(const ray &r) const = 0;

    vec3 Color;
};

#endif
