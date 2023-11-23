#ifndef PLANEH
#define PLANEH
#include "geometricObj.h"

class Plane : public GeometricObj
{
public:
    Plane(const Point3 &planepoint, const Vec3& normal, const Vec3 &color)
        : GeometricObj(color), Normal(normal), PP(planepoint) {}

    double intersect(const Ray &r) const
    {
        double t;
        
        Vec3 pp = Vec3(PP.x(), PP.y(), PP.z());
        Vec3 og = Vec3(r.origin().x(), r.origin().y(), r.origin().z());

        //produtos escalares
        double a = dot(Normal, pp);
        double b = dot(Normal, og);
        double c = dot(Normal, r.direction());

        if (c != 0) {
            t = (a - b) / c;
        }
    
    
        return t;
    }

    Point3 PP;
    Vec3 Normal;
};

#endif
