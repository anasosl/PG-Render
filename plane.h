#ifndef PLANEH
#define PLANEH
#include "geometricObj.h"

class plane : public geometricObj
{
public:
    plane(const point3 &planepoint, const vec3& normal, 
    const vec3 &color, vec3 Kd, vec3 Ks, vec3 Ka, vec3 Kr, vec3 Kt, double N)
        : geometricObj(color, Kd, Ks, Ka, Kr, Kt, N), Normal(normal), PP(planepoint) {}

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

    vec3 intNormal(const ray &r, double t) const {
        if (dot(r.direction(), Normal) > 0) {
            return vec3(-Normal.x(), -Normal.y(), -Normal.z());
        } else return Normal;
    }

    point3 PP;
    vec3 Normal;
};

#endif  
