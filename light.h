#ifndef LIGHTH
#define LIGHTH

#include "vec3.h"
#include "point3.h"

using namespace std;
#include <iostream>

class light {

public:
    light(point3 Origin, vec3 Color) {origin = Origin; color = Color;}

    point3 origin;
    vec3 color;

};

#endif