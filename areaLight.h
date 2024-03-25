#ifndef AREALIGHTH
#define AREALIGHTH

#include "vec3.h"
#include "point3.h"

using namespace std;
#include <iostream>

class areaLight {

public:
    areaLight(point3 Origin, vec3 Color, vec3 L) {origin = Origin; color = Color; l = L;}

    point3 origin;
    vec3 color;
    vec3 l;
};

#endif