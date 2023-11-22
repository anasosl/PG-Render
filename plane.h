#ifndef PLANEH
#define PLANEH
#include "geometricObj.h"

class plane : public geometricObj
{
public:
    plane(const point3 &planepoint, const vec3& normal, const vec3 &color)
        : geometricObj(color), Normal(normal), PP(planepoint) {}

    double intersect(const ray &r) const
    {
        double t;

        vec3 pp = vec3(PP.x(), PP.y(), PP.z());
        vec3 og = vec3(r.origin().x(), r.origin().y(), r.origin().z());

        double a = dot(Normal, pp);
        double b = dot(Normal, og);
        double c = dot(Normal, r.direction());

        if (c != 0) {
            t = (a - b) / c;
        }
    
    
        return t;
    }

    point3 PP;
    vec3 Normal;
};

#endif  
